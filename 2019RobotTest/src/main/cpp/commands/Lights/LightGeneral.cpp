/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.            Cam                                                   */
/*----------------------------------------------------------------------------*/

#include "commands/Lights/LightGeneral.h"
#include "Robot.h"
#include "frc/RobotState.h"

//Default command for Lights, independantly determines which light mode to set

LightGeneral::LightGeneral() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::Lights);
}

// Called just before this Command runs the first time
void LightGeneral::Initialize() {
  Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::Disabled);
}
// Called repeatedly when this Command is scheduled to run
void LightGeneral::Execute() {
  //make sure the robot is not disabled, if so, do that mode regardless
  if(!frc::RobotState::IsDisabled()){
    if(Robot::Drive.is_tracking_drive || Robot::Drive.is_turning_tracking){
      //if tracking, tell us if we have a target, update the limelight LEDs
      Robot::Camera.SetLedMode(Robot::Camera.CameraLEDMode::On);
      /*if(Robot::Drive.missing_vision_target){
        Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::TrackingWithoutTarget);
      }else{
        Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::TrackingWithTarget);
      }*/
    }/*else*/ if(Robot::Hatch.HasPannel()){
      //tell us if we think have a hatch
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::HaveHatch);
    }else if(Robot::Intake.HasCargo()){
      //tell us if we think have a cargo
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::HaveCargo);
    }else if(Robot::Lights.hp_strobe){
      //strobe the lights at hp
      Robot::Camera.SetLedMode(Robot::Camera.CameraLEDMode::On);
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::WantCargoFromHP);
    }else{
      // if nothing else, tun the lights off.
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::None);
    }
  }else{
    Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::Disabled);
  }

  if(!Robot::Drive.is_tracking_drive && !Robot::Drive.is_turning_tracking && !Robot::Lights.hp_strobe){
    Robot::Camera.SetLedMode(Robot::Camera.CameraLEDMode::Off);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool LightGeneral::IsFinished() { return false; }

// Called once after isFinished returns true
void LightGeneral::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LightGeneral::Interrupted() {}
