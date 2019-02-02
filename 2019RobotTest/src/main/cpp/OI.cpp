/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "frc/Buttons/Button.h"
#include "frc/Buttons/JoystickButton.h"
#include <frc/smartdashboard/SmartDashboard.h>
//elevator
#include "commands/Elevator/ElevatorGroundPickup.h"
#include "commands/Elevator/ElevatorBottom.h"
#include "commands/Elevator/ElevatorMiddle.h"
#include "commands/Elevator/ElevatorHPPickup.h"
#include "commands/Elevator/ElevatorTop.h"
#include "commands/Elevator/ElevatorManualGampieceToggle.h"

OI::OI() :
  left(0),
  right(1),
  operate(2)
{
  // Process operator interface input here.
  //definitions
  bool back_button = operate.GetRawButton(OperatorButton::Back);
  if(back_button == true && joystick_mode_toggle_limit == false){
    climber_switch = !climber_switch;
    joystick_mode_toggle_limit = true;
  }else if(back_button == false && joystick_mode_toggle_limit == true){
    joystick_mode_toggle_limit = false;
  }
  //switch logic
  if(climber_switch){

    



  }else{
    //elevator
    Button* Ground = new JoystickButton(&operate, OperatorButton::B);
    Ground->WhenReleased(new ElevatorGroundPickup());

    Button* Bottom = new JoystickButton(&operate, OperatorButton::A);
    Bottom->WhenReleased(new ElevatorBottom());

    Button* Middle = new JoystickButton(&operate, OperatorButton::X);
    Middle->WhenReleased(new ElevatorMiddle());

    Button* Top = new JoystickButton(&operate, OperatorButton::Y);
    Top->WhenReleased(new ElevatorTop());

    Button* HP = new JoystickButton(&operate, OperatorButton::RightJoystickCenterButton);
    HP->WhenReleased(new ElevatorHPPickup());

    Button* ManualSwap = new JoystickButton(&operate, OperatorButton::Start);
    ManualSwap->WhenReleased(new ElevatorManualGampieceToggle());


  }
  frc::SmartDashboard::PutBoolean("Opreator Controll Mode", climber_switch);
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
	return in * in - 1.0 * out * out ;//0.4->1.0
}