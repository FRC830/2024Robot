#pragma once

#include <rev/CANSparkMax.h>
#include <frc/geometry/Rotation2d.h>


struct SwerveTurnMotorConfig;


class SwerveTurnMotor{

    public: 
        SwerveTurnMotor() = default;
        virtual ~SwerveTurnMotor() = default;
        virtual void Configure(SwerveTurnMotorConfig &config) = 0;
        virtual void SetRotation(frc::Rotation2d deg) = 0; 
        virtual frc::Rotation2d GetRotation() = 0; 
        virtual bool GetInverted() = 0; 
        virtual void SetInverted(bool invert) = 0; 
        virtual void ForceTurnDirectionCW() = 0; 
        virtual void ForceTurnDirectionCCW() = 0; 
        
        const double ratio = 1.4933333333333;


    private: 


};
