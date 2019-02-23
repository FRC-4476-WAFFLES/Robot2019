/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Hatch/ToggleDeploy.h"
#include "Robot.h"

//toggle the hatch deploy piston

ToggleDeploy::ToggleDeploy() :
  frc::Command("ToggleDeploy")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Hatch);
}

// Called just before this Command runs the first time
void ToggleDeploy::Initialize() {
  Robot::Hatch.UpdateHatch(Robot::Hatch.current_clamp_state, !Robot::Hatch.current_deploy_state);
}

// Called repeatedly when this Command is scheduled to run
void ToggleDeploy::Execute() {
  
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleDeploy::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleDeploy::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleDeploy::Interrupted() {}
