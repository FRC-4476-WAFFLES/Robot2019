/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/Timer.h>

using namespace frc;

class ElevatorSubsystem : public frc::Subsystem {
 public:
  ElevatorSubsystem();
  void InitDefaultCommand() override;
  void SetExtend(bool extend);
  void SetCurrentGamepiece(int gamepiece);
  void AutoDetectCurrentGamepiece();
  void Periodic() override;
  void SeekTo(int next_rough_position, bool extend = false);
  float ElevatorPosition();
  void ExtendPeriodic();
  void Prints();


  //elevator
  //HATCH
  constexpr static float GROUND_PICKUP_HATCH = 0.0;
  constexpr static float BOTTOM_HATCH_POSITION = 0.0;
  constexpr static float MIDDLE_HATCH_POSITION = 0.0;
  constexpr static float TOP_HATCH_POSITION = 0.0;

  //CARGO
  constexpr static float GROUND_PICKUP_CARGO = 0.0;
  constexpr static float HUMAN_PLAYER_PICKUP_CARGO = 0.0;
  constexpr static float BOTTOM_CARGO_POSITION = 0.0;
  constexpr static float MIDDLE_CARGO_POSITION = 0.0;
  constexpr static float TOP_CARGO_POSITION = 0.0;
  constexpr static float LIMIT_OF_EFFECTED_BY_CARGO_INTAKE = 0.0;

  //CARGO EXTEND OUT
  constexpr static float CARGO_EXTEND_OUT = 0.0;
  constexpr static float CARGO_EXTEND_IN = 0.0;//slightly out

  enum Positions {
    Top = 1,
    Middle = 2,
    Bottom = 3,
    HPPickup = 4,
    Ground = 5,
  };
  enum Gamepiece  {
    Hatch = 1,
    Cargo = 2,
  };
  
  //logic variables
  bool PID_joystick_switch = false;
  int elevator_state_machine_state = 0;

  bool pull_in_cargo_exend = false;
  float next_elevator_position = 0.0;
  float next_cargo_extend_position = 0.0;
  float position_when_seek_to_set = 0;
  int current_gamepiece = 1;//default to Hatch
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  WPI_TalonSRX elevatorMaster;
  WPI_TalonSRX elevatorFollower;
  WPI_TalonSRX cargoIntakeExtend;
  Timer t;
  bool fudging = false;
};
