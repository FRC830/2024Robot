#pragma once

#include <frc2/command/CommandHelper.h>
#include "subsystems/subsystemsManagers/LauncherManager.h"
#include "RobotControlData.h"

class AmpShoot : public frc2::CommandHelper<frc2::Command, AmpShoot>
{
    public:
        AmpShoot(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        RobotControlData &m_controlData;
        int m_state;
        frc::Timer m_timer;
};