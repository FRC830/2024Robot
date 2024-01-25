#include"NeoTurnMotor.h"


void NeoTurnMotor::Configure(SwerveTurnMotorConfig &config){
    m_pastCommandAngle = -1000000.0;
    m_AbsouluteEncoder = config.absouluteEncoder;
    m_turn_motor = config.turn_motor;
    m_relative_Encoder = config.relative_Encoder;
    m_PID = config.PID;
    m_turn_motor->RestoreFactoryDefaults();
    m_turn_motor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_PID->SetP(config.p);
    m_PID->SetI(config.i);
    m_PID->SetD(config.d);
    m_PID->SetFF(config.ff);
    m_relative_Encoder->SetPositionConversionFactor(config.ratio);
    m_turn_motor->SetSmartCurrentLimit(config.turn_motor_current_limit);
    SetInverted(config.inverted);
    m_turn_motor->EnableVoltageCompensation(config.swerve_voltage_compensation);
    m_turn_motor->BurnFlash();
};    

void NeoTurnMotor::SetRotation(frc::Rotation2d deg){
    if (std::abs(m_pastCommandAngle-deg.Degrees().to<double>()) > 0.000001)
    {
        frc::Rotation2d realTurn = deg - GetRotation();
        if(realTurn.Degrees().to<double>() > 180.0) {

            realTurn = realTurn - frc::Rotation2d(units::degree_t(360.0));

        } else if (realTurn.Degrees().to<double>() < -180.0) {

            realTurn = realTurn + frc::Rotation2d(units::degree_t(360.0));

        }
    
        double targetPos = m_relative_Encoder->GetPosition() + realTurn.Degrees().to<double>();
        m_PID->SetReference(targetPos, rev::CANSparkMax::ControlType::kPosition);
        m_pastCommandAngle = deg.Degrees().to<double>();
    }
}; 

frc::Rotation2d NeoTurnMotor::GetRotation(){
    return m_AbsouluteEncoder->GetHeading();
}; 

bool NeoTurnMotor::GetInverted(){
    return m_turn_motor->GetInverted();
}; 
void NeoTurnMotor::SetInverted(bool invert){
    m_turn_motor->SetInverted(invert);
}; 
void NeoTurnMotor::ForceTurnDirectionCW(){
};
void NeoTurnMotor::ForceTurnDirectionCCW(){
};

//12.8:1
//537.6 
