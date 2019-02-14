/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/WaitCommand.h"

WaitCommand::WaitCommand(double timeout)
    : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void WaitCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WaitCommand::Execute() { double x = 5; x = x+3;}

// Called once after command times out
void WaitCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitCommand::Interrupted() {}
