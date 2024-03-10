#include "subsystems/IntakeHAL.h"



IntakeHAL::IntakeHAL(){
    // Since our pivot motor had no issue move the intake up and down. However we had issues with the actuator 
    //motors rotating the right way. 
    m_LFTActMotor.RestoreFactoryDefaults();
    m_LFTPvtMotor.RestoreFactoryDefaults();
    m_RGTActMotor.RestoreFactoryDefaults();
    m_RGTPvtMotor.RestoreFactoryDefaults();
    

    /**
     * Here's the act motor inversion stuff. 
     * Inverted intake is set to true...  
    */

    m_LFTActMotor.SetInverted(INVERT_INTAKE_ACT);
    m_curIntakeInversion = m_LFTActMotor.GetInverted();

    m_RGTActMotor.Follow(m_LFTActMotor, true);
    m_RGTPvtMotor.Follow(m_LFTPvtMotor, false);

    m_LFTActMotor.EnableVoltageCompensation(VOLT_COMP);
    m_LFTPvtMotor.EnableVoltageCompensation(VOLT_COMP);
    m_RGTActMotor.EnableVoltageCompensation(VOLT_COMP);
    m_RGTPvtMotor.EnableVoltageCompensation(VOLT_COMP);

    m_LFTPvtPID.SetP(INTAKE_P);
    m_LFTPvtPID.SetI(INTAKE_I);
    m_LFTPvtPID.SetD(INTAKE_D);

    
    m_LFTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
    m_LFTPvtMotor.SetSmartCurrentLimit(INTAKE_PVT_CURRENT_LIMIT);
    m_RGTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
    m_RGTPvtMotor.SetSmartCurrentLimit(INTAKE_PVT_CURRENT_LIMIT);

    m_LFTPvtPID.SetFeedbackDevice(m_LFTPvtAbsEncoder);

    m_LFTPvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_RGTPvtMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    
    m_LFTPvtAbsEncoder.SetInverted(LFT_PVT_ABS_ENC_INVERTED);
    m_LFTPvtAbsEncoder.SetPositionConversionFactor(LFT_PVT_ABS_ENC_CONVERSION_FACTOR);
    m_LFTPvtAbsEncoder.SetZeroOffset(INTAKE_ZERO_OFFSET);

    m_LFTPvtMotor.SetInverted(LFT_PVT_MTR_INVERTED);

    m_LFTActMotor.BurnFlash();
    m_LFTPvtMotor.BurnFlash();
    m_RGTActMotor.BurnFlash();
    m_RGTPvtMotor.BurnFlash();

    auto inst = nt::NetworkTableInstance::GetDefault();
    std::shared_ptr<nt::NetworkTable> table = inst.GetTable("intake");
    pub_intakeSpeed = table->GetDoubleTopic("intake").Publish();
    pub_angle = table->GetDoubleTopic("intake").Publish();
    pub_speed = table->GetDoubleTopic("intake").Publish();
    pub_profileState = table->GetStringTopic("intake").Publish();
}


void IntakeHAL::RunIntake(double speed) {

    m_intakeSpeed = speed;

    if (checkIfInverted()) {
        fixInversion();
    }

    m_LFTActMotor.Set(m_intakeSpeed);

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

void IntakeHAL::fixInversion() {
    m_LFTActMotor.RestoreFactoryDefaults();
    m_RGTActMotor.RestoreFactoryDefaults();
    m_RGTActMotor.Follow(m_LFTActMotor, true);
    m_LFTActMotor.SetInverted(INVERT_INTAKE_ACT);
    m_curIntakeInversion = m_LFTActMotor.GetInverted();
    m_LFTActMotor.SetSmartCurrentLimit(INTAKE_ACT_CURRENT_LIMIT);
    m_LFTActMotor.BurnFlash();
    m_RGTActMotor.BurnFlash();
}

bool IntakeHAL::checkIfInverted() {

    return m_curIntakeInversion;

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