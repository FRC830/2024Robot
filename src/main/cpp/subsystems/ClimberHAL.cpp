#include "subsystems/ClimberHAL.h"

ClimberHAL::ClimberHAL() {
    m_climberMotorLeft.RestoreFactoryDefaults();
    m_climberMotorRight.RestoreFactoryDefaults();
    
    error = m_EncoderLeft.SetPositionConversionFactor(wheel_circumference); 

    m_climberMotorRight.Follow(m_climberMotorLeft, true);

    m_climberMotorLeft.EnableVoltageCompensation(VOLT_COMP);
    m_climberMotorRight.EnableVoltageCompensation(VOLT_COMP);
    
    m_climberMotorLeft.SetSmartCurrentLimit(CLIMBER_CURRENT_LIMIT);
    m_climberMotorRight.SetSmartCurrentLimit(CLIMBER_CURRENT_LIMIT);      

    m_climberMotorRight.BurnFlash();
    m_climberMotorLeft.BurnFlash();
    
}

void ClimberHAL::RunClimber(double controllerSpeed)
{
    double height = m_EncoderLeft.GetPosition();
    bool nextTooHigh = isNextRotationTooHigh(height);
    while(!nextTooHigh) {
        m_climberMotorLeft.Set(controllerSpeed);
    }
};

bool ClimberHAL::isNextRotationTooHigh(double height) {
    return (height+wheel_circumference)>maxHeight;
}
