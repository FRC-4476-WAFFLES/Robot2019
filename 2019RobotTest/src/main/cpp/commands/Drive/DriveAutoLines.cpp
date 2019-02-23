#include "../include/commands/Drive/DriveAutoLines.h"
#include "subsystems/DriveSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Utils/PIDPreferences.h"
#include "Robot.h"

double clamp(double value, double min, double max) {
	//function to make sure a givien value doesn't exceed the given parameters.
	if(value < min) {
		return min;
	} else if(value > max) {
		return max;
	} else {
		return value;
	}
}

DriveAutoLines::DriveAutoLines(double distance, double angle, double epsilon, double speed_max, bool timed):
		//constructor to tell the commands functions the info input to the constructor
		frc::Command("DriveAutoLines"),
		//distance is input in feet, this is the converstion to encoder tics
		distance(distance * 680),//TODO: find the distance in a foot
		angle(angle),
		epsilon(epsilon),
		max_speed(speed_max)
{
	//makes sure this is the only command accessing the drive
	Requires(&Robot::Drive);
}


// Called just before this Command runs the first time
void DriveAutoLines::Initialize() {
	//add the target distance/angle to the last set distance/angle
	Robot::Drive.target_distance += distance;
	Robot::Drive.target_angle += angle;

	//calculate how far off the target we are to use int the PID
	double distance_error = Robot::Drive.target_distance - (Robot::Drive.Left() + Robot::Drive.Right()) / 2.0;
	double angle_error = Robot::Drive.target_angle - Robot::Drive.Gyro();

	//since this is the first time this command has been run, the last error will be the same as the current one
	last_distance_error = distance_error;
	last_angle_error = angle_error;
	last_time.Reset();
	last_time.Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveAutoLines::Execute() {
	//update the distance and angle error based on the newst data for the PID
	//these variables are created and destroyed every time the function is called.
	double distance_error = Robot::Drive.target_distance - (Robot::Drive.Left() + Robot::Drive.Right()) / 2.0;
	double angle_error = Robot::Drive.target_angle - Robot::Drive.Gyro();
	//get the time "error"
	double time = last_time.Get();
	last_time.Reset();
	last_time.Start();

	//output the errors to shuffleboard
	SmartDashboard::PutNumber("Drive Error", distance_error);
	SmartDashboard::PutNumber("Angle Error", angle_error);

	//set these temporary variables to the user input pid from prefrences on shuffleboard times how far off the target we are (calc p)
	double distance_p = GetP("drive_distance", 0.0 ) * distance_error; //TODO:tune PID
	double angle_p = GetP("drive_angle", 0.0) * angle_error;

	//set d for the drive forward only if the robot is far enough away to need it.
	double distance_d = 0.0;//TODO: Tune PID
	if(fabs(distance) > 0.1) {
		//calculation for d based on time
		distance_d = GetD("drive_distance", 0.0) * ((distance_error - last_distance_error) / time);
	}
	double angle_d = GetD("drive_angle", 0.0) * ((angle_error - last_angle_error) / time);

	//set the percent output of the drive and clamp it to the max set by the user
	double distance_out = clamp(distance_p + distance_d, -max_speed, max_speed);
	double angle_out = clamp(angle_p + angle_d, -0.45, 0.45);//TODO: Check Clamp For Max Output

	//tell the drive what to do
	Robot::Drive.WafflesDrive(-distance_out + angle_out, -distance_out - angle_out);

	//the current error is now outdated.
	last_angle_error = angle_error;
	last_distance_error = distance_error;

}

// Make this return true when this Command no longer needs to run execute()
bool DriveAutoLines::IsFinished() {
	//calculate the error in drive and turn
	double distance_error = Robot::Drive.target_distance - (Robot::Drive.Left() + Robot::Drive.Right()) / 2.0;
	double angle_error = Robot::Drive.target_angle - Robot::Drive.Gyro();

//	if(fabs(distance_error) < epsilon && fabs(angle_error) < epsilon/8) {
//		num_loops++;
//	} else {
//		num_loops = 0;
//	}
//
//	return num_loops > 5;
//}
	//check if the error is within the limit set by the user
	return fabs(distance_error) < epsilon && fabs(angle_error) < epsilon/8;
}

// Called once after isFinished returns true
void DriveAutoLines::End() {
	//stop the motors
	Robot::Drive.WafflesDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveAutoLines::Interrupted() {
	//stop the motors
	Robot::Drive.WafflesDrive(0,0);
}
