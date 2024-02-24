#include "subsystems/subsystemsManagers/LauncherManager.h"

namespace
{
    const double SUB_ANGLE = 55.0;
    const double STOW_ANGLE = 10.0;
    const double SUB_SPEED = 150.0;
    const double INDEXER_SPEED = 1.0;
}

void LauncherManager::ResetLauncher()
{
    m_goToStowPos = false;
    m_goToSubPos = false;
    m_visionResetProfiledMoveState = false;
}

void LauncherManager::HandleInput(LauncherInput &input, LauncherOutput &output)
{

    if (input.useVisionControl)
    {
        if (!m_visionResetProfiledMoveState)
        {
            m_launcher.ResetProfiledMoveState();
            m_visionResetProfiledMoveState = true;
            m_goToStowPos = false;
            m_goToSubPos = false;
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

    if (input.runIndexerForward && !input.runIndexerBackward)
    {
        m_launcher.SetIndexerSpeed(INDEXER_SPEED);
    } 
    else if (input.runIndexerBackward && !input.runIndexerForward) 
    {
        m_launcher.SetIndexerSpeed(-INDEXER_SPEED);
    }
    else
    {
        m_launcher.SetIndexerSpeed(0.0);
    }

    output.flywheelSpeed = m_launcher.GetFlywheelSpeed();
    output.launcherAngle = m_launcher.GetAngle();
}