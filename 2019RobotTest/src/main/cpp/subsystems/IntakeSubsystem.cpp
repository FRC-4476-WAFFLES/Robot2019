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
//  IR(INFRA_RED),
 Proximity(PROXIMITY_SENSOR)
 {

 }

void IntakeSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new IntakeDefault());
}


void IntakeSubsystem::Periodic(){
  // current_distance_voltage = IR.GetVoltage();
    speed = Robot::oi.IntakeSpeed();
    if(has_cargo_IR){
      speed = speed + 0.085;
    }
    if(!Robot::Hatch.current_clamp_state && Robot::Hatch.current_deploy_state && Robot::Elevator.next_elevator_position < Robot::Elevator.LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && Robot::Drive.is_tracking_drive || Robot::Drive.is_turning_tracking){
      speed = -0.3452345678901;
    }
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

    if(speed <= -0.1){
      is_outtaking = true;
    }else{
      is_outtaking = false;
    }

    if(-speed>= 0.5){
      has_cargo = false;
    }else if(-speed<=-0.5){
      has_cargo = true;
    }
//get returns a inverted value
  if(!Proximity.Get()/*current_distance_voltage>2.5*/){
    has_cargo_IR = true;
    // cargo_is_in_intake = true;
  }else if(Proximity.Get()/*current_distance_voltage<2.5 &&!cargo_is_in_intake*/) {
    has_cargo_IR = false;
    
  }
  // if(current_distance_voltage<0.1){
  //   cargo_is_in_intake = false;
  // }

  
}

void IntakeSubsystem::SetIntakeSpeed(double Speed){
  speed = Speed;
}
bool IntakeSubsystem::HasCargo(){
  
  return has_cargo;
}

bool IntakeSubsystem::HasCargoIR(){
  return has_cargo_IR;
}

void IntakeSubsystem::Prints(){
  SmartDashboard::PutBoolean("Intake/HasCargo", has_cargo);
  SmartDashboard::PutNumber("Intake/Intake Speed", speed);
  SmartDashboard::PutBoolean("Intake/HasCagoIR", has_cargo_IR);
  // SmartDashboard::PutNumber("Intake/IR Voltage", current_distance_voltage);
  SmartDashboard::PutBoolean("Intake/Is Intaking", is_intaking);
  SmartDashboard::PutBoolean("Intake/Is Outtaking", is_outtaking);
}