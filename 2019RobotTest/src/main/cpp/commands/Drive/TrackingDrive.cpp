/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive/TrackingDrive.h"
#include "Robot.h"

TrackingDrive::TrackingDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void TrackingDrive::Initialize() {
  t.Reset();
  t.Start();
}

// Called repeatedly when this Command is scheduled to run
void TrackingDrive::Execute() {
  Robot::Drive.TrackingDrive(0.3, 0.3);
}

// Make this return true when this Command no longer needs to run execute()
bool TrackingDrive::IsFinished() { return t.Get() > 2; }

// Called once after isFinished returns true
void TrackingDrive::End() {
  Robot::Drive.WafflesDrive(0.0,0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TrackingDrive::Interrupted() { End();}
