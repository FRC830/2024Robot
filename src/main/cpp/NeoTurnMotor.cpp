#include"NeoTurnMotor.h"
#include "ratpack/CANSparkMaxDebugMacro.h"

void NeoTurnMotor::Configure(SwerveTurnMotorConfig &config){
    m_pastCommandAngle = -1000000.0;
    m_AbsouluteEncoder = config.absouluteEncoder;
    m_turn_motor = config.turn_motor;
    m_relative_Encoder = config.relative_Encoder;
    m_PID = config.PID;

    START_RETRYING(NEO_TURN_MTR_RESTORE_FACTORY_DEFAULT)
    m_turn_motor->RestoreFactoryDefaults();
    END_RETRYING
    START_RETRYING(NEO_TURN_MTR_SET_CAN_TIMEOUT)
    m_turn_motor->SetCANTimeout(50);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            m_turn_motor->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

            if (m_turn_motor->GetIdleMode() == rev::CANSparkMax::IdleMode::kBrake)
            {
                successful = true;
            }
        }
    }

    START_RETRYING(NEO_TURN_PID_SETP)
    m_PID->SetP(config.p);
    END_RETRYING
    START_RETRYING(NEO_TURN_PID_SETI)
    m_PID->SetI(config.i);
    END_RETRYING
    START_RETRYING(NEO_TURN_PID_SETD)
    m_PID->SetD(config.d);
    END_RETRYING
    START_RETRYING(NEO_TURN_PID_SETFF)
    m_PID->SetFF(config.ff);
    END_RETRYING
    START_RETRYING(NEO_TURN_REL_ENC_SET_POSITION_CONVERSION_FACTOR)
    m_relative_Encoder->SetPositionConversionFactor(config.ratio);
    END_RETRYING
    START_RETRYING(NEO_TURN_MTR_SET_SMART_CURRENT_LIMIT)
    m_turn_motor->SetSmartCurrentLimit(config.turn_motor_current_limit);
    END_RETRYING

    {
        bool successful = false;
        int retries = 0;

        while (!successful && retries <= 50)
        {
            retries++;
            SetInverted(config.inverted);

            if (GetInverted() == config.inverted)
            {
                successful = true;
            }
        }
    }

    START_RETRYING(NEO_TURN_MTR_ENABLE_VOLTAGE_COMPENSATION)
    m_turn_motor->EnableVoltageCompensation(config.swerve_voltage_compensation);
    END_RETRYING
    START_RETRYING(NEO_TURN_MTR_BURN_FLASH)
    m_turn_motor->BurnFlash();
    END_RETRYING

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
