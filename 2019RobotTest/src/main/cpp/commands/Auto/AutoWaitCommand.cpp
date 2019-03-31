/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoWaitCommand.h"

//this command literallyy does nothing besides halting the auto it is called from until the timer it starts hits the custom timeout
AutoWaitCommand::AutoWaitCommand(float timeout) : Command("AutoWaitCommand"){
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  wait = timeout;//get the timeout that the user sets and make it accessable from the rest of the functions
}

// Called just before this Command runs the first time
void AutoWaitCommand::Initialize() {
  //reset the timer and start it. this clears the (empty) timer and tells it what time to count up from
  //timers record the start and end time and return the difference in seconds.
  t.Reset();
  t.Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoWaitCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool AutoWaitCommand::IsFinished() { return t.Get()>wait; }//exit when the requested time has passed

// Called once after isFinished returns true
void AutoWaitCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoWaitCommand::Interrupted() {}
