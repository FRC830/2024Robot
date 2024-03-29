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
const double INTAKE_ZERO_OFFSET = 223.694;

const bool LFT_PVT_ABS_ENC_INVERTED = false;
const double LFT_PVT_ABS_ENC_CONVERSION_FACTOR = 360.0;
const bool LFT_PVT_MTR_INVERTED = true;

const bool INVERT_INTAKE_ACT = false;

// ###########################################################
// #                        LAUNCHER                         #
// ###########################################################
const int FLYWHEEL_TOP_ID = 22;
const int FLYWHEEL_BOTTOM_ID = 23;
const int LAUNCHER_PVT_MTR_ID = 21;
const int LAUNCHER_IND_MTR_ID = 20;

const double FLYWHEEL_P = 0.25;
const double FLYWHEEL_I = 0.0;
const double FLYWHEEL_D = 0.0;

const double PVT_P = 0.1;
const double PVT_I = 0.0;
const double PVT_D = 0.0;

const int LAUNCHER_PVT_CURRENT_LIMIT = 20;
const int FLYWHEEL_ACT_CURRENT_LIMIT = 20;
const int LAUNCHER_IND_CURRENT_LIMIT = 28;

const bool INVERT_FLYWHEEL = true;

const double LAUNCHER_PVT_ABS_ENC_CONVERSION_FACTOR = 80.0;
const double LAUNCHER_ZERO_OFFSET = 13.501;

const double MAX_PIVOT_ANGLE = 75.0;
const double MIN_PIVOT_ANGLE = 5.0;

const bool INVERT_INDEXER = false;

const double UP_MAX_ACC = 600.0;
const double DOWN_MAX_ACC = 200.0;
const double MAX_JERK = 1250.0;

const double SUB_ANGLE = 55.0;
const double HOARDE_ANG = 40.0;
const double STOW_ANGLE = 10.0;
const double SUB_SPEED = 150.0;
const double HOARDE_SPD = 70.0;
const double INDEXER_SPEED = 1.0;
const double INDEXER_SLOW_SPEED = 0.15;