#include "AnalogAbsoluteEncoder.h"

void AnalogAbsoluteEncoder::Configure(AbsoluteEncoderConfig &config)
{
    SetInverted(config.is_inverted);
    SetZeroHeading(config.zero_heading);
    m_encoder = config.encoder;
}

frc::Rotation2d AnalogAbsoluteEncoder::GetHeading()
{
    frc::Rotation2d raw_heading = GetRawHeading();
    double heading = static_cast<double>((raw_heading - m_zero_heading).Degrees());
    if (heading < 0)
    {
        heading = 360.0f + heading;
    }

    return frc::Rotation2d(static_cast<units::degree_t>(heading));
}

frc::Rotation2d AnalogAbsoluteEncoder::GetRawHeading()
{ 
    double degrees = (m_encoder->GetAbsolutePosition().GetValueAsDouble() + 0.5) * 360.0f;
    if (m_is_inverted)
    {
        degrees = std::abs(360.0f - degrees);
    }

    frc::Rotation2d heading(static_cast<units::degree_t>(degrees));
    return heading;
}

bool AnalogAbsoluteEncoder::GetInverted()
{
    return m_is_inverted;
}

void AnalogAbsoluteEncoder::SetInverted(bool inverted)
{
    m_is_inverted = inverted;
}

void AnalogAbsoluteEncoder::SetZeroHeading(frc::Rotation2d zero_heading)
{
    m_zero_heading = zero_heading;
}
