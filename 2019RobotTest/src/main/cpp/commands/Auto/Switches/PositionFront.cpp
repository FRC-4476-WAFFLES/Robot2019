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
  //tells the class what command to run based on the reutrn value of the Condition() function
  SetTimeout(15.0);
}

bool PositionFront::Condition() {
  //getting the state input from shuffleboard to tell us what target we are looking for, and using that to choose between two (sets) of comands
  //uses the conditional command to run one of two commands when called
  if(*Robot::Info.targetPosition.GetSelected() == 3){
    //if if the postition is front(default), run the input for front
    return true;
  }else if(*Robot::Info.targetPosition.GetSelected() != 3){
    return false;
  }else{
    fprintf(stderr, "Position Set incorrectly, defaulting to Front-> PositionFront.cpp \n");
    return true;
  }
}
