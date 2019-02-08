/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <frc/WPILib.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/ADXRS450_Gyro.h>
#include <frc/Talon.h>
#include <string>
#include <frc/Notifier.h>
#include <math.h>
#include <pathfinder.h>

using namespace frc;

class DriveSubsystem : public frc::Subsystem {
 public:
  DriveSubsystem();
  void InitDefaultCommand() override;
  void Drive(float Left, float Right);
  void TrackingDrive(float Left, float Right);
  float GetSkew();
  void Prints();
  float Right();
  float Left();
  float Gyro();
  void LoadPath(std::string name);
  bool IsPathFinished();
  void ClosePath();

  


	//pathfinder constants
	constexpr static float MAX_SPEED = 14.0; // feet/s
	constexpr static float MAX_ACCEL = 6.56; // feet/s/s
	constexpr static float MAX_JERK = 197; // feet/s/s/s
	constexpr static float ANGLE_P = 0.8;
	constexpr static float WHEELBASE = 2.0;

	constexpr static int COUNTS_PER_REV = 256;
	constexpr static double WHEEL_CIRCUMFERENCE = 6*M_PI;
	constexpr static double KI = 1;
	constexpr static double KP = 0;
	constexpr static double KD = 0;
	constexpr static double KV = 1/MAX_SPEED;
	constexpr static double KA = 0;
  

	PowerDistributionPanel PDP;

	double target_distance;
	double target_angle;
	double drive_speed_FPS = 0.0;
	static constexpr float MIN_TRACKING_ERROR = 0.05;
	bool missing_vision_target = false;
	bool is_tracking_drive = false;

	

 private:
	static void FollowDrivePath();
	WPI_TalonSRX left1;
	WPI_VictorSPX left2;
	WPI_VictorSPX left3;
	WPI_TalonSRX right1;
	WPI_VictorSPX right2;
	WPI_VictorSPX right3;
  	ADXRS450_Gyro gyro;

	Talon JasnoorLeft1;
	Talon JasnoorLeft2;
	Talon JasnoorLeft3;
	Talon JasnoorRight1;
	Talon JasnoorRight2;
	Talon JasnoorRight3;

	Notifier* follower_notifier;
	int left_trajectory_length;
	int right_trajectory_length;
	Segment* left_trajectory_segments;
	Segment* right_trajectory_segments;	
	EncoderFollower left_follower;
	EncoderFollower right_follower;
	EncoderConfig encoder_config_left;
	EncoderConfig encoder_config_right;

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
};
