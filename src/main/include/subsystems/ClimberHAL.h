#pragma once

#include <rev/CANSparkMax.h>
#include <subsystems/SubSystemConfig.h>
#include <rev/SparkMaxAlternateEncoder.h>

class ClimberHAL{
    public:
        ClimberHAL();
        void RunClimber(double controllerSpeed);
        bool isNextRotationTooHigh(double height);
    private:
        rev::CANSparkMax m_climberMotorLeft = rev::CANSparkMax(CLIMBER_MOTOR_LEFT, rev::CANSparkLowLevel::MotorType::kBrushless); 
        rev::CANSparkMax m_climberMotorRight = rev::CANSparkMax(CLIMBER_MOTOR_RIGHT, rev::CANSparkLowLevel::MotorType::kBrushless); 

        rev::SparkRelativeEncoder m_EncoderRight = m_climberMotorRight.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 42);
        rev::SparkRelativeEncoder m_EncoderLeft = m_climberMotorLeft.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 1);
    
        rev::REVLibError error;

        //Constants
        const double WHEEL_RADIUS = 1.5;
        const double WHEEL_CIRCUMFERENCE = 2.0 * 3.14 * WHEEL_RADIUS;
        const double MAXHEIGHT = (3.0 + 8.0/12.0) * 12.0; //inches     
};