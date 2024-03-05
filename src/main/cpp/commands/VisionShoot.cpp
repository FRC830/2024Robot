#include "commands/VisionShoot.h"

VisionShoot::VisionShoot(RobotControlData &controlData) : m_controlData(controlData) {
    m_state = 0;
}

void VisionShoot::Initialize() 
{
    m_controlData.autoAimInput.autoAim = true;
    m_state = 0;
    m_timer.Stop();
    m_timer.Reset();
}

void VisionShoot::Execute() {}

bool VisionShoot::IsFinished() {
    bool isFinished = false;

    switch (m_state)
    {
        case 0:
        {
            if (!m_controlData.smartIntakeInput.laser)
            {
                m_timer.Start();
                m_state++;
            }

            break;
        }
        case 1:
        {
            if (m_timer.Get() > units::second_t(0.1))
            {
                m_timer.Stop();
                m_timer.Reset();
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

void VisionShoot::End(bool interrupted) {
    m_controlData.autoAimInput.autoAim = false;
}
