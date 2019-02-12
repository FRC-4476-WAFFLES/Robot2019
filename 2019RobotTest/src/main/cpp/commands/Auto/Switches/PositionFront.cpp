/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/PositionFront.h"
#include "Robot.h"

PositionFront::PositionFront(Command* Front, Command* Not_Front) :
  ConditionalCommand("PositionFront", Front, Not_Front)
{
  SetTimeout(15.0);
}

bool PositionFront::Condition() {
  if(*Robot::Info.targetSide.GetSelected() == 1){
    return true;
  }else if(*Robot::Info.targetSide.GetSelected() == 0){
    return false;
  }else{
    fprintf(stderr, "Position Set incorrectly, defaulting to Front-> PositionFront.cpp \n");
    return true;
  }
}
