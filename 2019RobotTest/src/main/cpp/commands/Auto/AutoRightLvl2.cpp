/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoRightLvl2.h"
#include "commands/Auto/AutoRightLvl1.h"
#include "Robot.h"

#include "commands/Drive/TrackingDrive.h"
#include "commands/Drive/DriveAutoLines.h"
#include "commands/Drive/PathFollower.h"

#include "commands/Auto/Switches/PositionFront.h"
#include "commands/Auto/Switches/SideState.h"
#include "commands/Auto/Switches/PositionClose.h"
#include "commands/Auto/Switches/PositionMiddle.h"
#include "commands/Auto/Switches/PositionFar.h"
#include "commands/Auto/Switches/GamepieceState.h"

#include "commands/Elevator/ElevatorBottom.h"
#include "commands/Elevator/ElevatorMiddle.h"
#include "commands/Elevator/ElevatorTop.h"

#include "commands/Intake/IntakeSet.h"
#include "commands/Intake/IntakeStop.h"

#include "commands/Hatch/ToggleClamp.h"
#include "commands/Hatch/ToggleDeploy.h"
#include "commands/Auto/AutoWaitCommand.h"

/*
instaid of re-writing my existing libraries of the level one autos, I decided to simply run the level 1
auto after some aditional code to get the robot off the platform. This code simply drives forward a set 
distance, then drives back to try to re-allign the robot with the starting postition of the level autos.
*/

AutoRightLvl2::AutoRightLvl2() : CommandGroup("AutoRightLvl2"){
  AddSequential(new DriveAutoLines(6.0, 0, 15, 0.4));
  AddSequential(new AutoWaitCommand(0.3));
  AddSequential(new DriveAutoLines(-3, 0, 15, 0.15));
  AddSequential(new AutoRightLvl1());
}
