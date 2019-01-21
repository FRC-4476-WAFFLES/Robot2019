#include "../include/Utils/PIDPreferences.h"
#include "frc/Preferences.h"
using namespace frc;
double UpdateSinglePreference(std::string name, double v) {
	if(!Preferences::GetInstance()->ContainsKey(name)) {
		Preferences::GetInstance()->PutDouble(name, v);
	}
	return Preferences::GetInstance()->GetDouble(name, v);
}

void UpdatePID(std::string name, WPI_TalonSRX &talon, double p, double i, double d, double f) {
	talon.Config_kP(0, UpdateSinglePreference(name + " P", p), 0);
	talon.Config_kI(0, UpdateSinglePreference(name + " I", i), 0);
	talon.Config_kD(0, UpdateSinglePreference(name + " D", d), 0);
	talon.Config_kF(0, UpdateSinglePreference(name + " F", f), 0);
}

void UpdatePID(std::string name, WPI_TalonSRX &talon, double p, double i, double d) {
	UpdatePID(name, talon, p, i, d, 0.0);
}

void UpdatePID(std::string name, WPI_TalonSRX &talon) {
	UpdatePID(name, talon, 0.0, 0.0, 0.0, 0.0);
}

double GetP(std::string name, double v) {
	return UpdateSinglePreference(name + " P", v);
}

double GetI(std::string name, double v) {
	return UpdateSinglePreference(name + " I", v);
}

double GetD(std::string name, double v) {
	return UpdateSinglePreference(name + " D", v);
}
