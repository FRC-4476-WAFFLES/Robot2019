/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoWaitCommand.h"

AutoWaitCommand::AutoWaitCommand(float timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  wait = timeout;
}

// Called just before this Command runs the first time
void AutoWaitCommand::Initialize() {
  t.Reset();
  t.Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoWaitCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool AutoWaitCommand::IsFinished() { return t.Get()>wait; }

// Called once after isFinished returns true
void AutoWaitCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoWaitCommand::Interrupted() {}
