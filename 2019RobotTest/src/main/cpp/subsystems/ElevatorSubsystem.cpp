/*----------------------------------------------------------------------------*/
/* DUNCAN STEVENSON (c) 2019-3019 FIRST. All Rights Reserved.                 */
/* Open Source Software - may NOT be modified and shared by FRC teams.The code*/
/* must be accompanied by the DUNCAN BSD license file in the root directory of*/
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ElevatorSubsystem.h"
#include "../include/Utils/PIDPreferences.h"
#include "../include/Robot.h"
#include "RobotMap.h"
#include "commands/Elevator/ElevatorDefault.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <frc/DriverStation.h>
using namespace std;

ElevatorSubsystem::ElevatorSubsystem() : 
  frc::Subsystem("ElevatorSubsystem"),
  elevatorMaster(ELEVATOR_MASTER),
  elevatorFollower(ELEVATOR_FOLLOWER),
  cargoIntakeExtend(CARGO_EXTEND)
  {
    //current limiting
    elevatorMaster.ConfigPeakCurrentDuration(30, 10);
    elevatorMaster.ConfigPeakCurrentLimit(22, 10);
    elevatorMaster.ConfigContinuousCurrentLimit(15, 10);
    elevatorMaster.EnableCurrentLimit(true);
    elevatorMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
    elevatorMaster.SetSelectedSensorPosition(0);
    elevatorMaster.SetSensorPhase(false);

    elevatorFollower.ConfigPeakCurrentDuration(30, 10);
    elevatorFollower.ConfigPeakCurrentLimit(22, 10);
    elevatorFollower.ConfigContinuousCurrentLimit(15, 10);
    elevatorFollower.EnableCurrentLimit(true);
    

    cargoIntakeExtend.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 10);
    cargoIntakeExtend.SetSelectedSensorPosition(0);
    cargoIntakeExtend.SetSensorPhase(true);//true
    cargoIntakeExtend.ConfigForwardLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector, LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 0);
    cargoIntakeExtend.SetInverted(true);
    //follow code
    elevatorFollower.Follow(elevatorMaster);
    //elevatorFollower.SetInverted(FollowMaster) //if necessary 
    elevatorMaster.SetInverted(false);
    elevatorFollower.SetInverted(false);
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
  if(Robot::Intake.HasCargoIR()){
    current_gamepiece = 2;
  }else if(Robot::Intake.HasCargo() && Robot::Hatch.HasPannel()){
    current_gamepiece = 1;
  }else if(Robot::Intake.HasCargo()){
    current_gamepiece = 2;
  }else{
    current_gamepiece = 1;
  }
}

void ElevatorSubsystem::Periodic(){
  //if we are going down
  if(next_elevator_position - ElevatorPosition() < 0){
    UpdatePID("elevatorDown", elevatorMaster, 9.0, 0.0, 1.0, 0.0);
    UpdatePID("cargo_extend", cargoIntakeExtend, 2.0, 0.0, 0.0, 0.0);
  }else{
    //         name          srx(lead)     p    i    d    f
    UpdatePID("elevator", elevatorMaster, 9.0, 0.0, 1.0, 0.0);
    UpdatePID("cargo_extend", cargoIntakeExtend, 2.0, 0.0, 0.0, 0.0);
  }

  if(Robot::oi.left.GetRawButton(10)) {
    elevatorMaster.SetSelectedSensorPosition(0, 0, 0);
    cargoIntakeExtend.SetSelectedSensorPosition(0, 0, 0);
	}
  
  // if(cargoIntakeExtend.GetSensorCollection().IsFwdLimitSwitchClosed()){
  //   cargoIntakeExtend.SetSelectedSensorPosition(0);
  // }

  double elevatorjoy = -1*Robot::oi.ElevatorFudge();

  double elevator_position = fabs(elevatorMaster.GetSelectedSensorPosition(0));
  double extend_position = fabs(cargoIntakeExtend.GetSelectedSensorPosition(0));

  AutoDetectCurrentGamepiece();

  if(!full_manual){
    if(t.Get() < 0.0 && frc::DriverStation::GetInstance().IsOperatorControl()){
      elevatorMaster.Set(ControlMode::PercentOutput, 0.0);
      // cargoIntakeExtend.Set(ControlMode::PercentOutput, 0.0);
    }else if(elevator_state_machine_state == 0){
      std::cout << "in state 0" << std::endl;
    }else if(elevator_state_machine_state == 1){//pull the extend out
      std::cout << "in state 1" << std::endl;
      fudging = false;
      has_moved_for_vision = false;
      has_moved_up_for_vision = false;
      has_moved_down_for_vision = false;
      std::cout << fabs(fabs(extend_position) - fabs(CARGO_EXTEND_HATCH)) << std::endl;
      elevatorMaster.Set(ControlMode::Position, position_when_seek_to_set);
      pull_in_cargo_exend = false;
      if(fabs(fabs(extend_position) - fabs(CARGO_EXTEND_CARGO)) < 40.0 && Robot::Intake.HasCargo()){
        elevator_state_machine_state = 2;
      }else if(fabs(fabs(extend_position) - fabs(CARGO_EXTEND_HATCH)) < 40.0 && Robot::Hatch.HasPannel()){
        elevator_state_machine_state = 2;
      }else if(fabs(fabs(extend_position) - fabs(CARGO_EXTEND_HATCH)) < 40.0){
        elevator_state_machine_state = 2;
      }
    }else if(elevator_state_machine_state == 2){//move the elevator
      std::cout << "in state 2" << std::endl;
      fudging = false;
      elevatorMaster.Set(ControlMode::Position, next_elevator_position);
      pull_in_cargo_exend = false;
      if(fabs(fabs(elevator_position) - fabs(next_elevator_position)) < 60.0){
        elevator_state_machine_state = 3;
      }

    }else if(elevator_state_machine_state == 3){//pull the extend back in, unless we're fudging
      std::cout << "in state 3" << std::endl;
      elevatorMaster.Set(ControlMode::Position, next_elevator_position);
      elevator_state_machine_state = 4;

    }else if(elevator_state_machine_state == 4){
      std::cout << "in state end state" << std::endl;
      //Elevator Fudge
      if(fabs(elevatorjoy) > 0.1){
        next_elevator_position = elevator_position + elevatorjoy * 75.0;
        fudging = true;
      }
      //set the motor to the fudge position using the encoder
      elevatorMaster.Set(ControlMode::Position, next_elevator_position);
      // elevatorMaster.Set(ControlMode::PercentOutput, elevatorjoy);
      //if intaking, move the extend out
      if(Robot::Intake.is_intaking){
        pull_in_cargo_exend = false;
        Robot::Hatch.UpdateHatch(Robot::Hatch.current_clamp_state, false);
        next_elevator_position = GROUND_PICKUP_CARGO;
      }else if(Robot::Intake.is_outtaking){
        pull_in_cargo_exend = false;
      }else if(elevator_position < LIMIT_OF_EFFECTED_BY_CARGO_INTAKE+100 && fudging){
        std::cout << "Condition: fudge move extend" << std::endl;
        // position_when_seek_to_set = elevator_position;
        elevator_state_machine_state = 5;
        pull_in_cargo_exend = false;
      }else if(!Robot::Hatch.current_clamp_state && Robot::Hatch.current_deploy_state && next_elevator_position < LIMIT_OF_EFFECTED_BY_CARGO_INTAKE /*&& !Robot::Drive.is_tracking_drive &&!Robot::Drive.is_turning_tracking*/){
        std::cout << "Condition: move out extend to support hatch" << std::endl;
        pull_in_cargo_exend = false;
      }else if(!has_moved_down_for_vision && Robot::Drive.is_tracking_drive && (MIDDLE_CARGO_POSITION + 200) > next_elevator_position && next_elevator_position > LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && !has_moved_for_vision){
        std::cout << "Condition: move Up for Vision under level 2" << std::endl;
        next_elevator_position +=300;
        has_moved_up_for_vision = true;
        has_moved_for_vision = true;
      }else if(Robot::Drive.is_tracking_drive && next_elevator_position > (MIDDLE_CARGO_POSITION + 200) && !has_moved_for_vision){
        std::cout << "Condition: move up then down for vision" << std::endl;
        next_elevator_position -= 100;
        has_moved_for_vision = true;
      }else{
        pull_in_cargo_exend = true;
      }

      if(has_moved_up_for_vision && fabs(elevator_position - next_elevator_position) < 40 && !has_moved_down_for_vision){
        next_elevator_position -=300;
        has_moved_down_for_vision = true;
        std::cout << "moving down for vision" << std::endl;
      }
      
      // in manual mode, move the extend out of the way if neccessary
    }else if(elevator_state_machine_state == 5){//for when fudging
      std::cout << "in state 5" << std::endl;
      std::cout << fabs(fabs(extend_position) - fabs(CARGO_EXTEND_HATCH)) << std::endl;
      // elevatorMaster.Set(ControlMode::Position, position_when_seek_to_set);
      pull_in_cargo_exend = false;
      if(fabs(fabs(extend_position) - fabs(CARGO_EXTEND_CARGO)) < 40.0 && Robot::Intake.HasCargo()){
        elevator_state_machine_state = 4;
      }else if(fabs(fabs(extend_position) - fabs(CARGO_EXTEND_HATCH)) < 40.0 && Robot::Hatch.HasPannel()){
        elevator_state_machine_state = 4;
      }else if(fabs(fabs(extend_position) - fabs(CARGO_EXTEND_HATCH)) < 40.0){
        elevator_state_machine_state = 4;
      }
    }
  }else{
    elevatorMaster.Set(ControlMode::PercentOutput, Robot::oi.operate.GetRawAxis(1));
  }



  ExtendPeriodic();
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
  }else if(next_rough_position >= 3 || next_rough_position == 5){
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
  }else if(next_rough_position == 5){//ground pickup
    if(gamepiece == 1){//Hatch
      next_elevator_position = GROUND_PICKUP_HATCH;
    }else{//Cargo
      next_elevator_position = GROUND_PICKUP_CARGO;
    }
  }else if(next_rough_position == 6){//Cargo Ship
    if(gamepiece == 1){//Hatch
      next_elevator_position = MIDDLE_HATCH_POSITION;
    }else{//Cargo
      next_elevator_position = CARGO_SHIP_CARGO_POSITION;
    }
  }
  
  if(position_when_seek_to_set >= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && next_elevator_position <= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE ||
     position_when_seek_to_set <= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && next_elevator_position >= LIMIT_OF_EFFECTED_BY_CARGO_INTAKE){
       std::cout << " move extend to accomodate elevator" << std::endl;
    elevator_state_machine_state = 1;//1
  }else{
    elevator_state_machine_state = 2;//2
    std::cout << " DO NOT move extend" << std::endl;
  }
}

float ElevatorSubsystem::ElevatorPosition(){
  return elevatorMaster.GetSelectedSensorPosition(0);
}

void ElevatorSubsystem::ExtendPeriodic(){
  if(!def_mode){
    if(!full_manual){
      if(pull_in_cargo_exend){
        cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_IN);
        //rezero on zero velocity
        if(fabs(cargoIntakeExtend.GetSelectedSensorPosition())<50 && fabs(cargoIntakeExtend.GetSelectedSensorVelocity())<5){
          ReZeroExtend();
        }
      }else{
        if(Robot::Intake.is_intaking){
          cout << "intaking "<<endl;
          cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_INTAKE);
        }else if(Robot::Intake.is_outtaking){
          cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_HATCH);
        }else if(Robot::Intake.HasCargo()){
          cout << "has cargo "<<endl;
          cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_CARGO);
        }else if(!Robot::Hatch.current_clamp_state && Robot::Hatch.current_deploy_state && next_elevator_position < LIMIT_OF_EFFECTED_BY_CARGO_INTAKE && !Robot::Drive.is_tracking_drive &&!Robot::Drive.is_turning_tracking){
          cout << "has hatch "<<endl;
          cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_SUPPORT);
        }else{
          cout << "else "<<endl;
          cargoIntakeExtend.Set(ControlMode::Position, CARGO_EXTEND_HATCH);
        }
      }
    }else{
      cargoIntakeExtend.Set(ControlMode::PercentOutput, -1*Robot::oi.operate.GetRawAxis(5));
    }
  }else{
    cargoIntakeExtend.Set(ControlMode::PercentOutput, -0.2);
  }
}

void ElevatorSubsystem::Prints(){
  SmartDashboard::PutNumber("Elevator/Elevator Encoder", elevatorMaster.GetSelectedSensorPosition(0));
  SmartDashboard::PutNumber("Elevator/Drawer Encoder", cargoIntakeExtend.GetSelectedSensorPosition(0));
  SmartDashboard::PutNumber("Elevator/Elevator Output", elevatorMaster.GetMotorOutputPercent());
  SmartDashboard::PutNumber("Elevator/Drawer Output", cargoIntakeExtend.GetMotorOutputPercent());
  SmartDashboard::PutNumber("Elevator/State", elevator_state_machine_state);
  SmartDashboard::PutBoolean("Elevator/pull in cargo extend?", pull_in_cargo_exend);
  SmartDashboard::PutBoolean("Elevator/Drawer limit", cargoIntakeExtend.GetSensorCollection().IsFwdLimitSwitchClosed());
  SmartDashboard::PutNumber("Gamepiece", current_gamepiece);
  SmartDashboard::PutNumber("Elevator/ElevatorError", fabs(fabs(ElevatorPosition()) - fabs(next_elevator_position)));
}

void ElevatorSubsystem::REZero(){
  elevatorMaster.SetSelectedSensorPosition(0);
}

float ElevatorSubsystem::GetNextPosition(){
  return next_elevator_position;
}

void ElevatorSubsystem::SetFullManual(){
  full_manual = !full_manual;
}

void ElevatorSubsystem::ReZeroExtend(){
  cargoIntakeExtend.SetSelectedSensorPosition(0);
}