#pragma once

#include "subsystems/SmartIntake.h"
#include <frc2/command/CommandHelper.h>

class SmartOuttake : public frc2::CommandHelper<frc2::Command, SmartOuttake>
{
    public:
        SmartOuttake(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        RobotControlData &m_controlData;
};