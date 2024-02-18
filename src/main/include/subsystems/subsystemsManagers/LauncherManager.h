#pragma once

#include "subsystems/LauncherHAL.h"

struct LauncherInput
{
    bool useVisionControl;
    double visionAngleSetpoint;
    double visionSpeedSetpoint;
    bool goToStowPos;
    bool goToSubPos;
    bool runIndexerForward; //Indexer is the little "kick" to help the Note transfer from the Intake to the Launcher
    bool runIndexerBackward;
};

struct LauncherOutput
{
    double launcherAngle;
    double flywheelSpeed;
};

class LauncherManager
{
    public:
        void HandleInput(LauncherInput &input, LauncherOutput &output);
        void ResetLauncher();
        
    private:
        LauncherHAL m_launcher;
        bool m_goToStowPos;
        bool m_goToSubPos;
        bool m_visionResetProfiledMoveState = false;
};