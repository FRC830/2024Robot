#include "LauncherHAL.h"

void LauncherHAL::Configure(LauncherHALConfig &config) {}

void LauncherHAL::SetFlywheelSpeed(double speed)
{   
    units::angular_velocity::turns_per_second_t speed_tps = units::angular_velocity::turns_per_second_t(speed);
    ctre::phoenix6::controls::VelocityVoltage m_request{speed_tps};
    m_FlywheelActMotorA.SetControl(m_request.WithVelocity(speed_tps));
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
    return m_FlywheelActMotorA.GetVelocity().GetValueAsDouble();
}

void LauncherHAL::ResetProfiledMoveState()
{
    m_profileState = 0;
}