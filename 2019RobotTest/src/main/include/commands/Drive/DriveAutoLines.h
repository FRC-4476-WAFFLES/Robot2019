#pragma once

#include <vector>

#include <frc/Timer.h>
#include <frc/commands/Command.h>
using namespace frc;

class DriveAutoLines : public frc::Command {
private:
	double distance;
	double angle;
	double epsilon;
	double last_distance_error;
	double last_angle_error;
	Timer last_time;
	int num_loops = 0;
	double max_speed;
public:
	DriveAutoLines(double distance, double angle, double epsilon = 15, double speed_max = 0.6, bool timed = false);

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

