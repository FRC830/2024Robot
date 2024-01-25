#pragma once
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/kinematics/SwerveModulePosition.h>

struct SwerveModuleConfig;


class SwerveModule
{
public:
    SwerveModule() = default;
    virtual ~SwerveModule() = default;
    virtual void SetState(frc::SwerveModuleState state) = 0; 
    virtual frc::SwerveModuleState GetState() = 0;
    virtual void SetIdleMode(bool idleMode) = 0;
    virtual bool GetIdleMode() = 0;
    virtual frc::SwerveModulePosition GetPosition() = 0;
    virtual void Configure(SwerveModuleConfig &config) = 0;
private:


};
