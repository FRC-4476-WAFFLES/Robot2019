/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive/DriveInterruptable.h"
#include "Robot.h"

DriveInterruptable::DriveInterruptable() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Drive);
}

// Called just before this Command runs the first time
void DriveInterruptable::Initialize() {
  Robot::Drive.WafflesDrive(0.5, 0.5);
}

// Called repeatedly when this Command is scheduled to run
void DriveInterruptable::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool DriveInterruptable::IsFinished() { return Robot::oi.operate.GetRawButton(Robot::oi.OperatorButton::BumperTopRight); }

// Called once after isFinished returns true
void DriveInterruptable::End() {
  Robot::Drive.WafflesDrive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveInterruptable::Interrupted() {End();}
