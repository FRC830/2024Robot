#include "NeoDriveMotor.h"

void NeoDriveMotor::Configure(SwerveDriveMotorConfig &config){
    m_encoder = config.encoder;
    m_motorID = config.motorID;
    m_motor = config.motor;
    m_PID = config.PID;

    bool successfulConfig = false;
    int numRetries = 0;
    rev::REVLibError error;

    while (!successfulConfig && numRetries <= 5)
    {
        numRetries++;

        error = m_motor->RestoreFactoryDefaults();
        if (error != rev::REVLibError::kOk) continue;
        error = m_motor->SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetP(config.p);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetI(config.i);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetD(config.d);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetFF(config.ff);
        if (error != rev::REVLibError::kOk) continue;
        error = m_encoder->SetVelocityConversionFactor(config.ratio);
        if (error != rev::REVLibError::kOk) continue;
        error = m_encoder->SetPositionConversionFactor(config.ratio * 60);
        if (error != rev::REVLibError::kOk) continue;
        error = m_motor->SetIdleMode(config.idleMode);
        if (error != rev::REVLibError::kOk) continue;
        error = m_motor->SetSmartCurrentLimit(config.drive_motor_current_limit);
        if (error != rev::REVLibError::kOk) continue;
        error = m_motor->EnableVoltageCompensation(config.swerve_voltage_compensation);
        if (error != rev::REVLibError::kOk) continue;
        error = m_motor->BurnFlash();
        if (error != rev::REVLibError::kOk) continue;

        successfulConfig = true;
    }

    m_MaxSpeed = config.maxSpeed;
    m_correction_factor = config.correction_factor;
};

units::foot_t NeoDriveMotor::GetPosition()
{
    double position = (m_encoder->GetPosition())  / m_correction_factor;
    return units::foot_t{position};
}

void NeoDriveMotor::SetVelocity(units::velocity::feet_per_second_t v) {


    // TODO - return PID to not need a scaling factor to get to desired setpoint
    m_PID->SetReference(1.6666667 * v.to<double>(), rev::CANSparkMax::ControlType::kVelocity);

};


units::velocity::feet_per_second_t NeoDriveMotor::GetVelocity() {
    return  units::velocity::feet_per_second_t{m_encoder->GetVelocity()};

};



void NeoDriveMotor::SetIdleMode(bool m) {
    m_motor->SetIdleMode(m ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast);

};


bool NeoDriveMotor::GetIdleMode() {
    return m_motor->GetIdleMode() == rev::CANSparkMax::IdleMode::kBrake;

};



