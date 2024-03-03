#include "commands/VisionShoot.h"

VisionShoot::VisionShoot(RobotControlData &controlData) : m_controlData(controlData) {}

void VisionShoot::Initialize() 
{
    m_controlData.autoAimInput.autoAim = true;
    m_timer.Stop();
    m_timer.Reset();
}

void VisionShoot::Execute() {}

bool VisionShoot::IsFinished() {
    // TODO: Replace timer with indicator that vision shot is over.
    bool isFinished = false;

    if (m_timer.Get() > units::second_t(3.0))
    {
        isFinished = true;
    }

    return isFinished;
}

void VisionShoot::End(bool interrupted) {}
