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



struct ASDF{

    int a;
    int b;

};

class AutoAimer{

    public: 
        AutoAimer(WPISwerveDrive& swerve);
        ~AutoAimer() = default; 

        
        void ResetState();

        void AutoAim();
        
    
    private: 
        WPISwerveDrive& m_Swerve;  
        double m_StartRobotHeading;
        int m_state = 0; 
        frc::Timer m_timer; 
        VisionConsumer m_vision;
        struct ASDF blue = {3, 4};
        struct ASDF red = {8, 7};
        frc::TrapezoidProfile<units::degrees> m_Profile{

                frc::TrapezoidProfile<units::degrees>::Constraints{360_deg_per_s, 50_deg_per_s_sq}  
                
        };

        void ProfiledMoveToDeg(double deg);

        double ar;
        double at;
        double br;
        double bt;

};