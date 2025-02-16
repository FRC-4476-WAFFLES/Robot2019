/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "commands/Auto/GeneralTestAuto.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/GenericHID.h>
#include <frc/XboxController.h>

OI Robot::oi;
ClimbSubsystem Robot::Climb;
DriveSubsystem Robot::Drive;
ElevatorSubsystem Robot::Elevator;
HatchSubsystem Robot::Hatch;
IntakeSubsystem Robot::Intake;
LightSubsystem Robot::Lights;
CameraSubsystem Robot::Camera;
RobotInfo Robot::Info;

void Robot::RobotInit(){

  CameraServer::GetInstance()->StartAutomaticCapture();
  compressor->SetClosedLoopControl(true);

  AutonomousChooser.SetDefaultOption("Null", nullptr);
  AutonomousChooser.AddOption("Test", &TestAuto);
  AutonomousChooser.AddOption("Center", &CenterAuto);
  AutonomousChooser.AddOption("Left Level 1", &LeftLvl1Auto);
  AutonomousChooser.AddOption("Left Level 2", &LeftLvl2Auto);
  AutonomousChooser.AddOption("Right Level 1", &RightLvl1Auto);
  AutonomousChooser.AddOption("Right Level 2", &RightLvl2Auto);
  frc::SmartDashboard::PutData("Auto Modes", &AutonomousChooser);
  Camera.SetLedMode(Camera.CameraLEDMode::Off);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  // oi.hid.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.0);
  // oi.hid.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
  Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Driver);
}

void Robot::DisabledPeriodic() { 
  frc::Scheduler::GetInstance()->Run();
  Camera.SetLedMode(Camera.CameraLEDMode::Off);
  Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Driver);
  oi.Prints();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }
  Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Driver);

  autonomousCommand = AutonomousChooser.GetSelected();

  if (autonomousCommand != nullptr) {
    autonomousCommand->Start();
  }
}

void Robot::AutonomousPeriodic() { 
  frc::Scheduler::GetInstance()->Run();
  oi.Prints(); 
  
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Driver);
  // oi.hid.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1.0);
  // oi.hid.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 1.0);

  if(fabs(fabs(Elevator.ElevatorPosition())-fabs(Elevator.GetNextPosition()) > 100)){
    Elevator.elevator_state_machine_state = 1;
  }
  if (autonomousCommand != nullptr) {
    autonomousCommand->Cancel();
    autonomousCommand = nullptr;
  }
}

void Robot::TeleopPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 
  oi.Prints();
  
}

void Robot::TestPeriodic() {
  oi.Prints();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
