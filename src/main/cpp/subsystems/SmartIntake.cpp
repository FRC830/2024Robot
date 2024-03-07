#include "subsystems/SmartIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

SmartIntake::SmartIntake()
{
    ResetSmartIntake();
}

void SmartIntake::ResetSmartIntake()
{
    m_SmartIntakeFlag = false;
    m_prevSmartIntake = false;
    
    m_SmartOutTakeFlag = false;
    m_prevSmartOutTake = false;
    
    m_SwitchModeFlag = false;
    m_prevSwitchMode = false;

    m_IntakeState = 10000;
    m_OutTakeState = 10000;

    m_centerNote = false;
    m_centerNoteState = 0;
}

void SmartIntake::HandleInput(RobotControlData& input){
    frc::SmartDashboard::PutBoolean("Launcher beam break", !m_beam_break.Get());
    input.smartIntakeInput.laser = !m_beam_break.Get();

    auto front_beam_break = !m_front_beam_break.Get();
    frc::SmartDashboard::PutBoolean("Launcher front beam break", front_beam_break);

    if (!m_prevSmartIntake && input.smartIntakeInput.smartIntake)
    {
        m_SmartIntakeFlag = !m_SmartIntakeFlag;
        m_SmartOutTakeFlag = false;
        m_IntakeState = 0;
        input.intakeInput.runIntakeOut = false;
        input.launcherInput.runIndexerBackward = false;
        input.launcherInput.runIndexerBackwardSlow = false;
        m_OutTakeState = 10000;
    }
    
    if (!m_prevSmartOutTake && input.smartIntakeInput.smartOutTake)
    {
        m_SmartOutTakeFlag = !m_SmartOutTakeFlag;
        m_SmartIntakeFlag = false;
        input.intakeInput.runIntakeIn = false;
        input.launcherInput.runIndexerForward = false;
        input.launcherInput.runIndexerBackwardSlow = false;
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
                input.intakeInput.goToGroundPos = true;
                input.launcherInput.goToStowPos = true;
                ++m_IntakeState;
        }
            break;
        case 1:
        {
            input.launcherInput.goToStowPos = false;
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
            input.launcherInput.runIndexerForward = true;
            if (input.smartIntakeInput.laser)
            {
                m_SmartIntakeFlag = false;
                m_IntakeState = 0;
                m_centerNote = true;
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
            input.intakeInput.runIntakeIn = false;
            if (!m_centerNote)
            {
                input.launcherInput.runIndexerForward = false;
            }
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

    if (m_centerNote)
    {
        switch (m_centerNoteState)
        {
        case 0:
        {
            m_timer.Stop();
            m_timer.Reset();
            m_timer.Start();

            input.launcherInput.runIndexerForward = true;

            ++m_centerNoteState;

            break;
        }
        case 1:
        {
            input.launcherInput.runIndexerForward = true;
            if (m_timer.Get() >= units::second_t(0.3))
            {
                m_timer.Stop();
                input.launcherInput.runIndexerForward = false;
                input.launcherInput.runIndexerBackwardSlow = true;
                ++m_centerNoteState;
            }

            break;
        }
        case 2:
        {
            if (!front_beam_break)
            {
                input.launcherInput.runIndexerBackwardSlow = false;
                ++m_centerNoteState;
            }

            break;
        }
        case 3:
        {
            m_centerNoteState = 0;
            m_centerNote = false;
            break;
        }
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
                input.launcherInput.goToStowPos = true;
                input.intakeInput.goToOutakePos = true;
                ++m_OutTakeState;
        }
            break;
        case 1:
        {
            input.launcherInput.goToStowPos = false;
            input.intakeInput.goToOutakePos = false;
            if (input.intakeOutput.intakePos == IntakePos::OUTAKE)
            {
                ++m_OutTakeState;
            }

            m_timer.Reset();
        }
            break;
        case 2:
        {
            input.intakeInput.runIntakeOut = true;
            input.launcherInput.runIndexerBackward = true;
            if (!input.smartIntakeInput.laser)
            {
                m_timer.Restart();
                m_OutTakeState++;
            }
        }
        case 3:
        {
            if (m_timer.Get() > units::second_t(0.04))
            {
                m_SmartOutTakeFlag = false;
                m_OutTakeState = 0;
                m_timer.Stop();
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
            input.intakeInput.runIntakeOut = false;
            input.launcherInput.runIndexerBackward = false;
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
