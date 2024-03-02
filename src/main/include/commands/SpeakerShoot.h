#pragma once

#include "subsystems/subsystemsManagers/LauncherManager.h"
#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"

class SpeakerShoot : public frc2::CommandHelper<frc2::Command, SpeakerShoot>
{
    public:
        SpeakerShoot(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        RobotControlData &m_controlData;
};