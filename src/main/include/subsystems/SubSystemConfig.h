#pragma once


#include "rev/CANSparkMax.h"
#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>

const double VOLT_COMP = 10.5;


// ###########################################################
// #                         Intake                          #
// ###########################################################
const int LFT_INTAKE_ACT_MTR_ID = 19;
const int RGT_INTAKE_ACT_MTR_ID = 18;

const int RGT_INTAKE_PVT_MTR_ID = 11;
const int LFT_INTAKE_PVT_MTR_ID = 4;

const int INTAKE_PVT_ENCODER_ID = 8; 

const double INTAKE_INPUT_TO_DEG = 2.0;

const double INTAKE_P = 0.05;
const double INTAKE_I = 0.0;
const double INTAKE_D = 0.0;

const int INTAKE_PVT_CURRENT_LIMIT = 30;
const int INTAKE_ACT_CURRENT_LIMIT = 40;

const double INTAKE_MAX_VEL = 60.0;
const double INTAKE_ACCEL = 30.0;

const bool LFT_PVT_ABS_ENC_INVERTED = false;
const double LFT_PVT_ABS_ENC_CONVERSION_FACTOR = 360.0;
const bool LFT_PVT_MTR_INVERTED = true;

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
// do we need cancoders for the falcons? 

