#include "LauncherManager.h"

namespace
{
    const double SUB_ANGLE;
    const double STOW_ANGLE;
    const double SUB_SPEED;
    const double INDEXER_SPEED;
}

void LauncherManager::HandleInput(LauncherInput &input)
{
    if (input.usevisionControl)
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

        if (m_goToStowPos)
        {
            m_launcher.ProfiledMoveToAngle(STOW_ANGLE);
            m_launcher.SetFlywheelSpeed(0.0);
        }
        if (m_goToSubPos)
        {
            m_launcher.ProfiledMoveToAngle(SUB_ANGLE);
            m_launcher.SetFlywheelSpeed(SUB_SPEED);
        }
    }

    if (input.runIndexer)
    {
        m_launcher.SetIndexerSpeed(INDEXER_SPEED);
    } 
    else 
    {
        m_launcher.SetIndexerSpeed(0.0);
    }
}