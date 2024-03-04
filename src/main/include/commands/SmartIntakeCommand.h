#pragma once

#include "subsystems/SmartIntake.h"
#include <frc2/command/CommandHelper.h>

class SmartIntakeCommand : public frc2::CommandHelper<frc2::Command, SmartIntakeCommand> {
    public:
        SmartIntakeCommand(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        RobotControlData &m_controlData;
        int m_state;
};
