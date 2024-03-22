#include "commands/SmartIntakeCommand.h"

SmartIntakeCommand::SmartIntakeCommand(RobotControlData &controlData) 
: m_controlData(controlData)
{
    m_state = 0;
}

void SmartIntakeCommand::Initialize()
{
    if (!m_controlData.smartIntakeOutput.smartIntakeFlag)
    {
        m_controlData.smartIntakeInput.smartIntake = true;
    }
    
    m_state = 0;
}

void SmartIntakeCommand::Execute() {}

bool SmartIntakeCommand::IsFinished()
{
    bool isFinished = false;

    switch(m_state)
    {
        case 0:
        {
            if (m_controlData.intakeOutput.intakePos == IntakePos::GROUND)
            {
                m_state++;
            }
            
            break;
        }
        case 1:
        {
            if (m_controlData.intakeOutput.intakePos == IntakePos::PSEUDO_STOW)
            {
                isFinished = true;
                m_state++;
            }

            break;
        }
        default:
        {
            break;
        }
    }
    
    return isFinished;
}

void SmartIntakeCommand::End(bool interrupted) {
    m_controlData.smartIntakeInput.smartIntake = false;
}