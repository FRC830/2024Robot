#include "subsystems/subsystemsManagers/ClimberManager.h"

void ClimberManager::HandleInput(ClimberInput &input)
{
    
    double controllerInput = ((std::fabs(input.controllerSpeed) - m_deadzone)/(1-m_deadzone)) * m_multiplier;
    
    if (input.controllerSpeed > m_deadzone) 
    {
        m_climber.RunClimber(controllerInput);
    }
    else if (input.controllerSpeed < -(m_deadzone))
    {       
        m_climber.RunClimber(-controllerInput);
    }
    else 
    {
        m_climber.RunClimber(0.0);
    }
    
}