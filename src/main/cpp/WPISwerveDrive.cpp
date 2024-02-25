#include "WPISwerveDrive.h"
#include "frc/Timer.h"
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>

void WPISwerveDrive::Configure(SwerveConfig &config){
    frc::SmartDashboard::PutData("Field", &m_field);
    m_ebrake = config.ebrake;
    m_maxDriveSpeed = config.maxDriveSpeed;
    m_maxTurnSpeed = config.maxTurnSpeed;
    m_orientation = config.orientation;
    m_frontLeftLocation = config.frontLeftLocation;
    m_frontRightLocation = config.frontRightLocation;
    m_backLeftLocation = config.backLeftLocation;
    m_backRightLocation = config.backRightLocation;
    SetIdleMode(config.idle_mode);
    //m_modules = config.modules;
    m_kinematics = new frc::SwerveDriveKinematics(m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation, m_backRightLocation);
    m_deadzone = config.deadzone;
    m_gyro = config.gyro;
    //Last parameter in constuer must be relative the actual robot for it to wrok some what correctly
    //REMEMEBR TO FLIP DIRECTION DURING AUTON MAKING
    m_estimator = new frc::SwerveDrivePoseEstimator<4>(*m_kinematics, m_gyro->GetRawHeading(), {m_modules[0]->GetPosition(), m_modules[1]->GetPosition(), m_modules[2]->GetPosition(), m_modules[3]->GetPosition()}, frc::Pose2d(frc::Translation2d(), m_gyro->GetHeading()));
    std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;
    pathplanner::AutoBuilder::configureHolonomic(
        [this]() {return GetPose();},
        [this](frc::Pose2d InitPose)  {ResetPose(InitPose);},
        [this](){return GetRobotRelativeSpeeds(); },
        [this](frc::ChassisSpeeds speeds) {Drive(speeds);},
        pathplanner::HolonomicPathFollowerConfig( // HolonomicPathFollowerConfig, this should likely live in your Constants class
            pathplanner::PIDConstants(5.0, 0.0, 0.0), // Translation PID constants
            pathplanner::PIDConstants(5.0, 0.0, 0.0), // Rotation PID constants
            4.5_mps, // Max module speed, in m/s
            0.4_m, // Drive base radius in meters. Distance from robot center to furthest module.
            pathplanner::ReplanningConfig() // Default path replanning config. See the API for the options here
        ),

        []() {
            // Boolean supplier that controls when the path will be mirrored for the red alliance
            // This will flip the path being followed to the red side of the field.
            // THE ORIGIN WILL REMAIN ON THE BLUE SIDE

            auto alliance = frc::DriverStation::GetAlliance();
            if (alliance) {
                return alliance.value() == frc::DriverStation::Alliance::kRed;
            }
            return false;
        },

        {nullptr}
    );
}

bool WPISwerveDrive::GetEbrake() {
    return m_ebrake;
}
void WPISwerveDrive::SetEbrake(bool ebrake) {
    m_ebrake = ebrake;
}
void WPISwerveDrive::Drive(double x_position, double y_position, double rotation) {
    x_position = ApplyDeadzone(x_position);
    y_position = ApplyDeadzone(y_position);
    rotation = ApplyDeadzone(rotation);
    
     Drive(
     (units::feet_per_second_t)x_position * m_maxDriveSpeed, 
     (units::feet_per_second_t)y_position * m_maxDriveSpeed, 
     (units::degrees_per_second_t)rotation * m_maxTurnSpeed);

}

void WPISwerveDrive::Drive(units::feet_per_second_t vx, units::feet_per_second_t vy, units::degrees_per_second_t omega) {
    frc::SmartDashboard::PutNumber("Omega", static_cast<double>(omega));

    if (!m_orientation)
    {
        Drive(frc::ChassisSpeeds{vx, vy, omega});   
    }
    else
    {
        frc::ChassisSpeeds speeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(vx, vy, omega, m_gyro->GetRawHeading());
        Drive(speeds);
    }
}   

void WPISwerveDrive::Drive(frc::ChassisSpeeds speed) {
    
    // states = m_kinematics.ToSwerveModuleStates(speed);
    auto states = m_kinematics->ToSwerveModuleStates(speed);
    
    m_kinematics->DesaturateWheelSpeeds(&states, units::feet_per_second_t(m_maxDriveSpeed));


    std::vector<frc::SwerveModuleState> stateN;
    stateN.push_back(states[0]);
    stateN.push_back(states[1]);
    stateN.push_back(states[2]);
    stateN.push_back(states[3]);

    Drive(stateN);

}
void WPISwerveDrive::Drive(std::vector<frc::SwerveModuleState> &state) {
    if (!m_ebrake) {
        for(int i = 0; i < state.size(); i++){
            m_modules[i]->SetState(state[i]);
        }
    }

    // frc::SmartDashboard::PutNumber("Degrees Of Gyro from RAW", m_gyro->GetRawHeading().Degrees().to<double>());

    // frc::SmartDashboard::PutNumber("Degrees Of Gyro from Processed", m_gyro->GetRawHeading().Degrees().to<double>());

    // frc::SmartDashboard::PutNumber("")

    // frc::SmartDashboard::PutData("Rotation2d", )

    

    m_estimator->UpdateWithTime(frc::Timer::GetFPGATimestamp(), m_gyro->GetRawHeading(), {m_modules[0]->GetPosition(), m_modules[1]->GetPosition(), m_modules[2]->GetPosition(), m_modules[3]->GetPosition()});
    m_field.SetRobotPose(m_estimator->GetEstimatedPosition());
} 

bool WPISwerveDrive::GetIdleMode() {
    return false;
}

void WPISwerveDrive::SetIdleMode(bool idle_mode) {
     for(int i = 0; i < m_modules.size(); i++){

        m_modules[i]->SetIdleMode(idle_mode);

    }
}
void WPISwerveDrive::SetRobotOriented() {
    m_orientation = false;
}
void WPISwerveDrive::SetFieldOriented() {
    m_orientation = true; 
}
bool WPISwerveDrive::GetOrientedMode() {
    return m_orientation;
}

frc::Pose2d WPISwerveDrive::GetPose()
{
    return m_estimator->GetEstimatedPosition();
}

void WPISwerveDrive::ResetPose(frc::Pose2d pose)
{
    m_estimator->ResetPosition(m_gyro->GetRawHeading(), {m_modules[0]->GetPosition(), m_modules[1]->GetPosition(), m_modules[2]->GetPosition(), m_modules[3]->GetPosition()}, pose);
}

frc::ChassisSpeeds WPISwerveDrive::GetRobotRelativeSpeeds()
{
    return m_kinematics->ToChassisSpeeds({m_modules[0]->GetState(), m_modules[1]->GetState(), m_modules[2]->GetState(), m_modules[3]->GetState()});
}

double WPISwerveDrive::ApplyDeadzone(double input)
{
    double output = 0;

    if (input > m_deadzone)
    {
        output = (input - m_deadzone) / (1 - m_deadzone);
    }
    else if (input < -(m_deadzone))
    {
        output = (input + m_deadzone) / (1 - m_deadzone);
    }

    return output;
}