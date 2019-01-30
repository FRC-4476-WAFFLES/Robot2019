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




  }
  frc::SmartDashboard::PutBoolean("Opreator Controll Mode", climber_switch);
}

float OI::ElevatorFudge(){
  return operate.GetRawAxis(1);
}