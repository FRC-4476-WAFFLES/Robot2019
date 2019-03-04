/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Elevator/ElevatorAutoManual.h"
#include "Robot.h"

ElevatorAutoManual::ElevatorAutoManual() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ElevatorAutoManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorAutoManual::Execute() {
  if(Robot::oi.operate.GetRawButton(Robot::oi.B)){
    Robot::Elevator.SeekTo(Robot::Elevator.Positions::Ground);
  }else if(Robot::oi.operate.GetRawButton(Robot::oi.A)){
    Robot::Elevator.SeekTo(Robot::Elevator.Positions::Bottom);
  }else if(Robot::oi.operate.GetRawButton(Robot::oi.X)){
    Robot::Elevator.SeekTo(Robot::Elevator.Positions::Middle);
  }else if(Robot::oi.operate.GetRawButton(Robot::oi.Y)){
    Robot::Elevator.SeekTo(Robot::Elevator.Positions::Top);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorAutoManual::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorAutoManual::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorAutoManual::Interrupted() {}
