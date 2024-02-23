// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "VisionConsumer.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::updateDashBoardValues() {};

void Robot::RobotInit() {
  // m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  // m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  vision = VisionConsumer();

  m_autos_directory = frc::filesystem::GetDeployDirectory();
  m_autos_directory = m_autos_directory / "pathplanner" / "autos";
  m_auto_chooser.SetDefaultOption("None", "None");

  for (auto i : std::filesystem::directory_iterator(m_autos_directory))
  {
    m_auto_chooser.AddOption(std::filesystem::path(i.path().string()).filename().string(), std::filesystem::path(i.path().string()).filename().string());
  }

  frc::SmartDashboard::PutData("Pathplanner Autos", &m_auto_chooser);

  SwerveInit();
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {

  vision.Periodic();
  auto a = vision.GetPolarCoordForTagX(11);
  auto b = vision.GetPolarCoordForTagX(15);

  auto temp = vision.GetRobotToSpeaker(a, b, 6.9);
  frc::SmartDashboard::PutNumber("Weird r", temp.r);
  frc::SmartDashboard::PutNumber("Weird Theta", temp.theta);

}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  // m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = frc::SmartDashboard::GetString("Auto Selector", kAutoNameDefault);
  // fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

  m_state = 0;
  m_auto = std::make_unique<frc2::CommandPtr>(pathplanner::PathPlannerAuto(m_auto_chooser.GetSelected()).ToPtr());
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

  switch(m_state)
  {
    case 0:
      m_auto.get()->get()->Initialize();
      m_state++;
      break;
    case 1:
      m_auto.get()->get()->Execute();
      if (m_auto.get()->get()->IsFinished())
      {
        m_state++;
      }
      break;
    case 2:
      m_auto.get()->get()->End(false);
      m_state++;
      break;
    default:
      break;
  }
}

void Robot::TeleopInit() 
{
  _intake_manager.ResetIntake();
  _launcher_manager.ResetLauncher();
}

void Robot::TeleopPeriodic() {

  PrintSwerveInfo();
  _controller_interface.UpdateRobotControlData(_robot_control_data);
  _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, _robot_control_data.swerveInput.rotation);
  _smart_intake.HandleInput(_robot_control_data);
  _intake_manager.HandleInput(_robot_control_data.intakeInput, _robot_control_data.intakeOutput);
  _launcher_manager.HandleInput(_robot_control_data.launcherInput, _robot_control_data.launcherOutput);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
