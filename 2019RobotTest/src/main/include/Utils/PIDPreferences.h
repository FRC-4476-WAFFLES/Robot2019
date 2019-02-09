#pragma once
#include <string>
#include <ctre/Phoenix.h>
#include <frc/Preferences.h>

void UpdatePID(std::string name, WPI_TalonSRX &talon, double p, double i, double d, double f);
void UpdatePID(std::string name, WPI_TalonSRX &talon, double p, double i, double d);
void UpdatePID(std::string name, WPI_TalonSRX &talon);
void UpdateSP_PID(std::string name, WPI_VictorSPX &victor, double p, double i, double d, double f);
double GetP(std::string name, double v);
double GetI(std::string name, double v);
double GetD(std::string name, double v);
double UpdateSinglePreference(std::string name, double v);
