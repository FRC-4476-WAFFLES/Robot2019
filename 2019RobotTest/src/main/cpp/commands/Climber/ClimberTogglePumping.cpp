/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Climber/ClimberTogglePumping.h"

ClimberTogglePumping::ClimberTogglePumping() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ClimberTogglePumping::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberTogglePumping::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClimberTogglePumping::IsFinished() { return true; }

// Called once after isFinished returns true
void ClimberTogglePumping::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberTogglePumping::Interrupted() {}
