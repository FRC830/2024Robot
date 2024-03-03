/* #pragma once

#include <frc2/command/CommandHelper.h>
#include <LauncherManager.h>
#include "RobotControlData.h"

class VisionShoot : public frc2::CommandHelper<frc2::Command, VisionShoot>
{
    public:
        VisionShoot(RobotControlData &controlData);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;
    private:
        RobotControlData &m_controlData;
}; */