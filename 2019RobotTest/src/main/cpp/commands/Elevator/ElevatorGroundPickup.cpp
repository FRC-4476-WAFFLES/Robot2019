/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Elevator/ElevatorGroundPickup.h"
#include "Robot.h"

//set the elevator to the ground pickup postition using SeekTo (unused)

ElevatorGroundPickup::ElevatorGroundPickup():
  frc::Command("ElevatorGroundPickup")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Elevator);
}

// Called just before this Command runs the first time
void ElevatorGroundPickup::Initialize() {
  Robot::Elevator.SeekTo(Robot::Elevator.Positions::Ground);
}

// Called repeatedly when this Command is scheduled to run
void ElevatorGroundPickup::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorGroundPickup::IsFinished() { return true; }

// Called once after isFinished returns true
void ElevatorGroundPickup::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorGroundPickup::Interrupted() {}
