#include "subsystems/LauncherHAL.h"
LauncherHAL::LauncherHAL()
{

    m_FlywheelActMotorB.SetControl(m_FlywheelActMtrBFollower);

    m_PvtMotor.RestoreFactoryDefaults();
    m_IndMotor.RestoreFactoryDefaults();
    m_PvtMotor.EnableVoltageCompensation(VOLT_COMP);
    m_IndMotor.EnableVoltageCompensation(VOLT_COMP);

    m_PvtPID.SetP(PVT_P);
    m_PvtPID.SetP(PVT_I);
    m_PvtPID.SetP(PVT_D);

    m_PvtMotor.SetSmartCurrentLimit(LAUNCHER_PVT_CURRENT_LIMIT);
    m_IndMotor.SetSmartCurrentLimit(LAUNCHER_IND_CURRENT_LIMIT);

    ctre::phoenix6::configs::TalonFXConfiguration configs{};

    configs.Slot0.kP = FLYWHEEL_P;
    configs.Slot0.kI = FLYWHEEL_I;
    configs.Slot0.kD = FLYWHEEL_D;

    // Need to implement voltage compensation for flywheel actuator motors
    /* ctre::phoenix6::controls::VoltageOut m_request{units::volt_t(VOLT_COMP)};
    m_FlywheelActMotorA.SetControl(m_request.WithOutput(units::volt_t(VOLT_COMP)));
    m_FlywheelActMotorB.SetControl(m_request.WithOutput(units::volt_t(VOLT_COMP))); */

    m_FlywheelActMotorA.GetConfigurator().Apply(configs);

    m_PvtMotor.BurnFlash();
    m_IndMotor.BurnFlash();
}

void LauncherHAL::SetFlywheelSpeed(double speed)
{   
    units::angular_velocity::turns_per_second_t speed_tps = units::angular_velocity::turns_per_second_t(speed);
    ctre::phoenix6::controls::VelocityDutyCycle m_request{speed_tps};
    m_FlywheelActMotorA.SetControl(m_request.WithVelocity(speed_tps));
    m_FlywheelActMotorB.SetControl(m_request.WithVelocity(speed_tps));
}

void LauncherHAL::SetIndexerSpeed(double speed)
{
    m_indexerSpeed = speed;

    m_IndMotor.Set(m_indexerSpeed);
}

void LauncherHAL::SetAngle(double angle)
{
    auto setPoint = angle * (1.0 / LAUNCHER_PVT_POS_TO_DEG); 

    m_PvtPID.SetReference(setPoint, rev::CANSparkMax::ControlType::kPosition);
}

void LauncherHAL::ProfiledMoveToAngle(double angle)
{
    SetAngle(angle);

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
    return m_PvtEncoder.GetPosition() * LAUNCHER_PVT_POS_TO_DEG;
}

double LauncherHAL::GetSpeed()
{
    return m_indexerSpeed;
}

void LauncherHAL::ResetProfiledMoveState()
{
    m_profileState = 0;
}