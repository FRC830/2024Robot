#pragma once
#include "Interfaces/SwerveGyro.h"
#include <AHRS.h>

struct GyroConfig 
{
    bool is_inverted;
    frc::Rotation2d zero_heading;
};

class NavXGyro : public SwerveGyro
{
    public:
        NavXGyro() = default;
        virtual ~NavXGyro() = default;
        virtual void Configure(GyroConfig &config) override;
        virtual frc::Rotation3d GetYawPitchRoll() override;
        virtual frc::Rotation2d GetHeading() override;
        virtual frc::Rotation2d GetRawHeading() override;
        virtual bool GetInverted() override;
        virtual void SetInverted(bool inverted) override;
        virtual void SetZeroHeading(double zero_heading) override;
    private:
        bool m_is_inverted;
        frc::Rotation2d m_zero_heading; // NavX Gyro should set a zero heading during automatic calibration
        AHRS* m_gyro;
};