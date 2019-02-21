/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/Switches/GamepieceState.h"
#include "Robot.h"

GamepieceState::GamepieceState(Command* Hatch, Command* Cargo) :
  ConditionalCommand("GamepieceState", Hatch, Cargo)
{
  //tells the class what command to run based on the reutrn value of the Condition() function
  SetTimeout(15.0);
}

bool GamepieceState::Condition() {
  //getting the state input from shuffleboard to tell us what gamepiece we start with, and using that to choose between two (sets) of comands
  //uses the conditional command to run one of two commands when called 
  if(*Robot::Info.preload.GetSelected() == 0){
    //if we have a hatch(default), run the input for the hatch
    return true;
  }else if(*Robot::Info.preload.GetSelected() == 1){
    return false;
  }else{
    fprintf(stderr, "preload Set incorrectly, defaulting to Hatch-> GamepieceState.cpp \n");
    return true;
  }
}
