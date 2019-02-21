/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/SideState.h"
#include "Robot.h"

SideState::SideState(Command* Left, Command* Right) :
  ConditionalCommand("SideState", Left, Right)
{
  //tells the class what command to run based on the reutrn value of the Condition() function
  SetTimeout(15.0);
}

bool SideState::Condition() {
  //getting the state input from shuffleboard to tell us what side the target we are looking for is on, and using that to choose between two (sets) of comands
  //uses the conditional command to run one of two commands when called
  if(*Robot::Info.targetSide.GetSelected() == 1){
    //if if the postition is left(default), run the input for left
    return true;
  }else if(*Robot::Info.targetSide.GetSelected() == 0){
    return false;
  }else{
    fprintf(stderr, "Side Set incorrectly, defaulting to left-> SideState.cpp \n");
    return true;
  }
}
