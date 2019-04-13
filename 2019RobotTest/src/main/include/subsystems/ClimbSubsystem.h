/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Relay.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "frc/Timer.h"

// #include <rev/CANSparkMax.h>
using namespace frc;
// using namespace rev;

class ClimbSubsystem : public frc::Subsystem {
 public:
  ClimbSubsystem();
  void InitDefaultCommand() override;
  void Periodic() override;
  void ClimbTo(int target);
  void TogglePumping();
  bool ShouldPumping();
  void ToggleEMLock();
  int GetFootState();
  int GetLegPosition();
  bool IsLegAtPosition();
  void Prints();
  
  enum FootPosition {
    kLiftSelf = 1,
    kLiftBuddy = 2,
  };
  enum LegPositions {
    kFullIn = 0,
    kFullOut = 0,
    kHabHight = 0,
    kBuddyHight = 0,
  };

 private:
  // // It's desirable that everything possible under private except
  // // for methods that implement subsystem capabilities
  // // CANSparkMax climbMaster;
  // // CANSparkMax climbFollower;
  // WPI_TalonSRX climberLegMaster;
  // WPI_TalonSRX climberLegFollower;

  // //suction cup
  // DoubleSolenoid suctionClamp;

  // //legs
  // Relay leftElectromagnetLock;
  // Relay rightElectromagnetLock;

  // //logic variables
  // bool pumping{false};
  // bool locking{true};
  // int foot_position{1};
  // int leg_target{0};
  // int current_leg_state{1};
  // Timer compressionRate;
  // bool cycle_state{false};
  // bool is_at_position{false};

};
