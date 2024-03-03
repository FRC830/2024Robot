#include "commands/SubShoot.h"
#include "subsystems/SubSystemConfig.h"

SubShoot::SubShoot(RobotControlData &controlData) : m_controlData(controlData) 
{
    m_state = 0;
}

void SubShoot::Initialize()
{
    m_state = 0;
    m_controlData.launcherInput.goToSubPos = false;
}

void SubShoot::Execute() {
    switch (m_state)
    {
    case 0:
    {
        m_controlData.launcherInput.goToSubPos = true;
        m_state++;
        break;
    }
    case 1:
    {
        m_controlData.launcherInput.goToSubPos = false;
        m_state++;
        break;
    }
    case 2:
    {
        if (std::fabs(m_controlData.launcherOutput.launcherAngle - SUB_ANGLE) < 10.0)
        {
            m_state++;
        }
        
        break;
    }
    case 3:
    {
        m_controlData.launcherInput.goToStowPos = false;
        m_state++;
    }
    case 4:
    {
        m_controlData.launcherInput.goToStowPos = true;
        m_state++;
    }
    case 5:
    {
        m_controlData.launcherInput.goToStowPos = false;
        m_state++;
    }
    default:
        break;
    }
}

bool SubShoot::IsFinished()
{
    bool isFinished = false;

    if (std::fabs(m_controlData.launcherOutput.launcherAngle - STOW_ANGLE) < 0.25)
    {
        isFinished = true;
    }

    return isFinished;
}

void SubShoot::End(bool interrupted) {}

