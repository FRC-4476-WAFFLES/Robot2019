/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Elevator/ElevatorHPPickup.h"
#include "Robot.h"

ElevatorHPPickup::ElevatorHPPickup():
  frc::Command("ElevatorHPPickup")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Elevator);
}

// Called just before this Command runs the first time
void ElevatorHPPickup::Initialize() {
  Robot::Elevator.SeekTo(Robot::Elevator.Positions::HPPickup, true);
}

// Called repeatedly when this Command is scheduled to run
void ElevatorHPPickup::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorHPPickup::IsFinished() { return true; }

// Called once after isFinished returns true
void ElevatorHPPickup::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorHPPickup::Interrupted() {}
