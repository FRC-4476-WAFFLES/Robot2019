/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive/OperatorTankDrive.h"
#include "../include/subsystems/DriveSubsystem.h"
#include "OI.h"
#include "Robot.h"

OperatorTankDrive::OperatorTankDrive() {
  Requires(&Robot::Drive);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

void OperatorTankDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorTankDrive::Execute() {
	if(Robot::oi.left.GetRawButton(6) || Robot::oi.left.GetRawButton(7)){
		Robot::Drive.TrackingDrive(-0.2, -0.2);
	}else {
	Robot::Drive.Drive(Robot::oi.left.GetY(), Robot::oi.right.GetY());
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorTankDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorTankDrive::End() {
	Robot::Drive.Drive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorTankDrive::Interrupted() {
	End();
}
