#include "WPISwerveModule.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/length.h>



frc::SwerveModuleState WPISwerveModule::Optimize(frc::SwerveModuleState desiredState, frc::Rotation2d currentHeading){

    auto delta = desiredState.angle - currentHeading;
    if (units::math::abs(delta.Degrees()) > 120_deg) {

        return frc::SwerveModuleState(-desiredState.speed, desiredState.angle + frc::Rotation2d{180_deg});

    } else {

        return {desiredState.speed, desiredState.angle};

    }


}
 
void WPISwerveModule::Configure(SwerveModuleConfig &config)
{
    m_driveMotor = config.driveMotor;
    m_turnMotor = config.turnMotor;
    SetIdleMode(config.idleMode);
};

void WPISwerveModule::SetState(frc::SwerveModuleState state)
{
    double fixed_heading = state.angle.Degrees().to<double>();
    fixed_heading = std::fmod(fixed_heading, 360.0);
    auto newState = Optimize(frc::SwerveModuleState(state.speed, frc::Rotation2d(units::degree_t{fixed_heading})), m_turnMotor->GetRotation());
    m_turnMotor->SetRotation(frc::Rotation2d(units::degree_t (std::fmod(newState.angle.Degrees().to<double>(), 360.0))));
    m_driveMotor->SetVelocity(newState.speed);
};

frc::SwerveModuleState WPISwerveModule::GetState() 
{
    frc::Rotation2d angle = m_turnMotor->GetRotation();
    auto speed = m_driveMotor->GetVelocity();
    frc::SwerveModuleState state{units::meters_per_second_t(units::feet_per_second_t(speed)),angle};
    return state;
};

void WPISwerveModule::SetIdleMode(bool idleMode)
{
    m_idleMode = idleMode;
    m_driveMotor->SetIdleMode(idleMode);
};

bool WPISwerveModule::GetIdleMode()
{
    return m_driveMotor->GetIdleMode();
};



frc::SwerveModulePosition WPISwerveModule::GetPosition() {


    auto dist = m_driveMotor->GetPosition(); 
    return {units::meter_t{dist}, m_turnMotor->GetRotation()};

}