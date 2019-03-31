/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Climber/WaitTrigger.h"
#include "Robot.h"

WaitTrigger::WaitTrigger() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Climb);
}

// Called just before this Command runs the first time
void WaitTrigger::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WaitTrigger::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool WaitTrigger::IsFinished() { return Robot::oi.operate.GetRawButton(Robot::oi.OperatorButton::BumperTopRight); }

// Called once after isFinished returns true
void WaitTrigger::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitTrigger::Interrupted() {}
