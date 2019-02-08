/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.            Cam                                                   */
/*----------------------------------------------------------------------------*/

#include "commands/Lights/LightGeneral.h"
#include "Robot.h"
#include "frc/RobotState.h"

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
  if(!frc::RobotState::IsDisabled()){
    if(Robot::Drive.is_tracking_drive){
      if(Robot::Drive.missing_vision_target){
        Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::TrackingWithoutTarget);
      }else{
        Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::TrackingWithTarget);
      }
    }else if(Robot::Hatch.HasPannel()){
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::HaveHatch);
    }else if(Robot::Intake.HasCargo()){
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::HaveCargo);
    }else if(Robot::Lights.hp_strobe){
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::WantCargoFromHP);
    }else{
      Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::None);
    }
  }else{
    Robot::Lights.UpdateColour(Robot::Lights.ColourCodes::Disabled);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool LightGeneral::IsFinished() { return false; }

// Called once after isFinished returns true
void LightGeneral::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LightGeneral::Interrupted() {}
