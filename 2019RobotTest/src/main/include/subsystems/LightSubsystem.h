/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/CANifier.h>
#include <frc/Timer.h>
using namespace frc;

class LightSubsystem : public frc::Subsystem {
 public:
  LightSubsystem();
  void InitDefaultCommand() override;
  void UpdateColour(int colour);
  void SendColour(int r, int g, int b);
  void Strobe(int r, int g, int b);
  bool hp_strobe = false;
  enum ColourCodes {
    None = 0,
    HaveHatch = 1,
    HaveCargo = 2,
    TrackingWithTarget = 3,
    TrackingWithoutTarget = 4,
    WantCargoFromHP = 5,
    Disabled = 6,
  };

 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  CANifier led;
  Timer T;
  bool strobe_index = false;
};
