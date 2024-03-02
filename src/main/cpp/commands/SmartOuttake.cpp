#include "commands/SmartOuttake.h"

SmartOuttake::SmartOuttake(RobotControlData &controlData) : m_controlData(controlData) {}

void SmartOuttake::Initialize()
{
    m_controlData.smartIntakeInput.smartOutTake = true;
}

void SmartOuttake::Execute() {}

bool SmartOuttake::IsFinished()
{
    bool isFinished = false;

    if (m_controlData.intakeOutput.intakePos == IntakePos::AMP)
    {
        isFinished = true;
    }

    return isFinished;
}

void SmartOuttake::End(bool interrupted)
{
    m_controlData.smartIntakeInput.smartOutTake = false;
}