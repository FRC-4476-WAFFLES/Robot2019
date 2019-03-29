/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimbSubsystem.h"
#include "Utils/PIDPreferences.h"
#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
//#include <iostream>

#include "RobotMap.h"
//does nothing rn

ClimbSubsystem::ClimbSubsystem() :
 frc::Subsystem("ClimbSubsystem"), 
 climberLegMaster(CLIMBER_ELEVATOR_MASTER), 
 climberLegFollower(CLIMBER_ELEVATOR_FOLLOWER),
 suctionClamp(CLIMBER_CLAMP, CLIMBER_UNCLAMP),
 leftElectromagnetLock(CLIMBER_LOCK_LEFT),
 rightElectromagnetLock(CLIMBER_LOCK_RIGHT)
 //,
 //climbMaster(CLIMB_MASTER, CANSparkMax::MotorType::kBrushless),
 //climbFollower(CLIMB_FOLLOWER, CANSparkMax::MotorType::kBrushless) 
 {
  //  climbFollower.Follow(climbMaster, false);
  //current limiting
  climberLegMaster.ConfigPeakCurrentDuration(30, 10);
  climberLegMaster.ConfigPeakCurrentLimit(22, 10);
  climberLegMaster.ConfigContinuousCurrentLimit(15, 10);
  climberLegMaster.EnableCurrentLimit(true);
  climberLegMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
  climberLegMaster.SetSelectedSensorPosition(0);

  climberLegFollower.ConfigPeakCurrentDuration(30, 10);
  climberLegFollower.ConfigPeakCurrentLimit(22, 10);
  climberLegFollower.ConfigContinuousCurrentLimit(15, 10);
  climberLegFollower.EnableCurrentLimit(true);
  //follow code
  climberLegFollower.Follow(climberLegMaster);
 }

void ClimbSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ClimbSubsystem::Periodic(){

}

void ClimbSubsystem::ClimbTo(int target){
  leg_target = target;
}

void ClimbSubsystem::TogglePumping(){
  pumping = !pumping;
}

bool ClimbSubsystem::ShouldPumping(){
  return pumping;
}

void ClimbSubsystem::ToggleEMLock(){
  locking = !locking;
}

int ClimbSubsystem::GetFootState(){
  return foot_position;
}

int ClimbSubsystem::GetLegPosition(){
  return climberLegMaster.GetSelectedSensorPosition(0);
}

void ClimbSubsystem::Prints(){
  SmartDashboard::PutNumber("Climbe/Leg Encoder", GetLegPosition());
  SmartDashboard::PutNumber("Climber/Foot State", GetFootState());
}