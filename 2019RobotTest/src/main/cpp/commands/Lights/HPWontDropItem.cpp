/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Lights/HPWontDropItem.h"
#include "Robot.h"

HPWontDropItem::HPWontDropItem() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void HPWontDropItem::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HPWontDropItem::Execute() {
  Robot::Lights.hp_strobe = true;
}

// Make this return true when this Command no longer needs to run execute()
bool HPWontDropItem::IsFinished() { return false; }

// Called once after isFinished returns true
void HPWontDropItem::End() {
  Robot::Lights.hp_strobe = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HPWontDropItem::Interrupted() {
  Robot::Lights.hp_strobe = false;
}
