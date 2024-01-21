#pragma once

#include "LauncherHAL.h"

struct LauncherInput
{
    bool useVisionControl;
    double visionAngleSetpoint;
    double visionSpeedSetpoint;
    bool goToStowPos;
    bool goToSubPos;
    bool runIndexer; //Indexer is the little "kick" to help the Note transfer from the Intake to the Launcher
};

class LauncherManager
{
public:
    void HandleInput(LauncherInput &input);

private:
    LauncherHAL m_launcher;
    bool m_goToStowPos;
    bool m_goToSubPos;
    bool m_visionResetProfiledMoveState = false;
};