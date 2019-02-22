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

OperatorTankDrive::OperatorTankDrive() :
	frc::Command("OperatroTankDrive")
{
  Requires(&Robot::Drive);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

void OperatorTankDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorTankDrive::Execute() {
	if(Robot::oi.right.GetRawButton(10) || Robot::oi.right.GetRawButton(11)){
		Robot::Drive.TrackingDrive(-0.25, -0.25);
	}else {
	Robot::Drive.WafflesDrive(Robot::oi.left.GetY(), Robot::oi.right.GetY());
	}
	if(!Robot::Drive.is_turning_tracking){
		if(Robot::Drive.AvgDriveOut()> 0.17 && !has_toggled){
			has_toggled = true;
			Robot::Hatch.UpdateHatch(!Robot::Hatch.current_clamp_state, Robot::Hatch.current_deploy_state);
		}
	}
	if(!Robot::Drive.is_turning_tracking && !Robot::Drive.is_tracking_drive){
		has_toggled = false;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorTankDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void OperatorTankDrive::End() {
	Robot::Drive.WafflesDrive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorTankDrive::Interrupted() {
	End();
}
