#include "commands/SpeakerShoot.h"
#include "subsystems/SubSystemConfig.h"

SpeakerShoot::SpeakerShoot(RobotControlData &controlData) : m_controlData(controlData) {}

void SpeakerShoot::Initialize()
{
    m_controlData.launcherInput.goToSubPos = true;
}

void SpeakerShoot::Execute() {}

bool SpeakerShoot::IsFinished()
{
    bool isFinished = false;

    if(std::fabs(m_controlData.launcherOutput.launcherAngle - SUB_ANGLE) < 1.0)
    {
        isFinished = true;
    }

    return isFinished;
}

void SpeakerShoot::End(bool interrupted)
{
    m_controlData.launcherInput.goToSubPos = false;
    m_controlData.launcherInput.goToStowPos = true;
}

