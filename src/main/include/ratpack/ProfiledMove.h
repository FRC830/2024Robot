#pragma once

#include <frc/trajectory/TrapezoidProfile.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class ProfiledMove{
    public:
    ProfiledMove(RobotControlData& data); //fix this later
    private:
    int m_turnState = 0;

}
