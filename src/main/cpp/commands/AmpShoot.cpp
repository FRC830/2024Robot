#include "commands/AmpShoot.h"

AmpShoot::AmpShoot(RobotControlData &controlData) : m_controlData(controlData) 
{
    m_state = 0;
}

void AmpShoot::Initialize()
{
    m_controlData.intakeInput.goToAmpPos = true;
    m_state = 0;
    m_timer.Stop();
    m_timer.Reset();
}

void AmpShoot::Execute() {
    switch (m_state)
    {
        case 0:
        {
            if (m_controlData.intakeOutput.intakePos == IntakePos::AMP)
            {
                m_controlData.intakeInput.runIntakeIn = true;
                m_timer.Start();
                m_state++;
            }

            break;
        }
        case 1:
        {
            if (m_timer.Get() > units::second_t(0.2))
            {
                m_timer.Stop();
                m_timer.Reset();
                m_controlData.intakeInput.runIntakeIn = false;
                m_controlData.intakeInput.goToAmpPos = false;
                m_controlData.intakeInput.goToPseudoStowPos = true;
                m_state++;
            }

            break;
        }
        default:
        {
            break;
        }
    }
}

bool AmpShoot::IsFinished()
{
    bool isFinished = false;

    if (m_controlData.intakeOutput.intakePos == IntakePos::PSEUDO_STOW)
    {
        m_controlData.intakeInput.goToPseudoStowPos = false;
        isFinished = true;
    }

    return isFinished;
}

void AmpShoot::End(bool interrupted) {}