/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Intake/IntakeSet.h"
#include "Robot.h"

IntakeSet::IntakeSet(float spd) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Intake);
  SPD = spd;
}

// Called just before this Command runs the first time
void IntakeSet::Initialize() {
  Robot::Intake.SetIntakeSpeed(SPD);
}

// Called repeatedly when this Command is scheduled to run
void IntakeSet::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool IntakeSet::IsFinished() { return true; }

// Called once after isFinished returns true
void IntakeSet::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeSet::Interrupted() {}
