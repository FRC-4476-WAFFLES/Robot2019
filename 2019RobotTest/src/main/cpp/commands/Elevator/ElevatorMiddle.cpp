/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Elevator/ElevatorMiddle.h"
#include "Robot.h"

ElevatorMiddle::ElevatorMiddle():
  frc::Command("ElevatorMiddle")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Elevator);
}

// Called just before this Command runs the first time
void ElevatorMiddle::Initialize() {
  Robot::Elevator.SeekTo(Robot::Elevator.Positions::Middle);
}

// Called repeatedly when this Command is scheduled to run
void ElevatorMiddle::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorMiddle::IsFinished() { return true; }

// Called once after isFinished returns true
void ElevatorMiddle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorMiddle::Interrupted() {}
