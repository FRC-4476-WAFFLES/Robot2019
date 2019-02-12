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

AutoCenter::AutoCenter() {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
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
  int* current_target_position = Robot::target_position;

}
