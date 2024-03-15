#include "subsystems/LauncherHAL.h"
#include <iostream>
#include <unistd.h>

#include "ratpack/CANSparkMaxDebugMacro.h"

LauncherHAL::LauncherHAL()
{

    START_RETRYING(LAUNCHER_PVT_MTR_RESTORE_FACOTRY_DEFAULT)
    m_PvtMotor.RestoreFactoryDefaults();
    END_RETRYING
    START_RETRYING(LAUNCHER_IND_MTR_RESTORE_FACOTRY_DEFAULT)
    m_IndMotor.RestoreFactoryDefaults();
    END_RETRYING

    START_RETRYING(LAUNCHER_PVT_MTR_SET_CAN_TIMEOUT)
    m_PvtMotor.SetCANTimeout(50);
    END_RETRYING
    START_RETRYING(LAUNCHER_IND_MTR_RESTORE_FACOTRY_DEFAULT)
    m_IndMotor.SetCANTimeout(50);
    END_RETRYING

    START_RETRYING(LAUNCHER_PVT_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_PvtMotor.EnableVoltageCompensation(VOLT_COMP);
    END_RETRYING
    START_RETRYING(LAUNCHER_IND_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_IndMotor.EnableVoltageCompensation(VOLT_COMP);
    END_RETRYING
    
    START_RETRYING(LAUNCHER_PVT_MTR_SET_SMART_CURRENT_LIMIT)
    m_PvtMotor.SetSmartCurrentLimit(LAUNCHER_PVT_CURRENT_LIMIT);
    END_RETRYING
    START_RETRYING(LAUNCHER_IND_MTR_SET_SMART_CURRENT_LIMIT)
    m_IndMotor.SetSmartCurrentLimit(LAUNCHER_IND_CURRENT_LIMIT);
    END_RETRYING

    START_RETRYING(LAUNCHER_PVT_MTR_SET_IDLE_MODE)
    m_PvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    END_RETRYING
    
    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_PvtMotor.SetInverted(true);
            if (m_PvtMotor.GetInverted() == true)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured LAUNCHER_PVT_MTR_SET_INVERTED in " << retries << " retries" << std::endl; 
        }
        else
        {
            std::cout << "Failed to configure LAUNCHER_PVT_MTR_SET_INVERTED in " << retries << " retries" << std::endl; 
        }
    }

    START_RETRYING(LAUNCHER_PVT_MTR_BURN_FLASH)
    m_PvtMotor.BurnFlash();
    END_RETRYING
    START_RETRYING(LAUNCHER_IND_MTR_BURN_FLASH)
    m_IndMotor.BurnFlash();
    END_RETRYING

    START_RETRYING(LAUNCHER_PVT_PID_SET_POSITION_PID_WRAPPING_ENABLED)
    m_PvtPID.SetPositionPIDWrappingEnabled(false);
    END_RETRYING

    START_RETRYING(LAUNCHER_PVT_PID_SETP)
    m_PvtPID.SetP(PVT_P);
    END_RETRYING
    START_RETRYING(LAUNCHER_PVT_PID_SETI)
    m_PvtPID.SetI(PVT_I);
    END_RETRYING
    START_RETRYING(LAUNCHER_PVT_PID_SETD)
    m_PvtPID.SetD(PVT_D);
    END_RETRYING

    START_RETRYING(LAUNCHER_PVT_PID_SET_FEEDBACK_DEVICE)
    m_PvtPID.SetFeedbackDevice(m_PvtAbsEncoder);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_PvtAbsEncoder.SetInverted(true);

            if (m_PvtAbsEncoder.GetInverted() == true)
            {
                successful = true;
            }
        }

        if (successful)
        {
            std::cout << "Configured LAUNCHER_PVT_ABS_ENC_SET_INVERTED in " << retries << " retries" << std::endl;
        }
        else
        {
            std::cout << "Failed to configure LAUNCHER_PVT_ABS_ENC_SET_INVERTED in " << retries << " retries" << std::endl;
        }
    }

    START_RETRYING(PVT_ABS_ENC_SET_POSITION_CONVERSION_FACTOR)
    m_PvtAbsEncoder.SetPositionConversionFactor(LAUNCHER_PVT_ABS_ENC_CONVERSION_FACTOR);
    END_RETRYING
    START_RETRYING(PVT_ABS_ENC_SET_ZERO_OFFSET)
    m_PvtAbsEncoder.SetZeroOffset(LAUNCHER_ZERO_OFFSET);
    END_RETRYING

    std::cout << "Launcher flashing complete" << std::endl;


    ctre::phoenix6::configs::TalonFXConfiguration configs{};

    configs.Slot0.kP = FLYWHEEL_P;
    configs.Slot0.kI = FLYWHEEL_I;
    configs.Slot0.kD = FLYWHEEL_D;

    configs.MotionMagic.MotionMagicJerk = MAX_JERK;

    m_FlywheelBottom.SetControl(m_FlywheelTopFollower);
    
    m_FlywheelTop.GetConfigurator().Apply(configs);
    m_FlywheelBottom.GetConfigurator().Apply(configs);

    m_currentAngle = -100.0;
}

void LauncherHAL::SetFlywheelSpeed(double speed)
{   
    if (INVERT_FLYWHEEL)
    {
        speed = -speed;
    }

    units::angular_velocity::turns_per_second_t speed_tps = units::angular_velocity::turns_per_second_t(speed);
    ctre::phoenix6::controls::MotionMagicVelocityVoltage m_request{speed_tps};
        
    if (std::fabs(speed) > 1.0)
    {
        m_request.Acceleration = units::turns_per_second_squared_t(UP_MAX_ACC);
    }
    else
    {
        m_request.Acceleration = units::turns_per_second_squared_t(DOWN_MAX_ACC);
    }

    m_FlywheelTop.SetControl(m_request.WithVelocity(speed_tps));
}

void LauncherHAL::SetIndexerSpeed(double speed)
{
    if (INVERT_INDEXER)
    {
        m_indexerSpeed = -speed;
    }
    else
    {
        m_indexerSpeed = speed;
    }

    m_IndMotor.Set(m_indexerSpeed);
}

void LauncherHAL::SetAngle(double angle)
{
    if (angle > MAX_PIVOT_ANGLE)
    {
        angle = MAX_PIVOT_ANGLE;
    }
    else if (angle < MIN_PIVOT_ANGLE)
    {
        angle = MIN_PIVOT_ANGLE;
    }

    m_PvtPID.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);
}

void LauncherHAL::ProfiledMoveToAngle(double angle)
{
    if (std::fabs(m_currentAngle - angle) >= 1e-8)
    {
        m_profileState = 0;
        m_currentAngle = angle;
    }

    switch(m_profileState)
    {
     case 0: 
        {
            m_ProfileStartPos = GetAngle();

            m_Timer.Restart();

            m_profileState++;

            break;
        }
            

        case 1:
        {
            auto setPoint = m_Profile.Calculate(m_Timer.Get(),    
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_ProfileStartPos}, 0_deg_per_s},  
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{angle}, 0_deg_per_s}
            );

            SetAngle(setPoint.position.to<double>());

            if (m_Profile.IsFinished(m_Timer.Get())) {

                m_profileState++;

            }



            break;
        }

        case 2: 
        {

            m_Timer.Stop();

            m_profileState++;

            break;
        }

        
        default:
            break; 
    }
}

double LauncherHAL::GetAngle()
{
    return m_PvtAbsEncoder.GetPosition();
}

double LauncherHAL::GetFlywheelSpeed()
{
    return m_FlywheelTop.GetVelocity().GetValueAsDouble();
}

void LauncherHAL::ResetProfiledMoveState()
{
    // m_profileState = 0;
}