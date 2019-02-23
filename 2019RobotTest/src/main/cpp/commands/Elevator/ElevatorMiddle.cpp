/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Elevator/ElevatorMiddle.h"
#include "Robot.h"

//set the elevator to the Middle postition using SeekTo

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
  time_held.Reset();
  time_held.Start();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorMiddle::Execute() {
  //if we hold the button, then go to the alternate setpoint
  if(time_held.Get() > 1 && !is_over_time_threshold){
    is_over_time_threshold = true;
    Robot::Elevator.SeekTo(Robot::Elevator.Positions::CargoShip);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorMiddle::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorMiddle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorMiddle::Interrupted() {}
