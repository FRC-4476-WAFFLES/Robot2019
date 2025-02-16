/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/OI/OperatorModeSwitch.h"
#include "Robot.h"

OperatorModeSwitch::OperatorModeSwitch(): 
  frc::InstantCommand("OperatorModeSwitch")
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  
}

// Called once when the command executes
void OperatorModeSwitch::Initialize() {
  Robot::oi.climber_switch = !Robot::oi.climber_switch;
}
