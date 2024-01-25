#pragma once
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Rotation3d.h>

struct GyroConfig;

class SwerveGyro
{
     public:
        SwerveGyro() = default;
        virtual ~SwerveGyro() = default;
        virtual void Configure(GyroConfig &config) = 0;
        virtual frc::Rotation3d GetYawPitchRoll() = 0;
        virtual frc::Rotation2d GetHeading() = 0;
        virtual frc::Rotation2d GetRawHeading() = 0;
        virtual bool GetInverted() = 0;
        virtual void SetInverted(bool inverted) = 0;
        virtual void SetZeroHeading(double zero_heading) = 0;

    private:
};