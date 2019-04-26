/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class OperatorTankDrive : public frc::Command {
 public:
	OperatorTankDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	bool has_toggled{false};
	bool has_set{false};
	bool has_set_backing{false};
	frc::Timer delay_clamp;
	frc::Timer delay_clamp_delay;
	double init_angle{0};
};
