#include "subsystems/subsystemsManagers/LauncherManager.h"
#include "subsystems/SubSystemConfig.h"

void LauncherManager::ResetLauncher()
{
    m_goToStowPos = false;
    m_goToSubPos = false;
    m_visionResetProfiledMoveState = false;
}

void LauncherManager::HandleInput(LauncherInput &launcherInput, LauncherOutput &launcherOutput, IntakeInput &intakeInput, IntakeOutput &intakeOutput)
{

    if (launcherInput.useVisionControl)
    {
        if (!m_visionResetProfiledMoveState)
        {
            m_launcher.ResetProfiledMoveState();
            m_visionResetProfiledMoveState = true;
            m_goToStowPos = false;
            m_goToSubPos = false;
        }

        m_launcher.SetFlywheelSpeed(launcherInput.visionSpeedSetpoint);
        m_launcher.ProfiledMoveToAngle(launcherInput.visionAngleSetpoint);
    }
    else 
    {
        if (m_visionResetProfiledMoveState)
        {
            m_launcher.SetFlywheelSpeed(0.0);
        }

        m_visionResetProfiledMoveState = false;


        if(launcherInput.goToStowPos){
            m_goToStowPos = true;
            m_goToSubPos = false;
            m_launcher.ResetProfiledMoveState();
        }
        else if (launcherInput.goToSubPos) {
            m_goToStowPos = false;
            m_goToSubPos = true;

            m_launcher.ResetProfiledMoveState();
        }

        if (m_goToStowPos)
        {
            m_launcher.ProfiledMoveToAngle(STOW_ANGLE);
            
            if ((intakeOutput.intakePos == IntakePos::GROUND && intakeInput.runIntakeIn) || (launcherInput.runIndexerBackwardSlow))
            {
                m_launcher.SetFlywheelSpeed(-10.0);
            }
            else
            {
                m_launcher.SetFlywheelSpeed(0.0);
            }
        }
        if (m_goToSubPos)
        {
            m_launcher.ProfiledMoveToAngle(SUB_ANGLE);
            m_launcher.SetFlywheelSpeed(SUB_SPEED);
        }
    }

    if (launcherInput.runIndexerBackwardSlow)
    {
        m_launcher.SetIndexerSpeed(-INDEXER_SLOW_SPEED);
    }
    else if (launcherInput.runIndexerForward && !launcherInput.runIndexerBackward)
    {
       
        m_launcher.SetIndexerSpeed(INDEXER_SPEED);
    } 
    else if (launcherInput.runIndexerBackward && !launcherInput.runIndexerForward) 
    {
        m_launcher.SetIndexerSpeed(-INDEXER_SPEED);
    }
    else
    {
        m_launcher.SetIndexerSpeed(0.0);
    }

    launcherOutput.flywheelSpeed = m_launcher.GetFlywheelSpeed();
    launcherOutput.launcherAngle = m_launcher.GetAngle();
}