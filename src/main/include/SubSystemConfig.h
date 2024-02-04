#pragma once


#include "rev/CANSparkMax.h"
#include <ctre/phoenix6/CANcoder.hpp>
#include "ctre/phoenix6/TalonFX.hpp"
#include <frc/motorcontrol/MotorControllerGroup.h>


// ###########################################################
// #                         Intake                          #
// ###########################################################
const int LFT_INTAKE_ACT_MTR_ID = 0;
const int RGT_INTAKE_ACT_MTR_ID = 1;

const int INTAKE_PVT_MTR_A = 2;
const int INTAKE_PVT_MTR_B = 3;

const int INTAKE_PVT_ENCODER_ID = 8; 

inline ctre::phoenix6::hardware::CANcoder PVT_ENCODER{INTAKE_PVT_ENCODER_ID, "rio"};

inline rev::CANSparkMax RGT_ACT_MTR{RGT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
inline rev::CANSparkMax LFT_ACT_MTR{LFT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
inline rev::CANSparkMax RGT_PVT_MTR{INTAKE_PVT_MTR_A, rev::CANSparkMax::MotorType::kBrushless};
inline rev::CANSparkMax LFT_PVT_MTR{INTAKE_PVT_MTR_B, rev::CANSparkMax::MotorType::kBrushless};


// ###########################################################
// #                        Flywheel                         #
// ###########################################################
const int FLYWHEEL_ACT_MTR_A_ID = 4;
const int FLYWHEEL_ACT_MTR_B_ID = 5;

const int LAUNCHER_PVT_MTR_ID = 6;
const int LAUNCHER_IND_MTR_ID = 7;

const int LAUNCHER_PVT_ENCODER_ID = 9;

const double FLYWHEEL_P = 1.0;
const double FLYWHEEL_I = 0.0;
const double FLYWHEEL_D = 0.0;

const double PVT_P = 1.0;
const double PVT_I = 0.0;
const double PVT_D = 0.0;

const int LAUNCHER_PVT_CURRENT_LIMIT = 20;
const int FLYWHEEL_ACT_CURRENT_LIMIT = 20;
const int LAUNCHER_IND_CURRENT_LIMIT = 20;

const double LAUNCHER_PVT_POS_TO_DEG = 1.0;
// do we need cancoders for the falcons? 

