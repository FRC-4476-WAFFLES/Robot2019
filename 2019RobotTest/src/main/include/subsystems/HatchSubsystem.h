/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>

using namespace frc;

class HatchSubsystem : public frc::Subsystem {
 public:
  HatchSubsystem();
  void InitDefaultCommand() override;
  void Periodic() override;
  void UpdateHatch(bool clamp, bool deploy);
  bool HasPannel();
  bool current_clamp_state = false;
  bool current_deploy_state = false;
  bool next_clamp_state = false;
  bool next_deploy_state = false;

 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  DoubleSolenoid hatchDeploy;
  DoubleSolenoid hatchClamp;
};
