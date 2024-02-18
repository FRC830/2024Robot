#pragma once

#include <rev/CANSparkMax.h>
#include <subsystems/SubSystemConfig.h>
#include <rev/SparkMaxAlternateEncoder.h>

class ClimberHAL{
    public:
        ClimberHAL();
        void RunClimber(double controllerSpeed);

        double get(double rotations);
        double getRotations();
        double getCurrentHeight(double rotations);
        double getChangeInHeight(double rotations);
        bool isNextRotationTooHigh(double height);
    private:
        rev::CANSparkMax m_climberMotorLeft = rev::CANSparkMax(CLIMBER_MOTOR_LEFT, rev::CANSparkMaxLowLevel::MotorType::kBrushless); 
        rev::CANSparkMax m_climberMotorRight = rev::CANSparkMax(CLIMBER_MOTOR_RIGHT, rev::CANSparkMaxLowLevel::MotorType::kBrushless); 

        rev::SparkRelativeEncoder m_EncoderRight = m_climberMotorRight.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 1);
        rev::SparkRelativeEncoder m_EncoderLeft = m_climberMotorLeft.GetEncoder(rev::SparkRelativeEncoder::Type::kHallSensor, 1);
    
        rev::REVLibError error;

        //Constants
        const double wheel_radius = 1.5;
        const double wheel_circumference = 2 * 3.14 * wheel_radius;
        const double maxHeight = (3 + 8/12) * 12; //inches     
};