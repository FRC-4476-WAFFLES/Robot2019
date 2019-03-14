/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystem.h"
#include "Robot.h"

CameraSubsystem::CameraSubsystem() : Subsystem("ExampleSubsystem") {}

void CameraSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void CameraSubsystem::SetLedMode(int mode){
  //update the existing entry on the table to change what the Limelight leds are doing. list in .h->CameraLEDMode(enum).
  camera->PutNumber("ledMode", mode);
}
double CameraSubsystem::GetCameraTX(){
  //get the x distance between the center of the target and the center of the crosshairs.
	return camera->GetNumber("tx", 0.0);
}
double CameraSubsystem::GetCameraTV(){
  //check for a valid target
  int tv = camera->GetNumber("tv", 0);
  //if the skew is too high, the camera is probobly tracking random lit pixels from lexan/doors
  if(fabs(Robot::Drive.GetSkew()) > 15){//magic number
    tv = 0;
  }
  return tv;
}
double CameraSubsystem::GetCameraTS(){
  //get the skew / rotation of the target rectangle
  return camera->GetNumber("ts", 0.0);
}
double CameraSubsystem::GetCameraTA(){
  //return the area of the target
  return camera->GetNumber("ta", 0.00000001);
}
void CameraSubsystem::SetCameraProcessingMode(int mode){
  //update the existing entry on the table to change what the Limelight is processing. list in .h->ProcessingMode(enum).
  camera->PutNumber("camMode", mode);
}
void CameraSubsystem::SetSnapshotMode(int mode){
  //update the existing entry on the table to change whether the Limelight is taking snapshots?. list in .h->SnapshotMode(enum).
  camera->PutNumber("snapshot", mode);
}