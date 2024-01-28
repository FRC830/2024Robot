#include "ClimberHAL.h"

void ClimberHAL::RunClimber(double controllerSpeed)
{
    m_climberMotorLeft.set(controllerSpeed)
    m_climberMotorRight.set(-controllerSpeed)
}