#pragma once

#include "subsystems/ClimberHAL.h"
#include "subsystems/SubSystemConfig.h"

struct ClimberInput
{
    double manualMove;
    double controllerSpeed;
};

class ClimberManager
{
public:
    void HandleInput(ClimberInput &input);

    
private:
    ClimberHAL m_climber;
    const double DEADZONE = 0.05;
    const double MULTIPLIER = 0.8;

    
};

