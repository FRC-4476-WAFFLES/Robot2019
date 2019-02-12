/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/PositionMiddle.h"
#include "Robot.h"

PositionMiddle::PositionMiddle(Command* Middle, Command* Not_Middle) :
  ConditionalCommand("PositionMiddle", Middle, Not_Middle)
{
  SetTimeout(15.0);
}

bool PositionMiddle::Condition() {
  if(*Robot::Info.targetSide.GetSelected() == 1){
    return true;
  }else if(*Robot::Info.targetSide.GetSelected() >= 2){
    return false;
  }else{
    fprintf(stderr, "Position Set incorrectly, defaulting to Middle-> PositionMiddle.cpp \n");
    return true;
  }
}
