/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LightSubsystem.h"

#include "RobotMap.h"
#include "commands/Lights/LightGeneral.h"

LightSubsystem::LightSubsystem() : frc::Subsystem("LightSubsystem"), led(LIGHT_STRIP) {
  T.Stop();
  T.Reset();
  T.Start();
}

void LightSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new LightGeneral());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void LightSubsystem::UpdateColour(int colour){
  /*    None = 0,
    HaveHatch = 1,
    HaveCargo = 2,
    TrackingWithTarget = 3,
    TrackingWithoutTarget = 4,
    WantCargoFromHP = 5,*/
  if(colour == 0){
    SendColour(0, 0, 0);
  }else if(colour == 1){
    SendColour(153, 0, 153);//purple(Dark)
  }else if(colour == 2){
    SendColour(153, 0, 153);//purple(Dark)
  }else if(colour == 3){
    SendColour(204, 0, 102);
  }else if(colour == 4){
    Strobe(255, 0, 0);
  }else if(colour == 5){
    Strobe(255, 255, 255);//white
  }else if(colour == 6){
    SendColour(240, 234, 72);//waffles yellow
    //SendColour(255, 255, 51);//"closest WebSafe colour"(just in case)
  }
}
void LightSubsystem::SendColour(int r, int g, int b){
  led.SetLEDOutput(r, CANifier::LEDChannel::LEDChannelA);
	led.SetLEDOutput(g, CANifier::LEDChannel::LEDChannelB);
	led.SetLEDOutput(b, CANifier::LEDChannel::LEDChannelC);
}
void LightSubsystem::Strobe(int r, int g, int b){
  if(T.Get() >= 0.1){
    if(!strobe_index){
      led.SetLEDOutput(r, CANifier::LEDChannel::LEDChannelA);
      led.SetLEDOutput(g, CANifier::LEDChannel::LEDChannelB);
      led.SetLEDOutput(b, CANifier::LEDChannel::LEDChannelC);
    }else{
      led.SetLEDOutput(0, CANifier::LEDChannel::LEDChannelA);
      led.SetLEDOutput(0, CANifier::LEDChannel::LEDChannelB);
      led.SetLEDOutput(0, CANifier::LEDChannel::LEDChannelC);
    }
    T.Reset();
  }

}