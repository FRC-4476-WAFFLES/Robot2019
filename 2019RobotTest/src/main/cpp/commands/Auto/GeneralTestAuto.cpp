/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/GeneralTestAuto.h"
#include "../commands/Drive/DriveAutoLines.h"

GeneralTestAuto::GeneralTestAuto() :
 CommandGroup("GeneralTestAuto") 
{
  AddSequential(new DriveAutoLines(10, 0))
  AddSequential(new DriveAutoLines(0, 90))

}
