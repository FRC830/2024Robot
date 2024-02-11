#pragma once
#include <frc/geometry/Rotation2d.h>

struct AbsoluteEncoderConfig;

class SwerveAbsoluteEncoder
{

    public:
        SwerveAbsoluteEncoder() = default;
        virtual ~SwerveAbsoluteEncoder() = default; 
        virtual void Configure(AbsoluteEncoderConfig &config) = 0;
        virtual frc::Rotation2d GetHeading() = 0;
        virtual frc::Rotation2d GetRawHeading() = 0;
        virtual bool GetInverted() = 0;
        virtual void SetInverted(bool inverted) = 0;
        virtual void SetZeroHeading(frc::Rotation2d zero_heading) = 0;

    private: 

};