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



}

void IntakeHAL::ProfiledMoveToAngle(double angle) {}

void IntakeHAL::ManualMovePivot(double speed) {}

void IntakeHAL::SetAngle(double angle) {



}

double IntakeHAL::GetAngle() {

     return m_PVTEncoder->GetAbsolutePosition() * m_PVTCalibrate;

}

double IntakeHAL::GetSpeed() {}