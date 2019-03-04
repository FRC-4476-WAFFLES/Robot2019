/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Hatch/HatchAutoManual.h"
#include "Robot.h"

HatchAutoManual::HatchAutoManual() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void HatchAutoManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchAutoManual::Execute() {
  if(Robot::oi.operate.GetRawButton(Robot::oi.BumperTopLeft)){
    Robot::Hatch.UpdateHatch(Robot::Hatch.current_clamp_state, !Robot::Hatch.current_deploy_state);
  }
  while(Robot::oi.operate.GetRawButton(Robot::oi.BumperTopLeft)){
    counter = counter+1;
  }
  if(Robot::oi.operate.GetRawButton(Robot::oi.BumperTopRight)){
    Robot::Hatch.UpdateHatch(!Robot::Hatch.current_clamp_state, Robot::Hatch.current_deploy_state);
  }
  while(Robot::oi.operate.GetRawButton(Robot::oi.BumperTopRight)){
    counter = counter+1;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchAutoManual::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchAutoManual::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchAutoManual::Interrupted() {}
