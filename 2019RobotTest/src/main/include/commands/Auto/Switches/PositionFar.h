/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/ConditionalCommand.h>

class PositionFar : public frc::ConditionalCommand {
 public:
  PositionFar(Command* Far, Command* Not_Far);
  bool Condition() override;
};
