/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoLeftLvl1.h"
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

/*
this year for autos we decided to try to make the autos *more* legible. did i do that? no. but i tried
this time around I opted for a long list of classes before every auto that can be run as commands, to 
sort of subdivide the autos into a series of editable and reusuable segments that can then be called 
individually to make the code more legible. Once the different classes are collated into the complete autos, 
they are selected by a long list of nested conditional commands that check the choosers on shuffleboard
to inform which command will be run. the classes do what thier names say using existing commands. the reason
for this is that alle the classes in this file are constructors that are not updated as the robot runs, 
what you see is what you get. this is a result of the auto chooser in robot. To make commands that update, 
you have to AddSequential the existing commands that will be updated by the scheduler as the robot runs.
*/

class ApproachLeft: public CommandGroup {
public:
	ApproachLeft():
		CommandGroup("ApproachLeft")
	{
		AddSequential(new ElevatorBottom());
		AddSequential(new GamepieceState(new ToggleDeploy(), nullptr));
		AddSequential(new TrackingDrive());
	}
};

class ApproachRight: public CommandGroup {
public:
	ApproachRight():
		CommandGroup("ApproachRight")
	{
		AddSequential(new ElevatorBottom());
		AddSequential(new GamepieceState(new ToggleDeploy(), nullptr));
		AddSequential(new TrackingDrive());
	}
};

class Drop: public CommandGroup {
public:
	Drop():
		CommandGroup("Drop")
	{
		AddSequential(new ElevatorBottom());
		AddSequential(new GamepieceState(new ToggleClamp(), new IntakeSet(1)));//TODO: check direction
	}
};

class BackOff: public CommandGroup {
public:
	BackOff():
		CommandGroup("BackOff")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));//TODO: make real
	}
};

class DriveToSlotOne: public CommandGroup {
public:
	DriveToSlotOne():
		CommandGroup("DriveToSlotOne")
	{
		AddSequential(new PathFollower("lefttoone"));//TODO: make real
	}
};

class DriveToSlotTwo: public CommandGroup {
public:
	DriveToSlotTwo():
		CommandGroup("DriveToSlotTwo")
	{
		AddSequential(new PathFollower("lefttotwo"));//TODO: make real
	}
};

class DriveToSlotThree: public CommandGroup {
public:
	DriveToSlotThree():
		CommandGroup("DriveToSlotThree")
	{
		AddSequential(new PathFollower("lefttothree"));//TODO: make real
	}
};

class SlotOne: public CommandGroup {
public:
	SlotOne():
		CommandGroup("SlotOne")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));//TODO: make real
	}
};

class SlotTwo: public CommandGroup {
public:
	SlotTwo():
		CommandGroup("SlotTwo")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));//TODO: make real
	}
};

class SlotThree: public CommandGroup {
public:
	SlotThree():
		CommandGroup("SlotThree")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));//TODO: make real
	}
};

AutoLeftLvl1::AutoLeftLvl1() : CommandGroup("AutoLeftLvl1"){

}
