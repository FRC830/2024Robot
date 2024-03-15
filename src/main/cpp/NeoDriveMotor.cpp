#include "NeoDriveMotor.h"
#include "ratpack/CANSparkMaxDebugMacro.h"

void NeoDriveMotor::Configure(SwerveDriveMotorConfig &config){
    m_encoder = config.encoder;
    m_motorID = config.motorID;
    m_motor = config.motor;
    m_PID = config.PID;

    START_RETRYING(NEO_DRIVE_MTR_RESTORE_FACTORY_DEFAULTS)
    m_motor->RestoreFactoryDefaults();
    END_RETRYING
    START_RETRYING(NEO_DRIVE_MTR_SET_CAN_TIMEOUT)
    m_motor->SetCANTimeout(50);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_PID_SETP)
    m_PID->SetP(config.p);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_PID_SETI)
    m_PID->SetI(config.i);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_PID_SETD)
    m_PID->SetD(config.d);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_PID_SETP)
    m_PID->SetFF(config.ff);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_ENC_SET_VELOCITY_CONVERSION_FACTOR)
    m_encoder->SetVelocityConversionFactor(config.ratio);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_ENC_SET_POSITION_CONVERSION_FACTOR)
    m_encoder->SetPositionConversionFactor(config.ratio * 60);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_motor->SetIdleMode(config.idleMode);

            if (m_motor->GetIdleMode() == config.idleMode)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured NEO_DRIVE_MTR_SET_IDLE_MODE in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure NEO_DRIVE_MTR_SET_IDLE_MODE" << std::endl;
        }
    }

    START_RETRYING(NEO_DRIVE_MTR_SET_SMART_CURRENT_LIMIT)
    m_motor->SetSmartCurrentLimit(config.drive_motor_current_limit);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_motor->EnableVoltageCompensation(config.swerve_voltage_compensation);
    END_RETRYING
    START_RETRYING(NEO_DRIVE_MTR_BURN_FLASH)
    m_motor->BurnFlash();
    END_RETRYING

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



