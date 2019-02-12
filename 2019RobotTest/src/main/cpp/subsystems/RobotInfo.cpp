/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/RobotInfo.h"
#include "frc/smartdashboard/SmartDashboard.h"

RobotInfo::RobotInfo() : Subsystem("ExampleSubsystem") {
  targetPosition.SetDefaultOption("Close", new int(0));
  targetPosition.AddOption("Middle", new int(1));
  targetPosition.AddOption("Far", new int(2));
	targetPosition.AddOption("Front", new int(3));
	SmartDashboard::PutData("Aim for ____ position", &targetPosition);
  


  targetSide.SetDefaultOption("Right", new int(0));
  targetSide.AddOption("Left", new int(1));
	SmartDashboard::PutData("Target Side", &targetSide);


  preload.SetDefaultOption("Hatch", new int(0));
  preload.AddOption("Cargo", new int(1));
	SmartDashboard::PutData("Preload Gamepiece", &preload);
}

void RobotInfo::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
