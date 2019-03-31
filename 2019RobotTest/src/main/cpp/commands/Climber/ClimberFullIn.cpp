/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Climber/ClimberFullIn.h"
#include "Robot.h"

ClimberFullIn::ClimberFullIn() : Command("ClimberFullIn"){
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Climb);
}

// Called just before this Command runs the first time
void ClimberFullIn::Initialize() {
  Robot::Climb.ClimbTo(Robot::Climb.LegPositions::kFullIn);
}

// Called repeatedly when this Command is scheduled to run
void ClimberFullIn::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClimberFullIn::IsFinished() { return true; }

// Called once after isFinished returns true
void ClimberFullIn::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberFullIn::Interrupted() {}
