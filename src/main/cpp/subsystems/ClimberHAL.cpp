#include "subsystems/ClimberHAL.h"

ClimberHAL::ClimberHAL() {
    error = m_EncoderLeft.SetPositionConversionFactor(wheel_circumference); 
}

void ClimberHAL::RunClimber(double controllerSpeed)
{
    while(!isNextRotationTooHigh(getCurrentHeight(m_EncoderLeft.GetPosition()))) {
        m_climberMotorLeft.Set(controllerSpeed);
        m_climberMotorRight.Set(-controllerSpeed);
    }
};

double ClimberHAL::getRotations() {
    double rotations = m_EncoderLeft.GetPosition();
    return rotations;
}
double ClimberHAL::getCurrentHeight(double rotations) {
    return rotations * getChangeInHeight(rotations);
}
bool ClimberHAL::isNextRotationTooHigh(double height) {
    return height+wheel_circumference>maxHeight;
}
double ClimberHAL::getChangeInHeight(double rotations) {
    return wheel_circumference * rotations;
}