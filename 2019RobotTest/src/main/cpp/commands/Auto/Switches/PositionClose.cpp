/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/PositionClose.h"
#include "Robot.h"

PositionClose::PositionClose(Command* Close, Command* Not_Close) :
  ConditionalCommand("PositionClose", Close, Not_Close)
{
  SetTimeout(15.0);
}

bool PositionClose::Condition() {
  if(*Robot::Info.targetSide.GetSelected() == 0){
    return true;
  }else if(*Robot::Info.targetSide.GetSelected() >= 1){
    return false;
  }else{
    fprintf(stderr, "Position Set incorrectly, defaulting to Close-> PositionClose.cpp \n");
    return true;
  }
}
