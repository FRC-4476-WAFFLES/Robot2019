/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/VictorSP.h>
#include <frc/AnalogInput.h>
using namespace frc;

class IntakeSubsystem : public frc::Subsystem {
 public:
  IntakeSubsystem();
  void InitDefaultCommand() override;
  void Periodic() override;
  void SetIntakeSpeed(double Speed);
  bool HasCargo();
  bool HasCargoIR();
  void Prints();

  double speed = 0.0;
  bool is_intaking = false;
  bool is_outtaking = false;
  bool has_cargo = false;
  VictorSP cargoCarriageLeft;
  VictorSP cargoCarriageRight;
  WPI_VictorSPX cargoIntake;
  AnalogInput IR;
  float current_distance_voltage = 0;
 private:
 bool cargo_is_in_intake = false;
bool has_cargo_IR = false;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  
};
