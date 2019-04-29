/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive/ALittleBitOfDefenceInmyLife.h"
#include "Robot.h"

ALittleBitOfDefenceInmyLife::ALittleBitOfDefenceInmyLife() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called once when the command executes
void ALittleBitOfDefenceInmyLife::Initialize() {
  Robot::Hatch.UpdateHatch(true, false);
  Robot::Elevator.def_mode = true;
  
}
