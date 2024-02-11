#pragma once
#include <frc/XboxController.h>
#include "RobotControlData.h"

class ControllerInterface
{
    public:
        ControllerInterface();
        ~ControllerInterface();
        void UpdateRobotControlData(RobotControlData &controlData);
        void UpdateSwerveInput(RobotControlData &controlData);
    private:
        frc::XboxController m_pilot{0};
        frc::XboxController m_copilot{1};
        double m_slowmodefactor = 0.5;
};