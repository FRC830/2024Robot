#pragma once
#include "subsystems/subsystemsManagers/ClimberManager.h"
#include "subsystems/subsystemsManagers/IntakeManager.h"
#include "subsystems/subsystemsManagers/LauncherManager.h"

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;
    bool slowMode;
};


struct SmartIntakeInput{
    bool smartIntake;
    bool smartOutTake;
    bool switchMode;
    bool laser;
};

struct AutoAimInput{
    bool autoAim;
    double robotCurAngle;
    double robotSetAngle;
};

struct AutoAimOutput{
    double robotRotSpeed;
};

struct RobotControlData {
    IntakeInput intakeInput;
    IntakeOutput intakeOutput;
    LauncherInput launcherInput;
    LauncherOutput launcherOutput;
    SwerveInput swerveInput;
    SmartIntakeInput smartIntakeInput;
    AutoAimInput autoAimInput;
    AutoAimOutput autoAimOutput;
    ClimberInput climberInput;
};

