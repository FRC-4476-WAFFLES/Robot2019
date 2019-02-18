/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystem.h"

CameraSubsystem::CameraSubsystem() : Subsystem("ExampleSubsystem") {}

void CameraSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void CameraSubsystem::SetLedMode(int mode){
  camera->PutNumber("ledMode", mode);
}
double CameraSubsystem::GetCameraTX(){
	return camera->GetNumber("tx", 0.0);
}
double CameraSubsystem::GetCameraTV(){
  return camera->GetNumber("tv", 0);
}
double CameraSubsystem::GetCameraTS(){
  return camera->GetNumber("ts", 0.0);
}
double CameraSubsystem::GetCameraTA(){
  return camera->GetNumber("ta", 0.0);
}
void CameraSubsystem::SetCameraProcessingMode(int mode){
  camera->PutNumber("camMode", mode);
}