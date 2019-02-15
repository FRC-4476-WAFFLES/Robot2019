/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Hatch/ToggleClamp.h"
#include "Robot.h"

ToggleClamp::ToggleClamp() :
  frc::Command("ToggleClamp")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Hatch);
}

// Called just before this Command runs the first time
void ToggleClamp::Initialize() {
  Robot::Hatch.UpdateHatch(!Robot::Hatch.current_clamp_state, Robot::Hatch.current_deploy_state);
  Robot::Elevator.temp_pull_in_cargo_exend = !Robot::Elevator.temp_pull_in_cargo_exend;
}

// Called repeatedly when this Command is scheduled to run
void ToggleClamp::Execute() {
  
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleClamp::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleClamp::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleClamp::Interrupted() {}
