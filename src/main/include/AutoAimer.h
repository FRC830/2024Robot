#pragma once
#include "WPISwerveDrive.h"
#include "VisionConsumer.h"
#include <units/length.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/acceleration.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/Timer.h>
#include <frc/DriverStation.h>
#include "RobotControlData.h"
#include <vector>



struct VisionSetPoint{
    double distance;
    double launcherAngle;
    double flywheelSpeed;
};


class AutoAimer{

    public: 

    struct VisionSetPoint{
        double distance;
        double launcherAngle;
        double flywheelSpeed;
    };
    
        AutoAimer();
        ~AutoAimer() = default; 
        
        void HandleInput(RobotControlData& data);
        

        
    
    private: 

        
        void TurnRobotToHeading(RobotControlData& data);
        void MonitorLauncherAngle(RobotControlData& data);
        void MonitorLauncherFlyWheelSpeed(RobotControlData& data);
       
        struct VisionSetPoint DetermineSetpoint(double dist);

        std::vector<VisionSetPoint> m_lookup;

        double m_StartRobotHeading;
        int m_state = 0; 
        int m_turnState = 0;
        int m_flyWheelState = 0; 
        int m_piviotState = 0;
        frc::Timer m_timer; 
        VisionConsumer m_vision;
        frc::TrapezoidProfile<units::degrees> m_Profile{

                frc::TrapezoidProfile<units::degrees>::Constraints{360_deg_per_s, 50_deg_per_s_sq}  
                
        };


        double ar;
        double at;
        double br;
        double bt;

};