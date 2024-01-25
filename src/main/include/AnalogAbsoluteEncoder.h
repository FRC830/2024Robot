#pragma once
#include "Interfaces/SwerveAbsoluteEncoder.h"
#include <ctre/phoenix6/CANcoder.hpp>

struct AbsoluteEncoderConfig
{
    ctre::phoenix6::hardware::CANcoder *encoder;
    bool is_inverted;
    frc::Rotation2d zero_heading;
};

class AnalogAbsoluteEncoder : public SwerveAbsoluteEncoder
{
    public:
        AnalogAbsoluteEncoder() = default;
        virtual ~AnalogAbsoluteEncoder() = default;
        virtual void Configure(AbsoluteEncoderConfig &config) override;
        virtual frc::Rotation2d GetHeading() override;
        virtual frc::Rotation2d GetRawHeading() override;
        virtual bool GetInverted() override;
        virtual void SetInverted(bool inverted) override;
        virtual void SetZeroHeading(frc::Rotation2d zero_heading) override;
        
    private:
        ctre::phoenix6::hardware::CANcoder *m_encoder;
        bool m_is_inverted;
        frc::Rotation2d m_zero_heading;
};