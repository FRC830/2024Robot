#pragma once
#include <frc/XboxController.h>
#include "RobotControlData.h"

class ControllerInterface
{
    public:
        ControllerInterface() = default;
        ~ControllerInterface() = default;
        void UpdateRobotControlData(RobotControlData &controlData);
    private:
        void UpdateIntakeInput(RobotControlData &controlData);
        void UpdateLauncherInput(RobotControlData &controlData);
        void UpdateSwerveInput(RobotControlData &controlData);
        void UpdateClimberInput(RobotControlData &controlData);

        frc::XboxController m_pilot{0};
        frc::XboxController m_copilot{1};
        double m_slowmodefactor = 0.5;
};