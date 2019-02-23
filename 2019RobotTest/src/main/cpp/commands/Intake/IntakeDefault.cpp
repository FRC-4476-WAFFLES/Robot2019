/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Intake/IntakeDefault.h"
#include "Robot.h"

//default does nothing

IntakeDefault::IntakeDefault() :
  frc::Command("IntakeDefault")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Intake);
}

// Called just before this Command runs the first time
void IntakeDefault::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeDefault::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeDefault::IsFinished() { return false; }

// Called once after isFinished returns true
void IntakeDefault::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeDefault::Interrupted() {}
