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
  Button* OpSwitch = new JoystickButton(&operate, OperatorButton::Back);
  //switch logic
  if(ClimberSwitch){
    OpSwitch->WhenReleased(ClimberSwitch = false);

  }else{
    OpSwitch->WhenReleased(ClimberSwitch = true);

  }
  frc::SmartDashboard::PutBoolean("Opreator Controll Mode", ClimberSwitch);
}

void OI::ElevatorFudge(){
  return operate.GetRawAxis(1);
}