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
#include <math.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "commands/Drive/OperatorTankDrive.h"
#include "Utils/PIDPreferences.h"
#include "pathfinder-frc.h"
#include <iostream>
using namespace std;


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

	velocity_time.Start();
}

void DriveSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new OperatorTankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveSubsystem::WafflesDrive(float Left, float Right) {
	if(velocity_time.Get()>0.1){
		left_vel_segment = this->Left() - last_left_val;
		right_vel_segment = this->Right() - last_right_val;
		last_left_val = this->Left();
		last_right_val = this->Right(); 
		velocity_time.Reset();
		velocity_time.Start();
	}
	velocity_encoder_segment = fabs( ( fabs(left_vel_segment) + fabs(right_vel_segment)) - velocity_encoder_segment);
	Robot::Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Driver);
	// Robot::Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Vision);
	left1.Set(ControlMode::PercentOutput, -Left);
	right1.Set(ControlMode::PercentOutput, Right);

	missing_vision_target = false;
	is_tracking_drive = false;
	is_turning_tracking = false;
	last_angle_error = 0;
	last_time.Stop();
	if(Robot::oi.left.GetRawButton(1) && Robot::oi.right.GetRawButton(1)){
		gyro.Reset();
	}
}

void DriveSubsystem::TrackingDrive(float Left, float Right){
	if(last_time.Get()> 1){
		//keep track of where we are in the vision prosses
		is_tracking_drive = true;
		is_turning_tracking = true;
	}else{
		//keep track of where we are in the vision prosse		
	}

	//Timekeeping
	last_time.Reset();
	last_time.Start();
	double time = last_time.Get();
	//Turn on Vision code
	Robot::Camera.SetCameraProcessingMode(Robot::Camera.ProcessingMode::Vision);
	Robot::Camera.SetLedMode(Robot::Camera.CameraLEDMode::On);
	//Get the PID values
	double kp_turning = UpdateSinglePreference("camera turning p", -0.003);
	double kd_turning = UpdateSinglePreference("camera turning d", -0.017);
	double kp_driving = UpdateSinglePreference("camera driving p", -0.017);
	double kd_driving = UpdateSinglePreference("camera driving d", -0.017);
	double kp_forwards = UpdateSinglePreference("camera area coefficient", 0.35);
	//Get values from the camera
	double area = Robot::Camera.GetCameraTA();
	double tx = Robot::Camera.GetCameraTX();
	int tv = Robot::Camera.GetCameraTV();
	// double distance = GetHorizontalDistace();//from horizontal distance
	//get the driving forewards speed -- disabled
	// // Left = kp_forwards*distance;//from horizontal distance
	// Left = Left*(1/(area*kp_forwards));
	// if(fabs(Left) <0.1){
	// 	Left = 0.1*(Left/fabs(Left));
	// }
	// // Right = kp_forwards*distance;//from horizontal distance
	// Right = Right*(1/(area*kp_forwards));
	// if(fabs(Right) <0.1){
	// 	Right = 0.1*(Right/fabs(Right));
	// }--disabled

	//calculate error for coarse and fine adjust 
	double error = 0;
	double error2 =0;
	if(is_turning_tracking){
		//coarse adjust error calculations
		error = kp_turning*tx;
		error2 = error;
	}else{
		//fine adjust error calculations
		std::cout << "fine"<<std::endl;
		error = kp_turning*tx;
		error2 = kp_driving*tx;
	}
	
	if(tv == 0){
		//check from missing target
		Left = 0;
		Right = 0;
		missing_vision_target = true;
	}else if(fabs(error) < acceptable_error){
		//coarse adjust output to motors selected
		Left+=error2*10;
		Right-=error2*10;
		missing_vision_target = false;
		is_turning_tracking = false;
	}else{
		//fine adjust while driving foreward
		kd_turning = (kd_turning/time) * (-tx + last_angle_error);
		double angle_out = clamp(kd_turning + tx*kp_turning, -0.45, 0.45);
		Left = (error2)*10;
		Right = -(error2)*10;
		is_turning_tracking = true;
		last_angle_error = tx;
	}
	SmartDashboard::PutNumber("Drive/trackingError", error);
	SmartDashboard::PutNumber("Drive/horizontalDistToTarget", GetHorizontalDistace());
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
	SmartDashboard::PutNumber("Camera/TX", Robot::Camera.GetCameraTX());
	SmartDashboard::PutNumber("Drive/AvgDriveOut", AvgDriveOut());
	SmartDashboard::PutNumber("Drive/AvgVel", GetAvgVel());
	SmartDashboard::PutNumber("Drive/encdif", velocity_encoder_segment);
	SmartDashboard::PutNumber("Drive/horizontalDistToTarget", GetHorizontalDistace());
	SmartDashboard::PutNumber("Drive/TanOutput", tan(CAMERA_ANGLE * (PI / 180.0)));
	SmartDashboard::PutNumber("Drive/ty u lik this", Robot::Camera.GetCameraTY());
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

double DriveSubsystem::clamp(double value, double min, double max) {
	//function to make sure a givien value doesn't exceed the given parameters.
	if(value < min) {
		return min;
	} else if(value > max) {
		return max;
	} else {
		return value;
	}
}

double DriveSubsystem::GetAvgVel(){
	return velocity_encoder_segment;  
}

double DriveSubsystem::GetHorizontalDistace(){
	CAMERA_ANGLE = UpdateSinglePreference("Camera Angle", CAMERA_ANGLE);
	return ((CAMERA_HEIGHT - TARGET_HEIGHT) / tan((CAMERA_ANGLE - Robot::Camera.GetCameraTY()) * (PI / 180.0))) - HATCH_OFFSET_DIST;
}
