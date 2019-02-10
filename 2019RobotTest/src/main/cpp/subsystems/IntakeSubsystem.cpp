/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IntakeSubsystem.h"
#include "Robot.h"
#include "RobotMap.h"
#include "commands/Intake/IntakeDefault.h"

IntakeSubsystem::IntakeSubsystem() :
 frc::Subsystem("IntakeSubsystem"),
 cargoCarriageLeft(LEFT_CARGO_CARRIAGE),
 cargoCarriageRight(RIGHT_CARGO_CARRIAGE),
 cargoIntake(CARGO_INTAKE)
 {

 }

void IntakeSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new IntakeDefault());
}


void IntakeSubsystem::Periodic(){
  if(frc::DriverStation::GetInstance().IsOperatorControl()){
    speed = Robot::oi.IntakeSpeed();
  }
  cargoCarriageLeft.Set(-speed - Robot::oi.OuttakeAngle());
	cargoCarriageRight.Set(speed + Robot::oi.OuttakeAngle());
  if(Robot::Elevator.ElevatorPosition() <= Robot::Elevator.LIMIT_OF_EFFECTED_BY_CARGO_INTAKE){
    cargoIntake.Set(-speed);
  }else{
    cargoIntake.Set(0.0);
  }
  if(speed >= 0.1){
    is_intaking = true;
  }else{
    is_intaking = false;
  }
}

void IntakeSubsystem::SetIntakeSpeed(double Speed){
  speed = Speed;
}
bool IntakeSubsystem::HasCargo(){
  return false;
}