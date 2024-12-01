#include "ratpack/ProfiledMove.h"

ProfiledMove::ProfiledMove(RobotControlData& data){
    switch(m_turnState) 
    {

        case 0: 
        {
            
            m_timer.Restart();
            m_StartRobotHeading = data.autoAimInput.robotCurAngle;

            m_turnState++;

            break;
        }

        case 1: 
        {
            auto setVelocity = m_Profile.Calculate(m_timer.Get(),
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_StartRobotHeading}, 0_deg_per_s},
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_StartRobotHeading + data.autoAimInput.robotSetAngle}, 0_deg_per_s}
            );

            data.autoAimOutput.robotRotSpeed = -setVelocity.velocity.to<double>();

            if (m_Profile.IsFinished(m_timer.Get())) {

                m_turnState++;

            }

            break;

        }

        case 2:
        {

            m_timer.Stop();

            m_turnState++;

            break;

        }

        default:
            break;


    }
}