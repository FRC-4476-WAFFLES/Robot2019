/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
//PWM
constexpr int LEFT_CARGO_CARRIAGE = 0;//SPX
constexpr int RIGHT_CARGO_CARRIAGE = 9;//SPX

constexpr int SPARE_SP_1 = 8;
constexpr int SPARE_SP_2 = 1;
//CAN
constexpr int DRIVE_RIGHT1 = 1;//SRX
constexpr int DRIVE_RIGHT2 = 2;//SPX
constexpr int DRIVE_RIGHT3 = 3;//SPX
constexpr int DRIVE_LEFT1 = 4;//SRX
constexpr int DRIVE_LEFT2 = 5;//SPX
constexpr int DRIVE_LEFT3 = 6;//SPX

constexpr int ELEVATOR_MASTER = 7;//SRX
constexpr int ELEVATOR_FOLLOWER = 8;//SRX

constexpr int CARGO_EXTEND = 8;//SPX
constexpr int CARGO_INTAKE = 10;//SPX



constexpr int CLIMB_MASTER = 13;//SPARK MAX
constexpr int CLIMB_FOLLOWER = 14;//SPARK MAX

constexpr int LIGHT_STRIP = 15;//canifier

//PCM
constexpr int HATCH_CLAMP = 0;//double solonoid
constexpr int HATCH_UNCLAMP = 1;//double solenoid
constexpr int HATCH_EXTEND = 2;//double Solenoid
constexpr int HATCH_UNEXTEND = 3;//double Solenoid

//DIGITAL INPUT

//ANALOG INPUT


// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
