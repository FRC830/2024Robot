#include "subsystems/subsystemsManagers/ClimberManager.h"

namespace
{
    
}

void ClimberManager::HandleInput(ClimberInput &input)
{
    
    // FIXME: I'm not correct according to the laws of mathematics
    double controllerInput = ((input.controllerSpeed + m_deadzone)/(1-m_deadzone)) * m_multiplier;
    
    if (input.controllerSpeed > m_deadzone) 
    {
        m_climber.RunClimber(controllerInput);
    }
    else if (input.controllerSpeed < m_deadzone)
    {       
        m_climber.RunClimber(((input.controllerSpeed - m_deadzone)/(1-m_deadzone)) * m_multiplier);
    }
    else 
    {
        m_climber.RunClimber(0.0);
    }
    
}
