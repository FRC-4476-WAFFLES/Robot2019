/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveSubsystem.h"
#include <frc/SmartDashboard/SmartDashboard.h>
#include "Robot.h"
#include "RobotMap.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "commands/Drive/OperatorTankDrive.h"
#include "Utils/PIDPreferences.h"

DriveSubsystem::DriveSubsystem() : 
  frc::Subsystem("DriveSubsystem"),
  	left1(DRIVE_LEFT1),
		left2(DRIVE_LEFT2),
		left3(DRIVE_LEFT3),
		right1(DRIVE_RIGHT1),
		right2(DRIVE_RIGHT2),
		right3(DRIVE_RIGHT3),
		JasnoorLeft1(DRIVE_LEFT_JASNOOR_1),
		JasnoorLeft2(DRIVE_LEFT_JASNOOR_2),
		JasnoorLeft3(DRIVE_LEFT_JASNOOR_3),
		JasnoorRight1(DRIVE_RIGHT_JASNOOR_1),
		JasnoorRight2(DRIVE_RIGHT_JASNOOR_2),
		JasnoorRight3(DRIVE_RIGHT_JASNOOR_3)
{
	//sensors are quadratic (greyhills)
  left1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
	right1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);

	//current limiting
	left1.ConfigPeakCurrentDuration(30,10);
	left1.ConfigPeakCurrentLimit(22, 10);
	left1.ConfigContinuousCurrentLimit(22,10);
	left1.EnableCurrentLimit(true);

	right1.ConfigPeakCurrentDuration(30,10);
	right1.ConfigPeakCurrentLimit(22, 10);
	right1.ConfigContinuousCurrentLimit(22,10);
	right1.EnableCurrentLimit(true);

	right2.Follow(right1);
	right3.Follow(right1);
	left2.Follow(left1);
	left3.Follow(left1);
}

void DriveSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new OperatorTankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::Drive(float Left, float Right) {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
	left1.Set(ControlMode::PercentOutput, Left);
	right1.Set(ControlMode::PercentOutput, Right);
	JasnoorLeft1.Set(Left);
	JasnoorLeft2.Set(Left);
	JasnoorLeft3.Set(Left);
	JasnoorRight1.Set(-Right);
	JasnoorRight2.Set(-Right);
	JasnoorRight3.Set(-Right);
}

void DriveSubsystem::TrackingDrive(float Left, float Right){
	double kp = UpdateSinglePreference("camera p", -0.017);
	float otherkp = UpdateSinglePreference("skew kp", 0.004);
	double tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
	float ts = GetSkew();
	double skew_error = 1/(ts*otherkp);
	if(skew_error > 7){
		skew_error = 7;
	}else if(skew_error < -7){
		skew_error = -7;
	}
	tx = tx + skew_error;
	double error = kp*tx;
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 0);
	int tv = 	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0);
	if(tv == 0){
		Left = 0;
		Right = 0;
	}else if(error > -MIN_TRACKING_ERROR && error < 0){
		Left+= -MIN_TRACKING_ERROR;
		Right-= -MIN_TRACKING_ERROR;
	}else if(error < MIN_TRACKING_ERROR && error > 0){
		Left+= MIN_TRACKING_ERROR;
	  Right-= MIN_TRACKING_ERROR;
	}else{
		Left+=error;
		Right-=error;
	}
	left1.Set(ControlMode::PercentOutput, Left);
	right1.Set(ControlMode::PercentOutput, Right);
	JasnoorLeft1.Set(Left);
	JasnoorLeft2.Set(Left);
	JasnoorLeft3.Set(Left);
	JasnoorRight1.Set(-Right);
	JasnoorRight2.Set(-Right);
	JasnoorRight3.Set(-Right);
}

float DriveSubsystem::GetSkew(){
	float ts = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts", 0.0);
  if(ts < -45){
		ts+=90;
	}
	SmartDashboard::PutNumber("Drive/Skew", ts);
	return ts;
}

float DriveSubsystem::Right() {
  return right1.GetSelectedSensorPosition(0)*2;
}

float DriveSubsystem::Left() {
  return left1.GetSelectedSensorPosition(0)*2;
}

float DriveSubsystem::Gyro() {
  return gyro.GetAngle();
}

void DriveSubsystem::Prints(){
  SmartDashboard::PutNumber("Drive/LeftEncoder", Left());
	SmartDashboard::PutNumber("Drive/RightEncoder", Right());
	SmartDashboard::PutNumber("Drive/Gyro", Gyro());
	SmartDashboard::PutNumber("Drive/LeftOutput", left1.GetMotorOutputPercent());
	SmartDashboard::PutNumber("Drive/RightOutput", right1.GetMotorOutputPercent());

}