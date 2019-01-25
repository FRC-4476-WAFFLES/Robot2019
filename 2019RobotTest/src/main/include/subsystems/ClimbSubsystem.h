/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
using namespace frc;
using namespace rev;

class ClimbSubsystem : public frc::Subsystem {
 public:
  ClimbSubsystem();
  void InitDefaultCommand() override;

 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  CANSparkMax climbMaster;
  CANSparkMax climbFollower;
};
