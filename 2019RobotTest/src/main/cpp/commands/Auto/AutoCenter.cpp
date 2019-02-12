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
#include "commands/Drive/TrackingDrive.h"

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

class ApproachLeft: public CommandGroup {
public:
	ApproachLeft():
		CommandGroup("ApproachLeft")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class ApproachRight: public CommandGroup {
public:
	ApproachRight():
		CommandGroup("ApproachRight")
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

class BackOff: public CommandGroup {
public:
	BackOff():
		CommandGroup("BackOff")
	{
		AddSequential(new DriveAutoLines(-19.7, 0, 10, 0.9));
	}
};

class LeftFront: public CommandGroup {
public:
	LeftFront():
		CommandGroup("LeftFront")
	{
		AddSequential(new FrontLeftDrive());
		AddSequential(new TrackingDrive());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class LeftFirst: public CommandGroup {
public:
	LeftFirst():
		CommandGroup("LeftFirst")
	{
		AddSequential(new SideLeftDrive());
		AddSequential(new DriveToSlotOne());
		AddSequential(new ApproachLeft());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class LeftSecond: public CommandGroup {
public:
	LeftSecond():
		CommandGroup("LeftSecond")
	{
		AddSequential(new SideLeftDrive());
		AddSequential(new DriveToSlotTwo());
		AddSequential(new ApproachLeft());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class LeftThird: public CommandGroup {
public:
	LeftThird():
		CommandGroup("LeftThird")
	{
		AddSequential(new SideLeftDrive());
		AddSequential(new DriveToSlotThree());
		AddSequential(new ApproachLeft());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class RightFront: public CommandGroup {
public:
	RightFront():
		CommandGroup("RightFront")
	{
		AddSequential(new FrontRightDrive());
		AddSequential(new TrackingDrive());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class RightFirst: public CommandGroup {
public:
	RightFirst():
		CommandGroup("RightFirst")
	{
		AddSequential(new SideRightDrive());
		AddSequential(new DriveToSlotOne());
		AddSequential(new ApproachRight());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class RightSecond: public CommandGroup {
public:
	RightSecond():
		CommandGroup("RightSecond")
	{
		AddSequential(new SideRightDrive());
		AddSequential(new DriveToSlotTwo());
		AddSequential(new ApproachRight());
		AddSequential(new Drop());
		AddSequential(new BackOff());
	}
};

class RightThird: public CommandGroup {
public:
	RightThird():
		CommandGroup("RightThird")
	{
		AddSequential(new SideRightDrive());
		AddSequential(new DriveToSlotThree());
		AddSequential(new ApproachRight());
		AddSequential(new Drop());
		AddSequential(new BackOff());
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
					new PositionFar(new RightThird(), nullptr))))));

}	
