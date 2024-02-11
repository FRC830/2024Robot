#pragma once

#include <rev/CANSparkMax.h>
#include "Interfaces/SwerveDriveMotor.h"
#include "units/velocity.h"

struct SwerveDriveMotorConfig {
    int motorID;
    bool inverted;
    rev::CANSparkMax *motor;
    rev::SparkRelativeEncoder *encoder;
    rev::SparkPIDController *PID;
    rev::CANSparkMax::IdleMode idleMode; 
    double p;
    double i;
    double d;
    double ff;
    double ratio;
    units::velocity::meters_per_second_t maxSpeed;
    double correction_factor;
    double drive_motor_current_limit;
    double swerve_voltage_compensation;
};

class NeoDriveMotor : public SwerveDriveMotor {

    public:
        NeoDriveMotor() = default; 
        virtual ~NeoDriveMotor() = default;
        virtual void Configure(SwerveDriveMotorConfig &config) override; 
        virtual void SetVelocity(units::velocity::feet_per_second_t v) override; 
        virtual units::velocity::feet_per_second_t GetVelocity() override; 
        virtual void SetIdleMode(bool m) override;
        virtual bool GetIdleMode() override; // just incase if we use motors other than the rev ones that use otehr than the rev stuff. idk 
        virtual units::foot_t GetPosition() override;



    private: 
        int m_motorID;
        bool m_inverted;
        rev::CANSparkMax *m_motor;
        rev::SparkRelativeEncoder *m_encoder;
        rev::SparkPIDController *m_PID;
        units::velocity::meters_per_second_t m_MaxSpeed;
        double m_correction_factor;
};
