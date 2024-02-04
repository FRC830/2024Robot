#include "IntakeHAL.h"

void IntakeHAL::Configure(IntakeHALConfig &config) {

    m_RGTActMotor = config.RGTActMotor;
    m_LFTActMotor = config.LFTActMotor;
    m_RGTPvtMotor = config.RGTPvtMotor;
    m_LFTPvtMotor = config.LFTPvtMotor;
    m_PVTEncoder = config.encoder;
    m_intakeSpeed = config.intakeSpeed;
    m_turningSpeed = config.turningspeed;

    m_PVTCalibrate = config.PVTCalibrate; 

    

    m_RGTActMotor->SetIdleMode(rev::CANSparkBase::IdleMode::kCoast);
    m_LFTActMotor->SetIdleMode(rev::CANSparkBase::IdleMode::kCoast);
    m_RGTPvtMotor->SetIdleMode(rev::CANSparkBase::IdleMode::kBrake);
    m_LFTPvtMotor->SetIdleMode(rev::CANSparkBase::IdleMode::kBrake);

    

    // m_ActMotors = frc::MotorControllerGroup(m_RGTActMotor, m_LFTActMotor);
    // m_PvtMotors = frc::SpeedControllerGroup(m_RGTPvtMotor, m_LFTPvtMotor);
}

void IntakeHAL::RunIntake(double speed) {

    auto pid = m_RGTActMotor->GetPIDController();
    auto pida = m_LFTActMotor->GetPIDController();

    pid.SetReference(speed, rev::CANSparkMax::ControlType::kVelocity);
    pida.SetReference(speed, rev::CANSparkMax::ControlType::kVelocity);
}

void IntakeHAL::ProfiledMoveToAngle(double angle) {

    SetAngle(angle);

}

void IntakeHAL::ManualMovePivot(double speed) {

    auto pid = m_LFTPvtMotor->GetPIDController();
    auto pida = m_RGTPvtMotor->GetPIDController();

    pid.SetReference(speed, rev::CANSparkMax::ControlType::kVelocity);
    pida.SetReference(speed, rev::CANSparkMax::ControlType::kVelocity);

}

void IntakeHAL::ResetProfiledMoveState()
{
    
}

void IntakeHAL::SetAngle(double angle) {

    //pid stuff go here

    auto pid = m_LFTPvtMotor->GetPIDController();
    auto pida = m_RGTPvtMotor->GetPIDController();

    pid.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);
    pida.SetReference(angle, rev::CANSparkMax::ControlType::kPosition);
}

double IntakeHAL::GetAngle() {

     return m_PVTEncoder->GetAbsolutePosition().GetValueAsDouble() *m_PVTCalibrate;


}

double IntakeHAL::GetSpeed() {

    return m_intakeSpeed;

}