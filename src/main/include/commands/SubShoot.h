#pragma once

#include "subsystems/subsystemsManagers/LauncherManager.h"
#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"

class SubShoot : public frc2::CommandHelper<frc2::Command, SubShoot>
{
    public:
        SubShoot(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        RobotControlData &m_controlData;
        int m_execute_state;
        int m_isFinished_state;
        frc::Timer m_timer;
};