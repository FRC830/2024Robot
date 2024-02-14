#include "subsystems/subsystemsManagers/IntakeManager.h"

namespace
{
    const double NORMAL_INTAKE_SPEED = 0.95;
    const double AMP_POS = 72.686;
    const double GROUND_POS = 182.315;
    const double STOW_POS = 119.375;
    const double PSEUDO_STOW_POS = 153.105;
}

void IntakeManager::HandleInput(IntakeInput &input)
{
    if (input.runIntakeIn && !input.runIntakeOut)
    {
        m_intake.RunIntake(NORMAL_INTAKE_SPEED);
    }
    else if (input.runIntakeOut && !input.runIntakeIn)
    {
        m_intake.RunIntake(-NORMAL_INTAKE_SPEED);
    } 
    else 
    {
        m_intake.RunIntake(0.0);
    }
    if (input.manualMove > 0.001)
    {
        m_intake.ManualMovePivot(input.manualMove);
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
    }
    else if (input.goToStowPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = true;
        m_goToPseudoStowPos = false;
    } 
    else if (input.goToGroundPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = true;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
    }
    else if (input.goToAmpPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = true;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
    }
    else if (input.goToPseudoStowPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = true;
    }
   
    if (m_goToAmpPos)
    {
        m_intake.ProfiledMoveToAngle(AMP_POS);
    }
    if (m_goToGroundPos)
    {
        m_intake.ProfiledMoveToAngle(GROUND_POS);
    }
    if (m_goToStowPos)
    {
        m_intake.ProfiledMoveToAngle(STOW_POS);
    }
    if (m_goToPseudoStowPos)
    {
        m_intake.ProfiledMoveToAngle(PSEUDO_STOW_POS);
    }
}