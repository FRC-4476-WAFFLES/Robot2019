/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoCenter.h"

#include "Robot.h"
#include "commands/Drive/DriveAutoLines.h"
#include "commands/Drive/PathFollower.h"
#include "commands/Auto/Switches/PositionFront.h"
#include "commands/Auto/Switches/SideState.h"
#include "commands/Auto/Switches/PositionClose.h"
#include "commands/Auto/Switches/PositionMiddle.h"
#include "commands/Auto/Switches/PositionFar.h"

class FrontLeftDrive: public CommandGroup {
public:
	FrontLeftDrive():
		CommandGroup("FrontLeftDrive")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class FrontRightDrive: public CommandGroup {
public:
	FrontRightDrive():
		CommandGroup("FrontRightDrive")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class SideLeftDrive: public CommandGroup {
public:
	SideLeftDrive():
		CommandGroup("SideLeftDrive")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class SideRightDrive: public CommandGroup {
public:
	SideRightDrive():
		CommandGroup("SideRightDrive")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class DriveToSlotOne: public CommandGroup {
public:
	DriveToSlotOne():
		CommandGroup("DriveToSlotOne")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class DriveToSlotTwo: public CommandGroup {
public:
	DriveToSlotTwo():
		CommandGroup("DriveToSlotTwo")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class DriveToSlotThree: public CommandGroup {
public:
	DriveToSlotThree():
		CommandGroup("DriveToSlotThree")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class Approach: public CommandGroup {
public:
	Approach():
		CommandGroup("Approach")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class Drop: public CommandGroup {
public:
	Drop():
		CommandGroup("Drop")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class LeftFront: public CommandGroup {
public:
	LeftFront():
		CommandGroup("LeftFront")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class LeftFirst: public CommandGroup {
public:
	LeftFirst():
		CommandGroup("LeftFirst")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class LeftSecond: public CommandGroup {
public:
	LeftSecond():
		CommandGroup("LeftSecond")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class LeftThird: public CommandGroup {
public:
	LeftThird():
		CommandGroup("LeftThird")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class RightFront: public CommandGroup {
public:
	RightFront():
		CommandGroup("RightFront")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class RightFirst: public CommandGroup {
public:
	RightFirst():
		CommandGroup("RightFirst")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class RightSecond: public CommandGroup {
public:
	RightSecond():
		CommandGroup("RightSecond")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class RightThird: public CommandGroup {
public:
	RightThird():
		CommandGroup("RightThird")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};


AutoCenter::AutoCenter() {
/*
  AutonomousChooser.SetDefaultOption("Null", nullptr);
  AutonomousChooser.AddOption("Test", &TestAuto);
  AutonomousChooser.AddOption("Center", &CenterAuto);
  AutonomousChooser.AddOption("Left Level 1", &LeftLvl1Auto);
  AutonomousChooser.AddOption("Left Level 2", &LeftLvl2Auto);
  AutonomousChooser.AddOption("Right Level 1", &RightLvl1Auto);
  AutonomousChooser.AddOption("Right Level 2", &RightLvl2Auto);

  targetPosition.SetDefaultOption("Close", new int(0));
  targetPosition.AddOption("Middle", new int(1));
  targetPosition.AddOption("Far", new int(2));
	targetPosition.AddOption("Front Left", new int(3));
	targetPosition.AddOption("Front Right", new int(4));

  targetSide.SetDefaultOption("Right", new int(0));
  targetSide.AddOption("Left", new int(1));
*/
	AddSequential(new SideState(
		new PositionFront(new LeftFront(), 
			new PositionClose(new LeftFirst(),
				new PositionMiddle(new LeftSecond(),
					new PositionFar(new LeftThird(), nullptr)))),
		new PositionFront(new RightFront(),
			new PositionClose(new RightFirst(), 
				new PositionMiddle(new RightSecond(), 
					new PositionFar(new RightThird(), nullptr))))))

}	
