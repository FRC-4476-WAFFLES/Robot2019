/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "frc/buttons/Button.h"
#include "frc/buttons/JoystickButton.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"
//elevator
#include "commands/Elevator/ElevatorGroundPickup.h"
#include "commands/Elevator/ElevatorBottom.h"
#include "commands/Elevator/ElevatorMiddle.h"
#include "commands/Elevator/ElevatorHPPickup.h"
#include "commands/Elevator/ElevatorTop.h"
#include "commands/Elevator/ElevatorManualGamepieceToggle.h"
//oi
#include "commands/OI/WithOperatorMode.h"
#include "commands/OI/OperatorModeSwitch.h"
#include "commands/Drive/PathFollower.h"
//Hatch
#include "commands/Hatch/ToggleClamp.h"
#include "commands/Hatch/ToggleDeploy.h"
//lights
#include "Commands/Lights/HPWontDropItem.h"
OI::OI() :
  left(0),
  right(1),
  operate(2),
  hid(3)
{
  Button* Ground = new JoystickButton(&operate, OperatorButton::B);
  Ground->WhenReleased(new WithOperatorMode(nullptr, new ElevatorGroundPickup()));

  Button* Bottom = new JoystickButton(&operate, OperatorButton::A);
  Bottom->WhenReleased(new WithOperatorMode(nullptr, new ElevatorBottom()));

  Button* Middle = new JoystickButton(&operate, OperatorButton::X);
  Middle->WhileHeld(new ElevatorMiddle());

  Button* Top = new JoystickButton(&operate, OperatorButton::Y);
  Top->WhenReleased(new WithOperatorMode(nullptr, new ElevatorTop()));

  Button* HP = new JoystickButton(&operate, OperatorButton::RightJoystickCenterButton);
  HP->WhenReleased(new WithOperatorMode(nullptr, new ElevatorHPPickup()));

  Button* ManualSwap = new JoystickButton(&operate, OperatorButton::Start);
  ManualSwap->WhenReleased(new WithOperatorMode(nullptr, new ElevatorManualGamepieceToggle()));

  Button* ModeSwitch = new JoystickButton(&operate, OperatorButton::Back);
  ModeSwitch->WhenPressed(new OperatorModeSwitch());

  Button* testthepathfindercode = new JoystickButton(&operate, OperatorButton::RightJoystickCenterButton);
  testthepathfindercode->WhenReleased(new PathFollower("first"));
  
  Button* ToggleHatchDeploy = new JoystickButton(&operate, OperatorButton::BumperTopLeft);
  ToggleHatchDeploy->WhenPressed(new WithOperatorMode(new ToggleDeploy(), new ToggleDeploy()));

  Button* ToggleHatchClamp = new JoystickButton(&operate, OperatorButton::BumperTopRight);
  ToggleHatchClamp->WhenPressed(new WithOperatorMode(new ToggleClamp(), new ToggleClamp()));

  Button* WhenUrHumanPlayerWontNoticeU = new JoystickButton(&right, 11);
  WhenUrHumanPlayerWontNoticeU->WhileHeld(new HPWontDropItem());
  
  Button* WhenUrHumanPlayerWontNoticeUAndUrAngry = new JoystickButton(&right, 10);
  WhenUrHumanPlayerWontNoticeUAndUrAngry->WhileHeld(new HPWontDropItem());
}

float OI::ElevatorFudge(){
  return operate.GetRawAxis(1);
}

float OI::OuttakeAngle(){
  return operate.GetRawAxis(4);
}

float OI::IntakeSpeed() {

	double in = operate.GetRawAxis(3);
	double out =  operate.GetRawAxis(2);
	return (in * in - 1.0 * out * out)*0.9;//0.4->1.0
}
void OI::Prints(){
  SmartDashboard::PutBoolean("climber switch", climber_switch);
  SmartDashboard::PutNumber("Elevator1Amp", Robot::Info.pdp.GetCurrent(5));
  SmartDashboard::PutNumber("Elevator2Amp", Robot::Info.pdp.GetCurrent(11));
  Robot::Drive.Prints();
  Robot::Elevator.Prints();
  Robot::Hatch.Prints();
  Robot::Intake.Prints();
  Robot::Lights.Prints();
}
