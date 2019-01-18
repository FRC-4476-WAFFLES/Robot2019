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

class DriveSubsystem : public frc::Subsystem {
 public:
  DriveSubsystem();
  void InitDefaultCommand() override;
  void Drive(float Left, float Right);
  void Prints();
  float Right();
  float Left();
  float Gyro();

  WPI_TalonSRX left1;
	WPI_VictorSPX left2;
	WPI_VictorSPX left3;
	WPI_TalonSRX right1;
	WPI_VictorSPX right2;
	WPI_VictorSPX right3;
  ADXRS450_Gyro gyro;

 private:

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
};
