/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/SideState.h"
#include "Robot.h"
#include "iostream"

SideState::SideState(Command* Left, Command* Right) :
  ConditionalCommand("SideState", Left, Right)
{
  SetTimeout(15.0);
}

bool SideState::Condition() {
  if(*Robot::Info.targetSide.GetSelected() == 1){
    return true;
  }else if(*Robot::Info.targetSide.GetSelected() == 0){
    return false;
  }else{
    fprintf(stderr, "Position Set incorrectly, defaulting to left-> SideState.cpp \n");
    return true;
  }
}
