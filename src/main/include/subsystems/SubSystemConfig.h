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
const int LFT_INTAKE_ACT_MTR_ID = 0;
const int RGT_INTAKE_ACT_MTR_ID = 1;

const int INTAKE_PVT_MTR_A = 2;
const int INTAKE_PVT_MTR_B = 3;

const int INTAKE_PVT_ENCODER_ID = 8; 

const double INTAKE_POS_TO_DEG = 1.0;

const double INTAKE_INPUT_TO_DEG = 2.0;


const double INTAKE_P = 1.0;
const double INTAKE_I = 1.0;
const double INTAKE_D = 1.0;


const int INTAKE_PVT_CURRENT_LIMIT = 20;
const int INTAKE_ACT_CURRENT_LIMIT = 20;


const double INTAKE_MAX_VEL = 0.0;
const double INTAKE_ACCEL = 0.0;

// ###########################################################
// #                        Flywheel                         #
// ###########################################################
const int FLYWHEEL_ACT_MTR_A_ID = 4;
const int FLYWHEEL_ACT_MTR_B_ID = 5;
const int FLYWHEEL_PVT_MTR_A_ID = 6;
const int FLYWHEEL_PVT_MTR_B_ID = 7;
// do we need cancoders for the falcons? 

