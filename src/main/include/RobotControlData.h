#pragma once
#include "subsystems/subsystemsManagers/IntakeManager.h"
#include "subsystems/subsystemsManagers/LauncherManager.h"

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;
    bool slowMode;
};

struct RobotControlData {
    IntakeInput intakeInput;
    LauncherInput launcherInput;
    SwerveInput swerveInput;
};