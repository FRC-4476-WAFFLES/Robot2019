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
  SetTimeout(15.0);
}

bool GamepieceState::Condition() {
  if(*Robot::Info.preload.GetSelected() == 0){
    return true;
  }else if(*Robot::Info.preload.GetSelected() == 1){
    return false;
  }else{
    fprintf(stderr, "preload Set incorrectly, defaulting to Hatch-> GamepieceState.cpp \n");
    return true;
  }
}
