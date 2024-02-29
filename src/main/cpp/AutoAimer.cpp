#include "AutoAimer.h"

#include <frc/smartdashboard/SmartDashboard.h>

AutoAimer::AutoAimer()
{
    m_lookup.emplace_back(AutoAimer::VisionSetPoint{36.0, 55.0, 150.0});
    m_lookup.emplace_back(AutoAimer::VisionSetPoint{240.0, 25.0, 350.0});

    frc::SmartDashboard::PutBoolean("use_manual_tune", false);
    frc::SmartDashboard::PutNumber("manual_launcher_pivot", 0.0);
    frc::SmartDashboard::PutNumber("manual_flywheel_speed", 0.0);
}


AutoAimer::VisionSetPoint AutoAimer::DetermineSetpoint(double dist) {

    //cond verify

    if (dist <= m_lookup.begin()->distance || dist > m_lookup.end()->distance)
     return AutoAimer::VisionSetPoint{dist, 0.0, 0.0};


    AutoAimer::VisionSetPoint a = m_lookup.at(0);
    AutoAimer::VisionSetPoint b = m_lookup.at(1);


    AutoAimer::VisionSetPoint ret = a;

    for (int i = 0; i < m_lookup.size(); i++) {

        b = m_lookup.at(i);

        if (a.distance < dist && b.distance > dist) {

            break; 

        } else {

            a = b;

        }

    }

    double ratio = (dist - a.distance) / (b.distance - a.distance);

    ret.flywheelSpeed = (ratio * (b.flywheelSpeed - a.flywheelSpeed)) + a.flywheelSpeed;
    ret.launcherAngle = (ratio * (b.launcherAngle - a.launcherAngle)) + a.launcherAngle;

    return ret;

}

void AutoAimer::TurnRobotToHeading(RobotControlData& data) {

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

            data.autoAimOutput.robotRotSpeed = setVelocity.velocity.to<double>();

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

void AutoAimer::MonitorLauncherAngle(RobotControlData& data) {

    switch (m_piviotState) {

        case 0: 
        {

            m_piviotState = std::fabs(data.launcherInput.visionAngleSetpoint - data.launcherOutput.launcherAngle) < 0.5 ? 1 : 0;
            break;

        }

        default: 
        {

            break;

        }

    }

}

void AutoAimer::MonitorLauncherFlyWheelSpeed(RobotControlData& data) {

    switch (m_flyWheelState){

        case 0:
        {
            auto setpoint = data.launcherInput.visionSpeedSetpoint;
            auto current = data.launcherOutput.flywheelSpeed;

            if (std::fabs(setpoint - current) < 0.1 * setpoint) {

                m_flyWheelState++;
                
            }

            break;
        }

        default: 
        {

            break;

        }

       
    }

}

void AutoAimer::HandleInput(RobotControlData& data) {

    if (data.autoAimInput.autoAim) {
        switch(m_state) {

            case 0: 
            {
                PolarCoords robotToSpeaker = m_vision.GetRobotToSpeaker(data.autoAimInput.robotCurAngle);
                
                data.autoAimInput.robotSetAngle = robotToSpeaker.theta;

                // vision lookup
                data.launcherInput.useVisionControl = true;

                //set launcher speed and angle in data.autoaim stuff
                AutoAimer::VisionSetPoint set = AutoAimer::DetermineSetpoint(robotToSpeaker.r);

                data.launcherInput.visionAngleSetpoint = set.launcherAngle;
                data.launcherInput.visionSpeedSetpoint = set.flywheelSpeed;

                if (frc::SmartDashboard::GetBoolean("use_manual_tune", false))
                {
                    data.launcherInput.visionAngleSetpoint = frc::SmartDashboard::GetNumber("manual_launcher_pivot", 0.0);
                    data.launcherInput.visionSpeedSetpoint = frc::SmartDashboard::GetNumber("manual_flywheel_speed", 0.0);
                }

                ++m_state;
                
                break;

            }
            case 1: 
            {
                TurnRobotToHeading(data);
                MonitorLauncherAngle(data);
                MonitorLauncherFlyWheelSpeed(data);

                if (m_turnState == 3 && m_flyWheelState != 0 && m_piviotState != 0)
                m_state++;

                break;
            }
            case 2:
            {
                data.launcherInput.runIndexerForward = true;
                break;
            }
            default: 
            {
                break;
            }
             

        }

    }
    else{

        m_state = 0; 
        m_turnState = 0;
        m_flyWheelState = 0; 
        m_piviotState = 0;
        data.launcherInput.useVisionControl = false;

    }

}