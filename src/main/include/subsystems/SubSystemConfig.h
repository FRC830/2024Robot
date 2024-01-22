#pragma once


#include "rev/CANSparkMax.h"
#include <ctre/phoenix/sensors/CANCoder.h>
#include <ctre/phoenix6/TalonFX.hpp>
#include <frc/motorcontrol/MotorControllerGroup.h>


// ###########################################################
// #                         Intake                          #
// ###########################################################
const int LFT_INTAKE_ACT_MTR_ID = 0;
const int RGT_INTAKE_ACT_MTR_ID = 1;

const int INTAKE_PVT_MTR_A = 2;
const int INTAKE_PVT_MTR_B = 3;

const int INTAKE_PVT_ENCODER_ID = 8; 

inline ctre::phoenix::sensors::CANCoder PVT_ENCODER{INTAKE_PVT_ENCODER_ID, "rio"};

inline rev::CANSparkMax RGT_ACT_MTR{RGT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
inline rev::CANSparkMax LFT_ACT_MTR{LFT_INTAKE_ACT_MTR_ID, rev::CANSparkMax::MotorType::kBrushless};
inline rev::CANSparkMax RGT_PVT_MTR{INTAKE_PVT_MTR_A, rev::CANSparkMax::MotorType::kBrushless};
inline rev::CANSparkMax LFT_PVT_MTR{INTAKE_PVT_MTR_B, rev::CANSparkMax::MotorType::kBrushless};




// ###########################################################
// #                        Flywheel                         #
// ###########################################################
const int FLYWHEEL_ACT_MTR_A_ID = 4;
const int FLYWHEEL_ACT_MTR_B_ID = 5;
const int FLYWHEEL_PVT_MTR_A_ID = 6;
const int FLYWHEEL_PVT_MTR_B_ID = 7;
// do we need cancoders for the falcons? 

