#include "AutoAimer.h"

#include <frc/smartdashboard/SmartDashboard.h>


AutoAimer::AutoAimer(WPISwerveDrive& s)
    : m_Swerve(s)
{}

void AutoAimer::ProfiledMoveToDeg(double deg) {


    switch(m_state) 
    {

        case 0: 
        {
            
            m_timer.Restart();
            m_StartRobotHeading = m_Swerve.GetPose().Rotation().Degrees().to<double>();

            m_state++;

            break;
        }

        case 1: 
        {
            auto setVelocity = m_Profile.Calculate(m_timer.Get(),
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_StartRobotHeading}, 0_deg_per_s},
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_StartRobotHeading + deg}, 0_deg_per_s}
            );
            m_Swerve.Drive(0.0, 0.0, setVelocity.velocity.to<double>());

            if (m_Profile.IsFinished(m_timer.Get())) {

                m_state++;

            }

            break;

        }

        case 2:
        {

            m_timer.Stop();

            m_state++;

            break;

        }

        default:
            break;


    }


}

void AutoAimer::ResetState()
{
    m_state = 0;
}

void AutoAimer::AutoAim() {

    // ar = frc::SmartDashboard::GetNumber("ar", 0.0);
    // at = frc::SmartDashboard::GetNumber("at", 0.0);
    // br = frc::SmartDashboard::GetNumber("br", 0.0);
    bt = frc::SmartDashboard::GetNumber("bt", 0.0);
    
    // PolarCoords a = {ar, at};
    // PolarCoords b = {br, bt};


    // m_StartRobotHeading = m_Swerve.GetPose().Rotation().Degrees().to<double>();
    // // m_vision.Periodic();

    // // auto cur = frc::DriverStation::GetAlliance().value() == frc::DriverStation::Alliance::kRed ? red : blue;
    // // PolarCoords a = m_vision.GetPolarCoordForTagX(cur.a);
    // // PolarCoords b = m_vision.GetPolarCoordForTagX(cur.b);
    // PolarCoords c = m_vision.GetRobotToSpeaker(a, b, m_StartRobotHeading);
    ProfiledMoveToDeg(bt);

}