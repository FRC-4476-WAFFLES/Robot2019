/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Climber/AutoClimb.h"
#include "commands/Climber/ClimberBuddy.h"
#include "commands/Climber/ClimberFullExtend.h"
#include "commands/Climber/ClimberFullIn.h"
#include "commands/Climber/ClimberHabLevel.h"
#include "commands/Climber/ClimberToggleFoot.h"
#include "commands/Climber/ClimberTogglePumping.h"
#include "commands/Climber/WaitForLegPosition.h"
#include "commands/Drive/DriveTime.h"
#include "commands/Drive/DriveInterruptable.h"
#include "commands/Auto/AutoWaitCommand.h"
#include "commands/Climber/WaitTrigger.h"

class Climb971Leg: public frc::CommandGroup {
public:
	Climb971Leg():
		CommandGroup("Climb971Leg")
	{
		AddSequential(new ClimberFullExtend());
    AddSequential(new WaitForLegPosition());
    AddSequential(new ClimberToggleFoot());
    AddSequential(new AutoWaitCommand(1));
    AddSequential(new ClimberToggleFoot());
    AddSequential(new DriveInterruptable());
    AddSequential(new AutoWaitCommand(1));
    AddSequential(new ClimberHabLevel());
    AddSequential(new DriveTime(1));
    AddSequential(new WaitTrigger());
    AddSequential(new ClimberBuddy());
    AddSequential(new WaitForLegPosition());
    AddSequential(new DriveTime(1));
    
	}
};

class Climb694Suction: public frc::CommandGroup {
public:
	Climb694Suction():
		CommandGroup("Climb694Suction")
	{
		
	}
};

AutoClimb::AutoClimb() {
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
  AddSequential(new Climb971Leg());
}
