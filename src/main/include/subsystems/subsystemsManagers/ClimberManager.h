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
    double m_deadzone = 0.05;
    double m_multiplier = 0.8;

    
};

