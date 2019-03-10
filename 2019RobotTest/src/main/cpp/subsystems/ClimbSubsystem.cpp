/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimbSubsystem.h"

#include "RobotMap.h"
//does nothing rn

ClimbSubsystem::ClimbSubsystem() :
 frc::Subsystem("ClimbSubsystem")//,
 //climbMaster(CLIMB_MASTER, CANSparkMax::MotorType::kBrushless),
 //climbFollower(CLIMB_FOLLOWER, CANSparkMax::MotorType::kBrushless) 
 {
  //  climbFollower.Follow(climbMaster, false);
 }

void ClimbSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
