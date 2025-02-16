/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Climber/ClimberHabLevel.h"
#include "Robot.h"

ClimberHabLevel::ClimberHabLevel() : Command("ClimberHabLevel"){
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Climb);
}

// Called just before this Command runs the first time
void ClimberHabLevel::Initialize() {
  Robot::Climb.ClimbTo(Robot::Climb.LegPositions::kHabHight);
}

// Called repeatedly when this Command is scheduled to run
void ClimberHabLevel::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClimberHabLevel::IsFinished() { return true; }

// Called once after isFinished returns true
void ClimberHabLevel::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberHabLevel::Interrupted() {}
