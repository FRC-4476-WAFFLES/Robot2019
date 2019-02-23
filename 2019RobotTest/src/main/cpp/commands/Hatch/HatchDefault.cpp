/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Hatch/HatchDefault.h"
#include "Robot.h"

//default

HatchDefault::HatchDefault() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Hatch);
}

// Called just before this Command runs the first time
void HatchDefault::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchDefault::Execute() {
  //unclamp if we don't have a hatch and are intaking
  if(Robot::Intake.is_intaking && Robot::Intake.HasCargo() && Robot::Hatch.current_clamp_state == false){
    Robot::Hatch.UpdateHatch(Robot::Hatch.current_clamp_state, false);
  }
  //if clamped, put the arm down
  if(Robot::Hatch.current_clamp_state == false){
    Robot::Hatch.UpdateHatch(false, false);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchDefault::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchDefault::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchDefault::Interrupted() {}
