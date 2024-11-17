#include "subsystems/subsystemsManagers/IntakeManager.h"

namespace
{
    const double NORMAL_INTAKE_SPEED = 0.95;
    const double OUTAKE_SPEED = 0.7;
    const double AMP_POS = 25.361;
    const double GROUND_POS = 129.000;
    const double STOW_POS = 68.144;
    const double PSEUDO_STOW_POS = 104.671;
    const double OUTAKE_POS = 113.4; //change later
}

void IntakeManager::ResetIntake()
{
    m_goToGroundPos = false;
    m_goToStowPos = false;
    m_goToAmpPos = false;
    m_goToPseudoStowPos = false;
    m_goToOutakePos = false;
}

void IntakeManager::HandleInput(IntakeInput &input, IntakeOutput &output)
{
    if (input.runIntakeOutSlow)
    {
        m_intake.RunIntake(-0.15);
    }
    else if (input.runIntakeIn && !input.runIntakeOut)
    {
        m_intake.RunIntake(NORMAL_INTAKE_SPEED);
    }
    else if (input.runIntakeOut && !input.runIntakeIn)
    {
        m_intake.RunIntake(-OUTAKE_SPEED);
    } 
    else 
    {
        m_intake.RunIntake(0.0);
    }

 

    
    // std::vector<bool> inputs = {false, false, false, false, false, true};
    // std::vector<bool> ouputs(inputs.size(), false);

    // for (int i = 0; i < inputs.size() + 1; i ++) {
    //     if (inputs[i] == true) {
    //         int counts = std::count(ouputs.begin(), ouputs.end(), true);
    //         if (counts == 0) {
    //             ouputs.at(i) = true;
    //             break;
    //         }
                
                
    //     }
    // }
    
    // for (bool i: ouputs) {
    //     std::cout << i << ' ';
    // }
    


    if (input.manualMove > 0.001)
    {
        m_intake.ManualMovePivot(input.manualMove);
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
        m_goToOutakePos = false;
    }
    else if (input.goToStowPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = true;
        m_goToPseudoStowPos = false;
        m_goToOutakePos = false;
    } 
    else if (input.goToGroundPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = true;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
        m_goToOutakePos = false;
    }
    else if (input.goToAmpPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = true;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
        m_goToOutakePos = false;
    }
    else if (input.goToPseudoStowPos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = true;
        m_goToOutakePos = false;
    }
    else if (input.goToOutakePos)
    {
        m_intake.ResetProfiledMoveState();
        m_goToAmpPos = false;
        m_goToGroundPos = false;
        m_goToStowPos = false;
        m_goToPseudoStowPos = false;
        m_goToOutakePos = true;
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
    if (m_goToOutakePos)
    {
        m_intake.ProfiledMoveToAngle(OUTAKE_POS);
    }

    output.intakePos = IntakePos::UNKNOWN;
    double tolerance = 0.5;
    if (std::fabs(m_intake.GetAngle() - GROUND_POS) < tolerance)
    {
        output.intakePos = IntakePos::GROUND;
    }
    else if (std::fabs(m_intake.GetAngle() - AMP_POS) < 5.0)
    {
        output.intakePos = IntakePos::AMP;
    }
    else if (std::fabs(m_intake.GetAngle() - PSEUDO_STOW_POS) < tolerance)
    {
        output.intakePos = IntakePos::PSEUDO_STOW;
    }
    else if (std::fabs(m_intake.GetAngle() - STOW_POS) < tolerance)
    {
        output.intakePos = IntakePos::STOW;
    }
    else if (std::fabs(m_intake.GetAngle() - OUTAKE_POS) < tolerance)
    {
        output.intakePos = IntakePos::OUTAKE;
    }
}