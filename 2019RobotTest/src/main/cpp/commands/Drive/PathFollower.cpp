/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive/PathFollower.h"
#include "Robot.h"

PathFollower::PathFollower(std::string path_name) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Drive);
  PathName = path_name;
}

// Called just before this Command runs the first time
void PathFollower::Initialize() {
  Robot::Drive.LoadPath(PathName);

}

// Called repeatedly when this Command is scheduled to run
void PathFollower::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool PathFollower::IsFinished() { return Robot::Drive.IsPathFinished(); }

// Called once after isFinished returns true
void PathFollower::End() {
  Robot::Drive.ClosePath();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PathFollower::Interrupted() {
  Robot::Drive.ClosePath();
}
