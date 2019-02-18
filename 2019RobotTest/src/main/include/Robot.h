/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Compressor.h>
#include "OI.h"

#include "commands/Auto/GeneralTestAuto.h"
#include "commands/Auto/AutoCenter.h"
#include "commands/Auto/AutoLeftLvl1.h"
#include "commands/Auto/AutoLeftLvl2.h"
#include "commands/Auto/AutoRightLvl1.h"
#include "commands/Auto/AutoRightLvl2.h"


#include "subsystems/ClimbSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ElevatorSubsystem.h"
#include "subsystems/HatchSubsystem.h"
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/LightSubsystem.h"
#include "subsystems/CameraSubsystem.h"
#include "subsystems/RobotInfo.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

using namespace frc;

class Robot : public frc::TimedRobot {
 public:
  static OI oi;
  static ClimbSubsystem Climb;
  static DriveSubsystem Drive;
  static ElevatorSubsystem Elevator;
  static HatchSubsystem Hatch;
  static IntakeSubsystem Intake;
  static LightSubsystem Lights;
  static CameraSubsystem Camera;
  static RobotInfo Info;


  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  Compressor *compressor = new Compressor(15);
  frc::Command* autonomousCommand = nullptr;
  GeneralTestAuto TestAuto;
  AutoCenter CenterAuto;
  AutoLeftLvl1 LeftLvl1Auto;
  AutoLeftLvl2 LeftLvl2Auto;
  AutoRightLvl1 RightLvl1Auto;
  AutoRightLvl2 RightLvl2Auto;
  frc::SendableChooser<frc::Command*> AutonomousChooser;
};
