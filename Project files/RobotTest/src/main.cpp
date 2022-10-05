/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Team 8861F                                                */
/*    Created:      Tue Sep 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor_group   1, 3            
// RightDrive           motor_group   8, 10           
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void AceBase();
void Player();
double FindGoal(int x, int z);

bool Auto = false;
int GoalY = 0;
int GoalX = 0;
int GoalZ = 0;
double RobotY = 0;
double RobotX = 0; // Need to change this to GPS sensors
double RobotZ = 0;
double RobotHead = 0;
// Right Joystick Horizonal
int RightSide = Controller1.Axis1.position(percent);
// Right Joystick Vertical
int RightVert = Controller1.Axis2.position(percent);
// Left Joystick Vertical
int LeftVert = Controller1.Axis3.position(percent);
// Left Joystick Horizonal
int LeftSide = Controller1.Axis4.position(percent);

int i = 215;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  AceBase();

  return 0;
}

double FindGoal(int x, int z) {
  return sqrt(pow(abs(GoalX - x), 2) + pow(abs(z - GoalZ), 2));
}

// Player control
void Player() {
  LeftDrive.setVelocity(LeftVert, pct);
  RightDrive.setVelocity(LeftVert, pct);

  while (true) {
    //LeftDrive, Left wheels -- LeftDriveMotorB
    //RightDrive, Right wheels -- RightDriveMotorE
    LeftDrive.spin(forward);
    RightDrive.spin(forward);

    if (LeftSide > 33 or LeftSide < -33) {
      LeftDrive.setVelocity(LeftVert + LeftSide, pct);
      RightDrive.setVelocity(LeftVert - LeftSide, pct);
    } else {
      LeftDrive.setVelocity(LeftVert, pct);
      RightDrive.setVelocity(LeftVert, pct);
    }
  }
}
void AceBase() {
  while (!Auto) {
    if (Controller1.ButtonUp.pressing()) {
      LeftDrive.spin(forward);
      RightDrive.spin(forward);
    } else if (Controller1.ButtonRight.pressing()) {
      LeftDrive.spin(forward);
      RightDrive.spin(reverse);
    } else if (Controller1.ButtonLeft.pressing()) {
      LeftDrive.spin(reverse);
      RightDrive.spin(forward);
    } else if (Controller1.ButtonA.pressing()) {
      Auto = true;
    } else {
      LeftDrive.stop();
      RightDrive.stop();
    }
    wait(0.1,seconds);
  }

    
    LeftDrive.spinFor(forward, 1, turns, false);
    RightDrive.spinFor(forward, 1, turns);
//  //we need to find out how far 1 turn of the mortor is or what the 
//  //method for the robot to drive a fixed distance because I forget what that is
//  LeftDrive.spinFor(reverse, 1, turns, false);
//  RightDrive.spinFor(forward, 1, turns);
//  //first turn
//  LeftDrive.spinFor(forward, 1, turns, false);
//  RightDrive.spinFor(forward, 1, turns);
//  //second straight portion
//  LeftDrive.spinFor(forward, 1, turns, false);
//  RightDrive.spinFor(reverse, 1, turns);
//  //second turn
//  LeftDrive.spinFor(forward, 1, turns, false);
//  RightDrive.spinFor(forward, 1, turns);
//  //third straight portion
//  LeftDrive.spinFor(forward, 1, turns, false);
//  RightDrive.spinFor(reverse, 1, turns);
//  //third turn
//  LeftDrive.spinFor(forward, 1, turns, false);
//  RightDrive.spinFor(forward, 1, turns);
//  //fourth straight portion
//  LeftDrive.spinFor(reverse, 1, turns, false);
//  RightDrive.spinFor(forward, 1, turns);
//  //fifth turn
//  LeftDrive.spinFor(forward, 1, turns, false);
//  RightDrive.spinFor(forward, 1, turns);
//  //fifth straight portion
}