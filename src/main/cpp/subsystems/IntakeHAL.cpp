#include "subsystems/IntakeHAL.h"


IntakeHAL::IntakeHAL(){
    bool successfulConfig = false;
    int numRetries = 0;
    rev::REVLibError error;

    while (!successfulConfig && numRetries <= 5)
    {
        numRetries++;


        error = m_LFTActMotor.RestoreFactoryDefaults();
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtMotor.RestoreFactoryDefaults();
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTActMotor.RestoreFactoryDefaults();
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.RestoreFactoryDefaults();
        if (error != rev::REVLibError::kOk) continue;

        error = m_LFTActMotor.SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtMotor.SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTActMotor.SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.SetCANTimeout(50);
        if (error != rev::REVLibError::kOk) continue;

        m_RGTActMotor.SetInverted(INVERT_INTAKE_ACT);
        if (m_RGTActMotor.GetInverted() != INVERT_INTAKE_ACT) continue;

        error = m_LFTActMotor.Follow(m_RGTActMotor, true);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.Follow(m_LFTPvtMotor, false);
        if (error != rev::REVLibError::kOk) continue;

        error = m_LFTActMotor.EnableVoltageCompensation(VOLT_COMP);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtMotor.EnableVoltageCompensation(VOLT_COMP);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTActMotor.EnableVoltageCompensation(VOLT_COMP);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.EnableVoltageCompensation(VOLT_COMP);
        if (error != rev::REVLibError::kOk) continue;

        error = m_LFTPvtPID.SetP(INTAKE_P);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtPID.SetI(INTAKE_I);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtPID.SetD(INTAKE_D);
        if (error != rev::REVLibError::kOk) continue;
        
        error = m_LFTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtMotor.SetSmartCurrentLimit(INTAKE_PVT_CURRENT_LIMIT);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.SetSmartCurrentLimit(INTAKE_PVT_CURRENT_LIMIT);
        if (error != rev::REVLibError::kOk) continue;

        error = m_LFTPvtPID.SetFeedbackDevice(m_LFTPvtAbsEncoder);
        if (error != rev::REVLibError::kOk) continue;

        error = m_LFTPvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        if (error != rev::REVLibError::kOk) continue;
        
        error = m_LFTPvtAbsEncoder.SetInverted(LFT_PVT_ABS_ENC_INVERTED);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtAbsEncoder.SetPositionConversionFactor(LFT_PVT_ABS_ENC_CONVERSION_FACTOR);
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtAbsEncoder.SetZeroOffset(INTAKE_ZERO_OFFSET);
        if (error != rev::REVLibError::kOk) continue;

        m_LFTPvtMotor.SetInverted(LFT_PVT_MTR_INVERTED);
        if (m_LFTPvtMotor.GetInverted() != LFT_PVT_MTR_INVERTED) continue;
    
        error = m_LFTActMotor.BurnFlash();
        if (error != rev::REVLibError::kOk) continue;
        error = m_LFTPvtMotor.BurnFlash();
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTActMotor.BurnFlash();
        if (error != rev::REVLibError::kOk) continue;
        error = m_RGTPvtMotor.BurnFlash();
        if (error != rev::REVLibError::kOk) continue;

        successfulConfig = true;
    }


    auto inst = nt::NetworkTableInstance::GetDefault();
    std::shared_ptr<nt::NetworkTable> table = inst.GetTable("intake");
    pub_intakeSpeed = table->GetDoubleTopic("intake").Publish();
    pub_angle = table->GetDoubleTopic("intake").Publish();
    pub_speed = table->GetDoubleTopic("intake").Publish();
    pub_profileState = table->GetStringTopic("intake").Publish();
}


void IntakeHAL::RunIntake(double speed) {

    m_intakeSpeed = speed;

    m_RGTActMotor.Set(m_intakeSpeed);

}

void IntakeHAL::ProfiledMoveToAngle(double angle) {

    switch (m_profileState) {

        case 0: 
        {
            m_ProfileStartPos = GetAngle();

            m_Timer.Restart();

            m_profileState++;

            break;
        }
            

        case 1:
        {
            auto setPoint = m_Profile.Calculate(m_Timer.Get(),    
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_ProfileStartPos}, 0_deg_per_s},  
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{angle}, 0_deg_per_s}
            );

            SetAngle(setPoint.position.to<double>());

            if (m_Profile.IsFinished(m_Timer.Get())) {

                m_profileState++;

            }

            break;
        }

        case 2: 
        {

            m_Timer.Stop();

            m_profileState++;

            break;
        }
        
        default:
            break; 
    }

}

void IntakeHAL::ManualMovePivot(double speed) {

    SetAngle(GetAngle() + (speed * INTAKE_INPUT_TO_DEG));

}

void IntakeHAL::ResetProfiledMoveState() {

    m_profileState = 0;

}

void IntakeHAL::SetAngle(double angle) {

    m_LFTPvtPID.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);

}

double IntakeHAL::GetAngle() {

     return m_LFTPvtAbsEncoder.GetPosition();

}

double IntakeHAL::GetSpeed() {

    return m_intakeSpeed;

}

void IntakeHAL::PublishDebugInfo()
{
    pub_intakeSpeed.Set(m_intakeSpeed);
    pub_angle.Set(GetAngle());
    pub_speed.Set(GetSpeed());

    std::string profileStateString;
    if(m_profileState == 0) profileStateString="ABOUT TO MOVE";
    if(m_profileState == 1) profileStateString="CURRENTLY MOVING";
    if(m_profileState == 2) profileStateString="FINISHED MOVE";
    if(m_profileState == 3) profileStateString="NOT MOVING";
    pub_profileState.Set(profileStateString);
}