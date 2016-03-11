#pragma config(Motor,  port1,           Elevator,      tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           Intake,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           DriveL1,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           DriveR1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           TowerM1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           TowerM2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           TowerM3,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           DriveL2,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           DriveR2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          DriveL3,       tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#define rpmDelay 100

int targetRPM = 0;
int RPM = 0;
int fwOutput = 0;
int ballCount = 0;

bool ballReady = false;
bool RPMReady = false;
bool newRPM = false;

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "tasks.c"

const unsigned int TrueSpeed[128] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
 25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
 28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
 33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
 37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
 41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
 46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
 52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
 61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
 71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
 80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
 88, 89, 89, 90, 90,127,127,127
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	while (true)
	{
	  // Tank Drive w/ deadzone of 20
	  if (vexRT[Ch3] > 20)
	  	motor[DriveL1] = motor[DriveL2] = motor[DriveL3] = TrueSpeed[abs(vexRT[Ch3])];
		else if (vexRT[Ch3] < -20)
			motor[DriveL1] = motor[DriveL2] = motor[DriveL3] = -TrueSpeed[abs(vexRT[Ch3])];
		else
			motor[DriveL1] = motor[DriveL2] = motor[DriveL3] = 0;
		if (vexRT[Ch2] > 20)
			motor[DriveR1] = motor[DriveR2] = TrueSpeed[abs(vexRT[Ch2])];
		else if (vexRT[Ch2] < -20)
			motor[DriveR1] = motor[DriveR2] = -TrueSpeed[abs(vexRT[Ch2])];
		else
			motor[DriveR1] = motor[DriveR2] = 0;

	  // Front Intake Control
		if (vexRT[Btn6U])
			motor[Intake] = 127;
		else if (vexRT[Btn6D])
			motor[Intake] = -127;
		else
			motor[Intake] = 0;

		// Elevator Control
		if (vexRT[Btn5U])
			motor[Elevator] = 127;
		else if (vexRT[Btn5D])
			motor[Elevator] = -127;
		else
			motor[Elevator] = 0;

		// Tower Motor Control
		if (vexRT[Btn8L]) // control flywheel
			motor[TowerM1] = motor[TowerM2] = motor[TowerM3] = 60;
		else if (vexRT[Btn8R])
			motor[TowerM1] = motor[TowerM2] = motor[TowerM3] = 75;
		else if (vexRT[Btn8U])
			motor[TowerM1] = motor[TowerM2] = motor[TowerM3] = 127;
		else if (vexRT[Btn7L]) // control puncher
			motor[TowerM1] = motor[TowerM2] = motor[TowerM3] = -127;
		else if (vexRT[Btn8D] || vexRT[Btn7L] == false)
		{
			motor[TowerM1] = motor[TowerM2] = motor[TowerM3] = 0;
		}
	}
}
