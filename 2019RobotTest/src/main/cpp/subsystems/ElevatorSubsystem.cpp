/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ElevatorSubsystem.h"
#include "../include/Utils/PIDPreferences.h"
#include "../include/Robot.h"
#include "RobotMap.h"
#include "commands/Elevator/ElevatorDefault.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
using namespace std;

ElevatorSubsystem::ElevatorSubsystem() : 
  frc::Subsystem("ElevatorSubsystem"),
  elevatorMaster(ELEVATOR_MASTER),
  elevatorFollower(ELEVATOR_FOLLOWER),
  cargoIntakeExtend(CARGO_EXTEND)
  {
    //encoder stuff goes here

    //current limiting, magic numbers currently
    elevatorMaster.ConfigPeakCurrentDuration(30, 10);
    elevatorMaster.ConfigPeakCurrentLimit(22, 10);
    elevatorMaster.ConfigContinuousCurrentLimit(15, 10);
    elevatorMaster.EnableCurrentLimit(true);

    elevatorFollower.ConfigPeakCurrentDuration(30, 10);
    elevatorFollower.ConfigPeakCurrentLimit(22, 10);
    elevatorFollower.ConfigContinuousCurrentLimit(15, 10);
    elevatorFollower.EnableCurrentLimit(true);

    cargoIntakeExtend.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
    cargoIntakeExtend.SetSelectedSensorPosition(0);
    cargoIntakeExtend.SetSensorPhase(true);
    cargoIntakeExtend.ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector, LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 0);
    
    //follow code
    elevatorFollower.Follow(elevatorMaster);
    //elevatorFollower.SetInverted(FollowMaster) //if necessary 

    //variable setup
    next_elevator_position = 0;
    pull_in_cargo_exend = true;

  }

void ElevatorSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new ElevatorDefault());
}


void ElevatorSubsystem::SetExtend(bool extend){
  pull_in_cargo_exend = !extend;
}

void ElevatorSubsystem::SetCurrentGamepiece(int gamepiece){
  current_gamepiece = gamepiece;
}

void ElevatorSubsystem::AutoDetectCurrentGamepiece(){
  current_gamepiece = 1;
}

void ElevatorSubsystem::Periodic(){
  //         name          srx(lead)     p    i    d    f
  UpdatePID("elevator", elevatorMaster, 0.0, 0.0, 0.0, 0.0);
  UpdatePID("cargo_extend", cargoIntakeExtend, 0.0, 0.0, 0.0, 0.0);

  if(Robot::oi.left.GetRawButton(10)) {
    elevatorMaster.SetSelectedSensorPosition(0, 0, 0);
    elevatorMaster.SetSelectedSensorPosition(0, 0, 0);
	}

  double elevatorjoy = Robot::oi.ElevatorFudge();

  double elevator_position = fabs(elevatorMaster.GetSelectedSensorPosition(0));
  double extend_position = fabs(cargoIntakeExtend.GetSelectedSensorPosition(0));

  AutoDetectCurrentGamepiece();
  ExtendPeriodic();

  if(t.Get() < 0.0){
    elevatorMaster.Set(ControlMode::PercentOutput, 0.0);
    cargoIntakeExtend.Set(ControlMode::PercentOutput, 0.0);
  }else if(elevator_state_machine_state == 0){
    fudging = false;
  }else if(elevator_state_machine_state == 1){//pull the extend out
    elevatorMaster.Set(ControlMode::Position, position_when_seek_to_set);
    pull_in_cargo_exend = false;
    if((extend_position - CARGO_EXTEND_OUT) < 0.0){
      elevator_state_machine_state = 2;
    }
  }else if(elevator_state_machine_state == 2){//move the elevator
    elevatorMaster.Set(ControlMode::Position, next_elevator_position);
    pull_in_cargo_exend = false;
    if((elevator_position - next_elevator_position) < 0.0 ||
    elevator_position > LIMIT_OF_EFFECTED_BY_CARGO_INTAKE+0.0){
      elevator_state_machine_state = 3;
    }

  }else if(elevator_state_machine_state == 3){//pull the extend back in, unless we're fudging
    if(fudging){
      elevator_state_machine_state = 4;
    }else{
      elevatorMaster.Set(ControlMode::Position, next_elevator_position);
      if(pull_in_cargo_exend){
        pull_in_cargo_exend = true;
        elevator_state_machine_state = 4;
      }else{
        pull_in_cargo_exend = false;
        elevator_state_machine_state = 4;
      }
    }

  }else{
    //Elevator Fudge
    if(fabs(elevatorjoy) > 0.1){
      next_elevator_position = elevator_position + elevatorjoy * 50.0;
    }
    //set the motor to the fudge position using the encoder
    elevatorMaster.Set(ControlMode::Position, next_elevator_position);
    //if intaking, move the extend out
    if(Robot::Intake.is_intaking){
      pull_in_cargo_exend = false;
    }else{
      pull_in_cargo_exend = true;
    }
    //in manual mode, move the extend out of the way if neccessary
    if(elevator_position < LIMIT_OF_EFFECTED_BY_CARGO_INTAKE-50){
      elevator_state_machine_state = 1;
      fudging = true;
    }
  }


}

void ElevatorSubsystem::SeekTo(int next_rough_position, bool extend){
  /*Top = 1,
    Middle = 2,
    Bottom = 3,
    HPPickup = 4
    
    Hatch = 1,
    Cargo = 2;*/
  
  position_when_seek_to_set = elevatorMaster.GetSelectedSensorPosition(0);
  int next_elevator_state = 1;
  int gamepiece = current_gamepiece;

  if(extend == false){
    pull_in_cargo_exend = true;
  }else if(next_rough_position >= 3){
    pull_in_cargo_exend = false;
  }else{
    pull_in_cargo_exend = true;
  }

  if(next_rough_position == 1){//top
    if(gamepiece == 1){//Hatch
      next_elevator_position = TOP_HATCH_POSITION;
    }else{//Cargo
      next_elevator_position = TOP_CARGO_POSITION;
    }
  }else if(next_rough_position == 2){//middle
    if(gamepiece == 1){//Hatch
      next_elevator_position = MIDDLE_HATCH_POSITION;
    }else{//Cargo
      next_elevator_position = MIDDLE_CARGO_POSITION;
    }
  }else if(next_rough_position == 3){//bottom
    if(gamepiece == 1){//Hatch
      next_elevator_position = BOTTOM_HATCH_POSITION;
    }else{//Cargo
      next_elevator_position = BOTTOM_CARGO_POSITION;
    }
  }else if(next_rough_position == 4){//hppickup
    if(gamepiece == 1){//Hatch
      next_elevator_position = BOTTOM_HATCH_POSITION;
    }else{//Cargo
      next_elevator_position = HUMAN_PLAYER_PICKUP_CARGO;
    }
  }
  
  if(position_when_seek_to_set >= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && next_rough_position <= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE ||
     position_when_seek_to_set <= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && next_rough_position >= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE){
       elevator_state_machine_state = 1;
     }else{
       elevator_state_machine_state = 2;
     }
  fudging = false;
}

float ElevatorSubsystem::ElevatorPosition(){
  return elevatorMaster.GetSelectedSensorPosition(0);
}

void ElevatorSubsystem::ExtendPeriodic(){
  if(pull_in_cargo_exend){
    cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_IN);
  }else{
    cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_OUT);
  }
  
}

void ElevatorSubsystem::Prints(){
  SmartDashboard::PutNumber("Elevator/Elevator Encoder", elevatorMaster.GetSelectedSensorPosition(0));
  SmartDashboard::PutNumber("Elevator/Drawer Encoder", cargoIntakeExtend.GetSelectedSensorPosition(0));
  SmartDashboard::PutNumber("Elevator/Elevator Output", elevatorMaster.GetMotorOutputPercent());
  SmartDashboard::PutNumber("Elevator/Drawer Output", cargoIntakeExtend.GetMotorOutputPercent());
  SmartDashboard::PutNumber("Elevator/State", elevator_state_machine_state);
  SmartDashboard::PutBoolean("Elevator/pull in cargo extend?", pull_in_cargo_exend);

}