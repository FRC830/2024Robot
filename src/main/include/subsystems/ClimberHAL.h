#pragma once

#include <rev/CANSparkMax.h>

class ClimberHAL{
    public:
        void RunClimber(double controllerSpeed);
    private:
        rev::CANSparkMax m_climberMotorLeft = rev::CANSparkMax(2, rev::CANSparkMaxLowLevel::MotorType::kBrushless); 
        rev::CANSparkMax m_climberMotorRight = rev::CANSparkMax(2, rev::CANSparkMaxLowLevel::MotorType::kBrushless); 

};