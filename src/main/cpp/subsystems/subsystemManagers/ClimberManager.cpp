#include "subsystems/subsystemsManagers/ClimberManager.h"

void ClimberManager::HandleInput(ClimberInput &input)
{
    
    double controllerInput = ((std::fabs(input.controllerSpeed) - DEADZONE)/(1-DEADZONE)) * MULTIPLIER;
    
    if (input.controllerSpeed > DEADZONE) 
    {
        m_climber.RunClimber(controllerInput);
    }
    else if (input.controllerSpeed < -(DEADZONE))
    {       
        m_climber.RunClimber(-controllerInput);
    }
    else 
    {
        m_climber.RunClimber(0.0);
    }
    
}