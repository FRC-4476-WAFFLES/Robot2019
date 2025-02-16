/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/PowerDistributionPanel.h>
using namespace frc;
class RobotInfo : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  RobotInfo();
  void InitDefaultCommand() override;
  SendableChooser<int*> targetPosition;
  SendableChooser<int*> targetSide;
  SendableChooser<int*> preload;
  PowerDistributionPanel pdp;
  
};
