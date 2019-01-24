/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h>
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <frc/WPILib.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/ADXRS450_Gyro.h>
using namespace frc;

class DriveSubsystem : public frc::Subsystem {
 public:
  DriveSubsystem();
  void InitDefaultCommand() override;
  void Drive(float Left, float Right);
  void Prints();
  float Right();
  float Left();
  float Gyro();

  
  constexpr static float MAX_SPEED = 1.0; // feet/s
	constexpr static float MAX_ACCEL = 1.0; // feet/s/s
	constexpr static float MAX_JERK = 10.0; // feet/s/s/s
	constexpr static float ANGLE_P = 0.8;
	PowerDistributionPanel PDP;

	double target_distance;
	double target_angle;
	double drive_speed_FPS = 0.0;

 private:
	WPI_TalonSRX left1;
	WPI_VictorSPX left2;
	WPI_VictorSPX left3;
	WPI_TalonSRX right1;
	WPI_VictorSPX right2;
	WPI_VictorSPX right3;
  	ADXRS450_Gyro gyro;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
};
