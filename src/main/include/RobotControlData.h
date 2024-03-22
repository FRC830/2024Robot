#pragma once
#include "subsystems/subsystemsManagers/IntakeManager.h"
#include "subsystems/subsystemsManagers/LauncherManager.h"

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;
    bool slowMode;
    bool resetGyroZeroHeading;
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
    double compare;
};

struct AutoAimOutput{
    double robotRotSpeed;
};

struct SmartIntakeOutput{
    bool smartIntakeFlag;
    bool smartOuttakeFlag;
};

struct RobotControlData {
    IntakeInput intakeInput;
    IntakeOutput intakeOutput;
    LauncherInput launcherInput;
    LauncherOutput launcherOutput;
    SwerveInput swerveInput;
    SmartIntakeInput smartIntakeInput;
    SmartIntakeOutput smartIntakeOutput;
    AutoAimInput autoAimInput;
    AutoAimOutput autoAimOutput;
};

