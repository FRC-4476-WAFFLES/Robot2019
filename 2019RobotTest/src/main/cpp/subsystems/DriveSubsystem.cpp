/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"
#include "RobotMap.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "commands/Drive/OperatorTankDrive.h"
#include "Utils/PIDPreferences.h"
#include "pathfinder-frc.h"


DriveSubsystem::DriveSubsystem() : 
  frc::Subsystem("DriveSubsystem"),
  	left1(DRIVE_LEFT1),
		left2(DRIVE_LEFT2),
		left3(DRIVE_LEFT3),
		right1(DRIVE_RIGHT1),
		right2(DRIVE_RIGHT2),
		right3(DRIVE_RIGHT3)
{
	//sensors are quadratic (greyhills)
  left1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
	right1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
	right1.SetSensorPhase(false);
	left1.SetSensorPhase(true);
	right1.SetSelectedSensorPosition(0);
	left1.SetSelectedSensorPosition(0);
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
	//pathfinder
	follower_notifier = new Notifier(this->FollowDrivePath);
	left_trajectory_segments = new Segment[10000];
	right_trajectory_segments = new Segment[10000];

	KP = UpdateSinglePreference("path k", KP);
	KI = UpdateSinglePreference("path i", KI);
	KD = UpdateSinglePreference("path d", KD);
	KV = UpdateSinglePreference("path v", KV);
	KA = UpdateSinglePreference("path a", KA);

}

void DriveSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new OperatorTankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::WafflesDrive(float Left, float Right) {
	Robot::Camera.SetCameraProcessingMode(1);
	Robot::Camera.SetLedMode(Robot::Camera.CameraLEDMode::Off);
	left1.Set(ControlMode::PercentOutput, -Left);
	right1.Set(ControlMode::PercentOutput, Right);
	missing_vision_target = false;
	is_tracking_drive = false;
}

void DriveSubsystem::TrackingDrive(float Left, float Right){
	Robot::Camera.SetCameraProcessingMode(0);
	is_tracking_drive = true;
	double kp_turning = UpdateSinglePreference("camera turning p", -0.017);
	double kp_driving = UpdateSinglePreference("camera driving p", -0.017);
	double kp_forwards = UpdateSinglePreference("camera area coefficient", 0.017);
	double area = Robot::Camera.GetCameraTA();
	float otherkp = UpdateSinglePreference("skew kp", 0.004);
	double tx = Robot::Camera.GetCameraTX();
	float ts = GetSkew();
	Left = Left*(1/(area*kp_forwards));
	Right = Right*(1/(area*kp_forwards));
	double skew_error = 1/(ts*otherkp);
	if(skew_error > 7){
		skew_error = 7;
	}else if(skew_error < -7){
		skew_error = -7;
	}
	tx = tx; //+ skew_error;
	 double error = 0;
	if(is_turning_tracking){
		error = kp_turning*tx;
	}else{
		error = kp_driving*tx;
	}
	
	Robot::Camera.SetLedMode(Robot::Camera.CameraLEDMode::On);
	int tv = Robot::Camera.GetCameraTV();
	if(tv == 0){
		Left = 0;
		Right = 0;
		missing_vision_target = true;
	}else if(fabs(error) < acceptable_error){
		if(error > -MIN_TRACKING_ERROR && error < 0){
			Left+= -MIN_TRACKING_ERROR;
			Right-= -MIN_TRACKING_ERROR;
			missing_vision_target = false;
			is_turning_tracking = false;
		}else if(error < MIN_TRACKING_ERROR && error > 0){
			Left+= MIN_TRACKING_ERROR;
			Right-= MIN_TRACKING_ERROR;
			missing_vision_target = false;
			is_turning_tracking = false;
		}else{
			Left+=error;
			Right-=error;
			missing_vision_target = false;
			is_turning_tracking = false;
		}
	}else{
		Left = error*10;
		Right = -error*10;
		is_turning_tracking = true;
	}
	SmartDashboard::PutNumber("Drive/trackingError", error);
	left1.Set(ControlMode::PercentOutput, -Left);
	right1.Set(ControlMode::PercentOutput, Right);
}

float DriveSubsystem::GetSkew(){
	float ts = Robot::Camera.GetCameraTS();
  if(ts < -45){
		ts+=90;
	}
	SmartDashboard::PutNumber("Drive/Skew", ts);
	return ts;
}

float DriveSubsystem::Right() {
  return right1.GetSelectedSensorPosition(0);
}

float DriveSubsystem::Left() {
  return left1.GetSelectedSensorPosition(0);
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

void DriveSubsystem::LoadPath(std::string name){
	left_trajectory_length = PathfinderFRC::get_trajectory(name + ".left", left_trajectory_segments);
	right_trajectory_length = PathfinderFRC::get_trajectory(name + ".right", right_trajectory_segments);

	left_follower.last_error = 0; left_follower.segment = 0; left_follower.finished = 0;
	right_follower.last_error = 0; right_follower.segment = 0; right_follower.finished = 0;
	KP = UpdateSinglePreference("path k", KP);
	KI = UpdateSinglePreference("path i", KI);
	KD = UpdateSinglePreference("path d", KD);
	KV = UpdateSinglePreference("path v", KV);
	KA = UpdateSinglePreference("path a", KA);
	
	encoder_config_left.initial_position = Left();
	encoder_config_left.ticks_per_revolution = COUNTS_PER_REV;
	encoder_config_left.wheel_circumference = WHEEL_CIRCUMFERENCE;
	encoder_config_left.kp = KP;
	encoder_config_left.ki = KI;
	encoder_config_left.kd = KD;
	encoder_config_left.kv = KV;
	encoder_config_left.ka = KA;

	encoder_config_right.initial_position = Right();
	encoder_config_right.ticks_per_revolution = COUNTS_PER_REV;
	encoder_config_right.wheel_circumference = WHEEL_CIRCUMFERENCE;
	encoder_config_right.kp = KP;
	encoder_config_right.ki = KI;
	encoder_config_right.kd = KD;
	encoder_config_right.kv = KV;
	encoder_config_right.ka = KA;

	follower_notifier->StartPeriodic(left_trajectory_segments[0].dt);
}

void DriveSubsystem::FollowDrivePath(){
	DriveSubsystem *sub = &Robot::Drive;
	double l = pathfinder_follow_encoder(sub->encoder_config_left, &sub->left_follower, sub->left_trajectory_segments, sub->left_trajectory_length, sub->Left());
	double r = pathfinder_follow_encoder(sub->encoder_config_right, &sub->right_follower, sub->right_trajectory_segments, sub->right_trajectory_length, sub->Right());
	sub->WafflesDrive(-l, -r);
}

bool DriveSubsystem::IsPathFinished(){
	return left_follower.finished && right_follower.finished;
}

void DriveSubsystem::ClosePath(){
	follower_notifier->Stop();
	WafflesDrive(0,0);
}

double DriveSubsystem::AvgDriveOut(){
	return (left1.GetMotorOutputPercent()+right1.GetMotorOutputPercent())/2;
}