#pragma once

#include <frc2/command/CommandHelper.h>
#include "subsystems/subsystemsManagers/IntakeManager.h"
#include "RobotControlData.h"

class IntakeDown : public frc2::CommandHelper<frc2::Command, IntakeDown>
{
    public:
        IntakeDown(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;
    private:
        RobotControlData &m_controlData;
        int m_state;
};