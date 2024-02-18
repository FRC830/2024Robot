#include "subsystems/SmartIntake.h"

SmartIntake::SmartIntake()
{
    m_SmartIntakeFlag = false;
    m_prevSmartIntake = false;
    
    m_SmartOutTakeFlag = false;
    m_prevSmartOutTake = false;
    
    m_SwitchModeFlag = false;
    m_prevSwitchMode = false;

    m_IntakeState = 0;
    m_OutTakeState = 0;
}

void SmartIntake::HandleInput(RobotControlData& input){

    if (!m_prevSmartIntake && input.smartIntakeInput.smartIntake)
    {
        m_SmartIntakeFlag = !m_SmartIntakeFlag;
        m_SmartOutTakeFlag = false;
        m_IntakeState = 0;
        m_OutTakeState = 10000;
    }
    
    if (!m_prevSmartOutTake && input.smartIntakeInput.smartOutTake)
    {
        m_SmartOutTakeFlag = !m_SmartOutTakeFlag;
        m_SmartIntakeFlag = false;
        m_IntakeState = 10000;
        m_OutTakeState = 0;
    }

    if (!m_prevSwitchMode && input.smartIntakeInput.switchMode)
    {
        m_SwitchModeFlag = !m_SwitchModeFlag;
    }

    //SmartIntake switch stuff
    if (m_SmartIntakeFlag)
    {
        switch (m_IntakeState)
        {
        case 0:
        {
                /* code */
                input.intakeInput.goToGroundPos = true;
                ++m_IntakeState;
        }
            break;
        case 1:
        {
            input.intakeInput.goToGroundPos = false;
            if (input.intakeOutput.intakePos == IntakePos::GROUND)
            {
                ++m_IntakeState;
            }
        }
            break;
        case 2:
        {
            input.intakeInput.runIntakeIn = true;
            if (input.smartIntakeInput.laser){
                input.intakeInput.runIntakeIn = false;
                input.intakeInput.goToPseudoStowPos = true;
                ++m_IntakeState;
            }
            
        }
            break;
        case 3:
        {
            input.intakeInput.goToPseudoStowPos = false;
            if (input.intakeOutput.intakePos == IntakePos::PSEUDO_STOW)
            {
                ++m_IntakeState;
            }
        }
            break;
        default:
            break;
        }
    }
    else
    {
        switch (m_IntakeState)
        {
        case 0:
        {
                /* code */
                input.intakeInput.runIntakeIn = false;
                input.intakeInput.goToPseudoStowPos = true;
                ++m_IntakeState;
        }
            break;
        case 1:
        {
            input.intakeInput.goToPseudoStowPos = false;
            if (input.intakeOutput.intakePos == IntakePos::PSEUDO_STOW)
            {
                ++m_IntakeState;
            }
        }
            break;
        default:
            break;
        }
    }


    if (m_SmartOutTakeFlag)
    {
        switch (m_OutTakeState)
        {
        case 0:
        {
                /* code */
                input.intakeInput.goToGroundPos = true;
                ++m_OutTakeState;
        }
            break;
        case 1:
        {
            input.intakeInput.goToGroundPos = false;
            if (input.intakeOutput.intakePos == IntakePos::GROUND)
            {
                ++m_OutTakeState;
            }
        }
            break;
        case 2:
        {
            input.intakeInput.runIntakeOut = true;
            if (input.smartIntakeInput.laser){
                input.intakeInput.runIntakeOut = false;
                input.intakeInput.goToPseudoStowPos = true;
                ++m_OutTakeState;
            }
            
        }
            break;
        case 3:
        {
            input.intakeInput.goToPseudoStowPos = false;
            if (input.intakeOutput.intakePos == IntakePos::PSEUDO_STOW)
            {
                ++m_OutTakeState;
            }
        }
            break;
        default:
            break;        
        }
    }
    else
    {
        
        switch (m_OutTakeState)
        {
        case 0:
        {
                /* code */
                input.intakeInput.runIntakeOut = false;
                input.intakeInput.goToPseudoStowPos = true;
                ++m_OutTakeState;
        }
            break;
        case 1:
        {
            input.intakeInput.goToPseudoStowPos = false;
            if (input.intakeOutput.intakePos == IntakePos::PSEUDO_STOW)
            {
                ++m_OutTakeState;
            }
        }
            break;
        default:
            break;
        }
    }
    
        // needs to go at the bottom
    m_prevSmartIntake = input.smartIntakeInput.smartIntake;
    m_prevSmartOutTake = input.smartIntakeInput.smartOutTake;
    m_prevSwitchMode = input.smartIntakeInput.switchMode;
}
