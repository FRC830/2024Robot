#include "subsystems/LauncherHAL.h"

LauncherHAL::LauncherHAL()
{
    m_PvtMotor.RestoreFactoryDefaults();
    m_IndMotor.RestoreFactoryDefaults();
    m_PvtMotor.EnableVoltageCompensation(VOLT_COMP);
    m_IndMotor.EnableVoltageCompensation(VOLT_COMP);

    m_PvtPID.SetP(PVT_P);
    m_PvtPID.SetP(PVT_I);
    m_PvtPID.SetP(PVT_D);

    m_PvtPID.SetPositionPIDWrappingEnabled(false);

    m_PvtAbsEncoder.SetInverted(true);
    m_PvtAbsEncoder.SetPositionConversionFactor(LAUNCHER_PVT_ABS_ENC_CONVERSION_FACTOR);
    m_PvtAbsEncoder.SetZeroOffset(ZERO_OFFSET);

    m_PvtPID.SetFeedbackDevice(m_PvtAbsEncoder);

    m_PvtMotor.SetSmartCurrentLimit(LAUNCHER_PVT_CURRENT_LIMIT);
    m_IndMotor.SetSmartCurrentLimit(LAUNCHER_IND_CURRENT_LIMIT);

    m_PvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    ctre::phoenix6::configs::TalonFXConfiguration configs{};

    configs.Slot0.kP = FLYWHEEL_P;
    configs.Slot0.kI = FLYWHEEL_I;
    configs.Slot0.kD = FLYWHEEL_D;

    m_FlywheelBottom.SetControl(m_FlywheelTopFollower);

    m_FlywheelTop.SetInverted(INVERT_FLYWHEEL);
    
    m_FlywheelTop.GetConfigurator().Apply(configs);
    m_FlywheelBottom.GetConfigurator().Apply(configs);

    m_PvtMotor.BurnFlash();
    m_IndMotor.BurnFlash();
}

void LauncherHAL::SetFlywheelSpeed(double speed)
{   
    if (std::fabs(speed) > 1.0)
    {
        units::angular_velocity::turns_per_second_t speed_tps = units::angular_velocity::turns_per_second_t(speed);
        ctre::phoenix6::controls::VelocityVoltage m_request{speed_tps};
        m_FlywheelTop.SetControl(m_request.WithVelocity(speed_tps));
    }
    else
    {
        ctre::phoenix6::controls::DutyCycleOut m_request{0.0};
        m_FlywheelTop.SetControl(m_request.WithOutput(0.0));
    }
}

void LauncherHAL::SetIndexerSpeed(double speed)
{
    m_indexerSpeed = speed;

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
            frc::TrapezoidProfile<units::meters>::State{units::meter_t{m_ProfileStartPos}, 0_mps},  
            frc::TrapezoidProfile<units::meters>::State{units::meter_t{angle}, 0_mps}
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
    m_profileState = 0;
}