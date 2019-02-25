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
	//make sure no other command is setting the drive
  Requires(&Robot::Drive);
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

void OperatorTankDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OperatorTankDrive::Execute() {
  //check if the driver is requesting vision assistance
	if(Robot::oi.right.GetRawButton(10) || Robot::oi.right.GetRawButton(11)){
		if(!has_set){
			has_set = true;
			Robot::Drive.target_angle = Robot::Camera.GetCameraTX() + Robot::Drive.Gyro();
		}
		Robot::Drive.TrackingDrive(-0.25, -0.25);
	}else {
    //set the drive to the y axis of the joysticks
	  Robot::Drive.WafflesDrive(Robot::oi.left.GetY(), Robot::oi.right.GetY());
	}
	if(!Robot::Drive.is_turning_tracking){
    //if we're in the drive strait part of vision tracking, and we are very close to the target, then
    //change the clamp state to pick up or drop off a hatch. 
		if(Robot::Drive.AvgDriveOut()> 0.17 && !has_toggled){
			has_toggled = true;
      //                                   opposite                            same
			Robot::Hatch.UpdateHatch(!Robot::Hatch.current_clamp_state, Robot::Hatch.current_deploy_state);
		}
	}
	if(!Robot::Drive.is_turning_tracking && !Robot::Drive.is_tracking_drive){
    //if we aren't vision tracking then next time we are we can auto clamp again
		has_toggled = false;
		has_set = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorTankDrive::IsFinished() {
  //the only reason this command isn't running is if its auto
	return false;
}

// Called once after isFinished returns true
void OperatorTankDrive::End() {
  //stop drive
	Robot::Drive.WafflesDrive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorTankDrive::Interrupted() {
  //do end
	End();
}
