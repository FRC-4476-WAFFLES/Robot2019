/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IntakeSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"
#include "RobotMap.h"
#include "commands/Intake/IntakeDefault.h"
#include "Utils/PIDPreferences.h"

IntakeSubsystem::IntakeSubsystem() :
 frc::Subsystem("IntakeSubsystem"),
 cargoCarriageLeft(LEFT_CARGO_CARRIAGE),
 cargoCarriageRight(RIGHT_CARGO_CARRIAGE),
 cargoIntake(CARGO_INTAKE),
 IR(INFRA_RED)
 {

 }

void IntakeSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new IntakeDefault());
}


void IntakeSubsystem::Periodic(){
  current_distance_voltage = IR.GetVoltage();
  if(frc::DriverStation::GetInstance().IsOperatorControl()){
    speed = Robot::oi.IntakeSpeed();
    float effect_on_angle = UpdateSinglePreference("outtake angle impact", 0.5);
    cargoCarriageLeft.Set(-speed + Robot::oi.OuttakeAngle()*effect_on_angle);
    cargoCarriageRight.Set(speed + Robot::oi.OuttakeAngle()*effect_on_angle);
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
    if(-speed>= 0.5){
      has_cargo = false;
    }else if(-speed<=-0.5){
      has_cargo = true;
    }
  }
  
}

void IntakeSubsystem::SetIntakeSpeed(double Speed){
  speed = Speed;
}
bool IntakeSubsystem::HasCargo(){
  // if(current_distance_voltage > 1.200 && current_distance_voltage < 3.000){
  //   has_cargo = true;
  // }else{
  //   has_cargo = false;
  // }
  return has_cargo;
}

void IntakeSubsystem::Prints(){
  SmartDashboard::PutBoolean("Intake/HasCargo", has_cargo);
  SmartDashboard::PutNumber("Intake/Intake Speed", speed);
  SmartDashboard::PutNumber("Intake/IR Voltage", current_distance_voltage);
}