#pragma once
#include "subsystems/subsystemsManagers/IntakeManager.h"
#include "subsystems/subsystemsManagers/LauncherManager.h"

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;
    bool slowMode;
};

struct VisionInput {
    bool autoAim;
    bool reset;

};

struct SmartIntakeInput{
    bool smartIntake;
    bool smartOutTake;
    bool switchMode;
    bool laser;
};

struct RobotControlData {
    IntakeInput intakeInput;
    IntakeOutput intakeOutput;
    LauncherInput launcherInput;
    LauncherOutput launcherOutput;
    SwerveInput swerveInput;
    SmartIntakeInput smartIntakeInput;
    VisionInput visionInput;
};

