#include "Robot.h"
#include "SwerveConfig.h"

  namespace ModulePosition
  { 
    static const int FL = 0;
    static const int FR = 1;
    static const int BL  = 2;
    static const int BR  = 3; 
  };

void Robot::SwerveInit(){
  AbsoluteEncoderConfig abs_config;

  abs_config.encoder = &fl_abs_enc;
  abs_config.is_inverted = FL_ABS_ENC_INVERTED;
  abs_config.zero_heading = FL_ZERO_HEADING;
  _abs_encoders[ModulePosition::FL].Configure(abs_config);

  abs_config.encoder = &fr_abs_enc;
  abs_config.is_inverted = FR_ABS_ENC_INVERTED;
  abs_config.zero_heading = FR_ZERO_HEADING;
  _abs_encoders[ModulePosition::FR].Configure(abs_config);

  abs_config.encoder = &bl_abs_enc;
  abs_config.is_inverted = BL_ABS_ENC_INVERTED;
  abs_config.zero_heading = BL_ZERO_HEADING;
  _abs_encoders[ModulePosition::BL].Configure(abs_config);

  abs_config.encoder = &br_abs_enc;
  abs_config.is_inverted = BR_ABS_ENC_INVERTED;
  abs_config.zero_heading = BR_ZERO_HEADING;
  _abs_encoders[ModulePosition::BR].Configure(abs_config);


  SwerveTurnMotorConfig turn_config;
  turn_config.p=TURN_P;  
  turn_config.i=TURN_I;
  turn_config.d=TURN_D;
  turn_config.ff=TURN_FF;
  turn_config.ratio=MOTOR_ROT_TO_DEG;
  turn_config.swerve_voltage_compensation = SWERVE_VOLTAGE_COMPENSATION;
  turn_config.turn_motor_current_limit = TURN_MOTOR_CURRENT_LIMIT;

  turn_config.deviceID=FL_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::FL];
  turn_config.inverted=FL_TURN_MTR_INVERTED;
  turn_config.PID=&fl_turn_pid;
  turn_config.relative_Encoder=&fl_turn_enc;
  turn_config.turn_motor=&fl_turn_mtr;
  _turn_motors[ModulePosition::FL].Configure(turn_config);

  turn_config.deviceID=FR_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::FR];
  turn_config.inverted=FR_TURN_MTR_INVERTED;
  turn_config.PID=&fr_turn_pid;
  turn_config.relative_Encoder=&fr_turn_enc;
  turn_config.turn_motor=&fr_turn_mtr;
  _turn_motors[ModulePosition::FR].Configure(turn_config);

  turn_config.deviceID=BL_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::BL];
  turn_config.inverted=BL_TURN_MTR_INVERTED;
  turn_config.PID=&bl_turn_pid;
  turn_config.relative_Encoder=&bl_turn_enc;
  turn_config.turn_motor=&bl_turn_mtr;
  _turn_motors[ModulePosition::BL].Configure(turn_config);

  turn_config.deviceID=BR_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::BR];
  turn_config.inverted=BR_TURN_MTR_INVERTED;
  turn_config.PID=&br_turn_pid;
  turn_config.relative_Encoder=&br_turn_enc;
  turn_config.turn_motor=&br_turn_mtr;
  _turn_motors[ModulePosition::BR].Configure(turn_config);


  SwerveDriveMotorConfig drive_config;
  drive_config.p = DRIVE_P;
  drive_config.i = DRIVE_I;
  drive_config.d = DRIVE_D;
  drive_config.ff = DRIVE_FF;
  drive_config.ratio = MOTOR_ROT_TO_FT / 60.0;
  drive_config.drive_motor_current_limit = DRIVE_MOTOR_CURRENT_LIMIT;
  drive_config.swerve_voltage_compensation = SWERVE_VOLTAGE_COMPENSATION;
  
  drive_config.PID = &fl_drive_pid;
  drive_config.encoder = &fl_drive_enc;
  drive_config.motor = &fl_drive_mtr;
  drive_config.correction_factor = FL_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::FL].Configure(drive_config);

  drive_config.PID = &fr_drive_pid;
  drive_config.encoder = &fr_drive_enc;
  drive_config.motor = &fr_drive_mtr;
  drive_config.correction_factor = FR_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::FR].Configure(drive_config);

  drive_config.PID = &bl_drive_pid;
  drive_config.encoder = &bl_drive_enc;
  drive_config.motor = &bl_drive_mtr;
  drive_config.correction_factor = BL_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::BL].Configure(drive_config);

  drive_config.PID = &br_drive_pid;
  drive_config.encoder = &br_drive_enc;
  drive_config.motor = &br_drive_mtr;
  drive_config.correction_factor = BR_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::BR].Configure(drive_config);


  SwerveModuleConfig module_config;
  module_config.idleMode=true;

  for (int i = 0; i < NUM_MODULES; ++i)
  {
    module_config.driveMotor = &_drive_motors[i];
    module_config.turnMotor  = &_turn_motors[i];
    _modules[i].Configure(module_config);
  }
  
  GyroConfig gyroConfig;
  gyroConfig.is_inverted = GYRO_INVERTED;
  gyroConfig.zero_heading = GYRO_ZERO_HEADING;
  _gyro.Configure(gyroConfig);

  SwerveConfig swerveConfig;
  swerveConfig.backLeftLocation=bl_position;
  swerveConfig.backRightLocation=br_position;
  swerveConfig.ebrake=false;
  swerveConfig.frontLeftLocation=fl_position;
  swerveConfig.frontRightLocation=fr_position;
  swerveConfig.idle_mode=IS_DRIVE_IN_COAST;
  swerveConfig.maxDriveSpeed=MAX_DRIVE_SPEED_FPS;
  swerveConfig.maxTurnSpeed=MAX_ANGULAR_VELOCITY_DEGPS;
  swerveConfig.orientation=IS_ROBOT_ORIENTED_DRIVE;
  swerveConfig.deadzone=CONTROLLER_DEADZONE;
  swerveConfig.gyro=&_gyro;
  auto* temp = _swerve.GetModules();
  for (int i = 0; i < 4; ++i)
  {
    (*temp)[i] = &_modules[i];
  }
  _swerve.Configure(swerveConfig);
  _swerve.SetFieldOriented();
}