/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/PositionFar.h"
#include "Robot.h"

PositionFar::PositionFar(Command* Far, Command* Not_Far) :
  ConditionalCommand("PositionFar", Far, Not_Far)
{
  SetTimeout(15.0);
}

bool PositionFar::Condition() {
  if(*Robot::Info.targetSide.GetSelected() == 2){
    return true;
  }else if(*Robot::Info.targetSide.GetSelected() > 3){
    return false;
  }else{
    fprintf(stderr, "Position Set incorrectly, defaulting to left-> PositionFar.cpp \n");
    return true;
  }
}
