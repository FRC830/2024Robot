#pragma once

#include "subsystems/LauncherHAL.h"
#include "subsystems/subsystemsManagers/IntakeManager.h"

struct LauncherInput
{
    bool useVisionControl;
    double visionAngleSetpoint;
    double visionSpeedSetpoint;
    double compare;
    bool goToStowPos;
    bool goToSubPos;
    bool runIndexerForward; //Indexer is the little "kick" to help the Note transfer from the Intake to the Launcher
    bool runIndexerBackward;
    bool runIndexerBackwardSlow;
    bool goToHoardePos;
};

struct LauncherOutput
{
    double launcherAngle;
    double flywheelSpeed;
};

class LauncherManager
{
    public:
        void HandleInput(LauncherInput &launcherInput, LauncherOutput &launcherOutput, IntakeInput &intakeInput, IntakeOutput &intakeOutput);
        void ResetLauncher();
        
    private:
        LauncherHAL m_launcher;
        bool m_goToStowPos;
        bool m_goToSubPos;
        bool m_goToHoardePos;
        bool m_visionResetProfiledMoveState = false;
};