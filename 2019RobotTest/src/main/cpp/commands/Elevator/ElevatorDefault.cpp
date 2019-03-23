/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Elevator/ElevatorDefault.h"
#include "Robot.h"

//nothing atm

ElevatorDefault::ElevatorDefault():
  frc::Command("ElevatorDefault")
{
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::Elevator);
}

// Called just before this Command runs the first time
void ElevatorDefault::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorDefault::Execute() {
  if(Robot::Intake.HasCargoIR() && !has_moved_to_level_one){
    Robot::Elevator.SeekTo(Robot::Elevator.Positions::Bottom);
    has_moved_to_level_one = true;
  }
  if(!Robot::Intake.HasCargoIR()){
    has_moved_to_level_one = false;
  }

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorDefault::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorDefault::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorDefault::Interrupted() {}
