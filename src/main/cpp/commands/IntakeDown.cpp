#include "commands/IntakeDown.h"

IntakeDown::IntakeDown(RobotControlData &controlData) : m_controlData(controlData) {
    m_state = 0;
}

void IntakeDown::Initialize()
{
    m_controlData.intakeInput.goToGroundPos = false;
    m_state = 0;
}

void IntakeDown::Execute() {
    switch (m_state)
    {
        case 0:
        {
            m_controlData.intakeInput.goToGroundPos = true;
            m_state++;
            break;
        }
        case 1:
        {
            m_controlData.intakeInput.goToGroundPos = false;
            m_state++;
            break;
        }
        default:
            break;
    }
}

bool IntakeDown::IsFinished()
{
    bool isFinished = false;

    if (m_state > 1)
    {
        isFinished = true;
    }

    return isFinished;
}

void IntakeDown::End(bool interrupted) {}