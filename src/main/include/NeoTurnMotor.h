#pragma once

#include "Interfaces/SwerveTurnMotor.h"
#include "Interfaces/SwerveAbsoluteEncoder.h"
#include "rev/CANSparkMax.h"

struct SwerveTurnMotorConfig{
    SwerveAbsoluteEncoder *absouluteEncoder; 
    int deviceID;
    bool inverted; 
    rev::CANSparkMax *turn_motor; 
    rev::SparkMaxRelativeEncoder *relative_Encoder;
    rev::SparkMaxPIDController *PID;
    double p;
    double i;
    double d;
    double ff;
    double ratio;
};

class NeoTurnMotor : public SwerveTurnMotor {

    public:
        NeoTurnMotor() = default;
        virtual ~NeoTurnMotor() = default;
        virtual void Configure(SwerveTurnMotorConfig &config) override;
        virtual void SetRotation(frc::Rotation2d deg) override; 
        virtual frc::Rotation2d GetRotation() override; 
        virtual bool GetInverted() override; 
        virtual void SetInverted(bool invert) override; 
        virtual void ForceTurnDirectionCW() override; 
        virtual void ForceTurnDirectionCCW() override; 

    private: 
       SwerveAbsoluteEncoder *m_AbsouluteEncoder;
       rev::CANSparkMax *m_turn_motor; 
       rev::SparkMaxRelativeEncoder *m_relative_Encoder;
       rev::SparkMaxPIDController *m_PID; 
       double m_pastCommandAngle;
};