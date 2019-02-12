/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/ConditionalCommand.h>

class PositionFront : public frc::ConditionalCommand {
 public:
  PositionFront(Command* Front, Command* Not_Front);
  bool Condition() override;
};
