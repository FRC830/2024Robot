#include "NeoDriveMotor.h"

void NeoDriveMotor::Configure(SwerveDriveMotorConfig &config){
    m_encoder = config.encoder;
    m_motorID = config.motorID;
    m_motor = config.motor;
    m_PID = config.PID;
    m_motor->RestoreFactoryDefaults();
    m_PID->SetP(config.p);
    m_PID->SetI(config.i);
    m_PID->SetD(config.d);
    m_PID->SetFF(config.ff);
    m_motor->SetIdleMode(config.idleMode);
    m_encoder->SetVelocityConversionFactor(config.ratio);
    m_encoder->SetPositionConversionFactor(config.ratio * 60);
    m_motor->SetSmartCurrentLimit(config.drive_motor_current_limit);
    m_motor->BurnFlash();
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



