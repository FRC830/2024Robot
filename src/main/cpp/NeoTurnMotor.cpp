#include"NeoTurnMotor.h"


void NeoTurnMotor::Configure(SwerveTurnMotorConfig &config){
    m_pastCommandAngle = -1000000.0;
    m_AbsouluteEncoder = config.absouluteEncoder;
    m_turn_motor = config.turn_motor;
    m_relative_Encoder = config.relative_Encoder;
    m_PID = config.PID;
    bool succesful = false;
    int num_retries = 0;
    rev::REVLibError error;
    
    while (!succesful && num_retries <= 5)
    {
        num_retries++;
        error = m_turn_motor->RestoreFactoryDefaults();
        if (error != rev::REVLibError::kOk) continue;
        error = m_turn_motor->SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        error = m_turn_motor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetP(config.p);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetI(config.i);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetD(config.d);
        if (error != rev::REVLibError::kOk) continue;
        error = m_PID->SetFF(config.ff);
        if (error != rev::REVLibError::kOk) continue;
        error = m_relative_Encoder->SetPositionConversionFactor(config.ratio);
        if (error != rev::REVLibError::kOk) continue;
        error = m_turn_motor->SetSmartCurrentLimit(config.turn_motor_current_limit);
        if (error != rev::REVLibError::kOk) continue;
        SetInverted(config.inverted);
        if (m_turn_motor->GetInverted() != config.inverted) continue;
        error = m_turn_motor->EnableVoltageCompensation(config.swerve_voltage_compensation);
        if (error != rev::REVLibError::kOk) continue;
        error = m_turn_motor->BurnFlash();
        if (error != rev::REVLibError::kOk) continue;
        succesful = true;
    }
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
