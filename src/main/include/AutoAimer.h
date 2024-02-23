#pragma once
#include "WPISwerveDrive.h"
#include "VisionConsumer.h"


class AutoAimer{

    public: 
        AutoAimer(WPISwerveDrive& swerve);
        ~AutoAimer() = default; 
        VisionConsumer m_vision;
        WPISwerveDrive m_Swerve;
        void TurnChasisToDeg(double deg);
        bool AutoAim();
        
    
    private: 
        
        double degreesToTurn;


}