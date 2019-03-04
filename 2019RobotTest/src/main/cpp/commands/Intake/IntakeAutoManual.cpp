/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Intake/IntakeAutoManual.h"
#include "Robot.h"
#include "Utils/PIDPreferences.h"

IntakeAutoManual::IntakeAutoManual() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void IntakeAutoManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeAutoManual::Execute() {
  // Robot::Intake.current_distance_voltage = Robot::Intake.IR.GetVoltage();
  //   Robot::Intake.speed = Robot::oi.IntakeSpeed();
  //   float effect_on_angle = UpdateSinglePreference("outtake angle impact", 0.5);
  //   Robot::Intake.cargoCarriageLeft.Set(-Robot::Intake.speed + Robot::oi.OuttakeAngle()*effect_on_angle);
  //   Robot::Intake.cargoCarriageRight.Set(Robot::Intake.speed + Robot::oi.OuttakeAngle()*effect_on_angle);
  //   if(Robot::Elevator.ElevatorPosition() <= Robot::Elevator.LIMIT_OF_EFFECTED_BY_CARGO_INTAKE){
  //     Robot::Intake.cargoIntake.Set(-Robot::Intake.speed);
  //   }else{
  //     Robot::Intake.cargoIntake.Set(0.0);
  //   }
  //   if(Robot::Intake.speed >= 0.1){
  //     Robot::Intake.is_intaking = true;
  //   }else{
  //     Robot::Intake.is_intaking = false;
  //   }
  //   if(-Robot::Intake.speed>= 0.5){
  //     Robot::Intake.has_cargo = false;
  //   }else if(-Robot::Intake.speed<=-0.5){
  //     Robot::Intake.has_cargo = true;
  // }
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeAutoManual::IsFinished() { return false; }

// Called once after isFinished returns true
void IntakeAutoManual::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeAutoManual::Interrupted() {}
