#include "subsystems/ClimberHAL.h"

ClimberHAL::ClimberHAL() {
    m_climberMotorLeft.RestoreFactoryDefaults();
    error = m_EncoderLeft.SetPositionConversionFactor(WHEEL_CIRCUMFERENCE); 
    m_climberMotorLeft.SetInverted(INVERT_CLIMBER_MOTOR_LEFT);
    m_climberMotorLeft.BurnFlash();
}

void ClimberHAL::RunClimber(double controllerSpeed)
{
    double height = m_EncoderLeft.GetPosition();
    bool nextTooHigh = isNextRotationTooHigh(height);
    while(!nextTooHigh) {
        m_climberMotorLeft.Set(controllerSpeed);
        m_climberMotorRight.Set(-controllerSpeed);
    }
};

bool ClimberHAL::isNextRotationTooHigh(double height) {
    return (height+WHEEL_CIRCUMFERENCE)>MAXHEIGHT;
}
