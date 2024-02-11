#pragma once
#include "Interfaces/SwerveModule.h"
#include "Interfaces/SwerveDriveMotor.h"
#include "Interfaces/SwerveTurnMotor.h"


struct SwerveModuleConfig
{
    bool idleMode;
    SwerveDriveMotor *driveMotor;
    SwerveTurnMotor *turnMotor;
};

class WPISwerveModule : public SwerveModule
{
    public:
        WPISwerveModule() = default;
        virtual ~WPISwerveModule() = default;
        virtual void SetState(frc::SwerveModuleState state) override; 
        virtual frc::SwerveModuleState GetState() override;
        virtual void SetIdleMode(bool idleMode) override;
        virtual bool GetIdleMode() override;
        virtual void Configure(SwerveModuleConfig &config) override;
        virtual frc::SwerveModulePosition GetPosition() override;
        virtual frc::SwerveModuleState Optimize(frc::SwerveModuleState desiredState, frc::Rotation2d currentHeading);

    private:
        bool m_idleMode;
        SwerveDriveMotor *m_driveMotor;
        SwerveTurnMotor *m_turnMotor;
};
