#include "LauncherManager.h"

namespace
{
    const double SUB_ANGLE = 0.0;
    const double STOW_ANGLE = 0.0;
    const double SUB_SPEED = 0.0;
    const double INDEXER_SPEED = 0.0;
}

void LauncherManager::HandleInput(LauncherInput &input)
{
    if (input.useVisionControl)
    {
        if (!m_visionResetProfiledMoveState)
        {
            m_launcher.ResetProfiledMoveState();
            m_visionResetProfiledMoveState = true;
        }
        m_launcher.SetFlywheelSpeed(input.visionSpeedSetpoint);
        m_launcher.ProfiledMoveToAngle(input.visionAngleSetpoint);
    }
    else 
    {
        m_visionResetProfiledMoveState = false;
        if(input.goToStowPos){
            m_goToStowPos = true;
            m_goToSubPos = false;
            m_launcher.ResetProfiledMoveState();
        }
        else if (input.goToSubPos) {
            m_goToStowPos = false;
            m_goToSubPos = true;
            m_launcher.ResetProfiledMoveState();
        }
    }
}