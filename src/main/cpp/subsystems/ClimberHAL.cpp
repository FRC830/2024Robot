#include "subsystems/ClimberHAL.h"

void ClimberHAL::RunClimber(double controllerSpeed)
{
    m_climberMotorLeft.Set(controllerSpeed);
    m_climberMotorRight.Set(-controllerSpeed);
}