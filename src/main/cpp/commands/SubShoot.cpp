#include "commands/SubShoot.h"
#include "subsystems/SubSystemConfig.h"

SubShoot::SubShoot(RobotControlData &controlData) : m_controlData(controlData)
{
    m_execute_state = 0;
    m_isFinished_state = 0;
}

void SubShoot::Initialize()
{
    m_execute_state = 0;
    m_isFinished_state = 0;
    m_controlData.launcherInput.goToSubPos = false;
    m_controlData.launcherInput.runIndexerForward = false;
    m_timer.Stop();
    m_timer.Reset();
}

void SubShoot::Execute()
{
    switch (m_execute_state)
    {
        case 0:
        {
            m_controlData.launcherInput.goToSubPos = true;
            m_execute_state++;
            break;
        }
        case 1:
        {
            m_controlData.launcherInput.goToSubPos = false;
            m_execute_state++;
            break;
        }
        case 2:
        {
            if (std::fabs(m_controlData.launcherOutput.launcherAngle - SUB_ANGLE) < 0.5)
            {
                m_controlData.launcherInput.runIndexerForward = true;
                m_execute_state++;
            }

            break;
        }
        default:
        {
            break;
        }
    }
}

bool SubShoot::IsFinished()
{
    bool isFinished = false;

    switch (m_isFinished_state)
    {
        case 0:
        {
            if (!m_controlData.smartIntakeInput.laser)
            {
                m_timer.Start();
                m_isFinished_state++;
            }

            break;
        }
        case 1:
        {
            if (m_timer.Get() > units::second_t(0.1))
            {
                m_controlData.launcherInput.runIndexerForward = false;
                m_timer.Stop();
                m_timer.Reset();
                isFinished = true;
                m_isFinished_state++;
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

void SubShoot::End(bool interrupted) {}
