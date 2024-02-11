// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "subsystems/SubSystemConfig.h"
#include <string>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <iostream>
#include <array>
#include <frc/XboxController.h>
#include <frc2/command/CommandPtr.h>
#include <memory>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include "VisionConsumer.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;
  void updateDashBoardValues(); 
  void SwerveInit();

  void PrintSwerveInfo();

 private:
  static const int NUM_MODULES = 4;

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  // std::array<AnalogAbsoluteEncoder, NUM_MODULES> _abs_encoders;
  // std::array<NeoTurnMotor, NUM_MODULES> _turn_motors;
  // std::array<NeoDriveMotor, NUM_MODULES> _drive_motors;
  // std::array<WPISwerveModule, NUM_MODULES> _modules;
  // WPISwerveDrive _swerve;
  VisionConsumer vision; 

  // NavXGyro _gyro;
};
