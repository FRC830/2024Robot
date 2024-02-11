
#pragma once
#include <frc/geometry/Translation2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <vector>

struct SwerveConfig;

class SwerveDrive 
{
    public:
        SwerveDrive() = default;
        virtual ~SwerveDrive() = default;
        virtual void Configure(SwerveConfig &config) = 0;
        virtual bool GetEbrake() = 0;
        virtual void SetEbrake(bool ebrake) = 0;
        virtual void Drive(double x_position, double y_position, double rotation) = 0;
        virtual void Drive(units::feet_per_second_t vx, units::feet_per_second_t vy, units::degrees_per_second_t omega) = 0;
        virtual void Drive(frc::ChassisSpeeds speed) = 0;
        virtual void Drive(std::vector<frc::SwerveModuleState> &state) = 0;
        virtual bool GetIdleMode() = 0;
        virtual void SetIdleMode(bool idle_mode) = 0;
        virtual void SetRobotOriented() = 0;
        virtual void SetFieldOriented() = 0;
        virtual bool GetOrientedMode() = 0; 
        virtual frc::Pose2d GetPose() = 0;
        virtual void ResetPose(frc::Pose2d pose) = 0;
        virtual frc::ChassisSpeeds GetRobotRelativeSpeeds() = 0;

    private:
        
};
