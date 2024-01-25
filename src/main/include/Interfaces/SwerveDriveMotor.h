#pragma once

#include <frc/geometry/Rotation2d.h>
#include "units/velocity.h"

struct SwerveDriveMotorConfig;


class SwerveDriveMotor{
    public: 
        SwerveDriveMotor() = default;
        virtual ~SwerveDriveMotor() = default;
        virtual void Configure(SwerveDriveMotorConfig &config) = 0;
        virtual void SetVelocity(units::velocity::feet_per_second_t v) = 0; 
        virtual units::velocity::feet_per_second_t GetVelocity() = 0;
        virtual void SetIdleMode(bool m) = 0;
        virtual bool GetIdleMode() = 0; // just incase if we use motors other than the rev ones that use otehr than the rev stuff. idk 
        virtual units::foot_t GetPosition() = 0;

    private: 





};