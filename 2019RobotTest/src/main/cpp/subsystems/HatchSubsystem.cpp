/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchSubsystem.h"

#include "RobotMap.h"
#include "iostream"


HatchSubsystem::HatchSubsystem() :
 frc::Subsystem("HatchSubsystem"),
 //     true            false
 hatchDeploy(HATCH_EXTEND, HATCH_UNEXTEND),
 hatchClamp(HATCH_CLAMP, HATCH_UNCLAMP) 
 {

 }

void HatchSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void HatchSubsystem::Periodic(){
  std::cout << "current clamp state" << std::endl;
  std::cout << current_clamp_state << std::endl;
  std::cout << next_clamp_state << std::endl;

  if(current_clamp_state != next_clamp_state){
    current_clamp_state = next_clamp_state;
    if(next_clamp_state){
      std::cout << "in clamp change periodic" << std::endl;
      hatchClamp.Set(DoubleSolenoid::Value::kForward);
    }else{
      hatchClamp.Set(DoubleSolenoid::Value::kReverse);
    }
  }
  if(current_deploy_state != next_deploy_state){
    current_deploy_state = next_deploy_state;
    if(next_deploy_state){
      hatchDeploy.Set(DoubleSolenoid::Value::kForward);
    }else{
      hatchDeploy.Set(DoubleSolenoid::Value::kReverse);
    }
  }
}
void HatchSubsystem::UpdateHatch(bool clamp, bool deploy){
  if(clamp != current_clamp_state){
    next_clamp_state = clamp;
  }
  if(deploy != current_deploy_state){
    next_deploy_state = deploy;
  }
}
bool HatchSubsystem::HasPannel(){
  return false;
}