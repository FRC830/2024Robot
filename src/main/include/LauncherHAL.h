#pragma once

#include "SubSystemConfig.h"

struct LauncherHALConfig
{

};

class LauncherHAL
{
    public:    
        void Configure(LauncherHALConfig &config);
        void SetFlywheelSpeed(double speed);
        void SetIndexerSpeed(double speed);
        void ProfiledMoveToAngle(double angle);
        double GetAngle(); 
        double GetSpeed();
        void ResetProfiledMoveState();

    private:
        void SetAngle(double angle);

};