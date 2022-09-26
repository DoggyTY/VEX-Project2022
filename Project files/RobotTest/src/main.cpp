/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       e2622588                                                  */
/*    Created:      Tue Sep 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor_group   1, 3            
// LeftDriveMotorB      motor         2               
// RightDrive           motor_group   8, 10           
// RightDriveMotorE     motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
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
  //wait(4,sec);
  //Player();
}

double FindGoal(int x, int z){
  return sqrt(pow(abs(GoalX-x),2)+pow(abs(z-GoalZ),2));
}


// Player control
void Player() {
  LeftDrive.setVelocity(LeftVert,pct);
  LeftDriveMotorC.setVelocity(LeftVert,pct);
  RightDrive.setVelocity(LeftVert,pct);
  RightDriveMotorC.setVelocity(LeftVert,pct);
  while (true){
    //LeftDrive, Left wheels -- LeftDriveMotorB
    //RightDrive, Right wheels -- RightDriveMotorE
    LeftDrive.spin(forward);
    LeftDriveMotorC.spin(forward);
    RightDrive.spin(forward);
    RightDriveMotorC.spin(forward);
    if (LeftSide > 33 or LeftSide < -33) {
      LeftDrive.setVelocity(LeftVert+LeftSide,pct);
      LeftDriveMotorC.setVelocity(LeftVert+LeftSide,pct);
      RightDrive.setVelocity(LeftVert-LeftSide,pct);
      RightDriveMotorC.setVelocity(LeftVert-LeftSide,pct);
    } else {
      LeftDrive.setVelocity(LeftVert,pct);
      LeftDriveMotorC.setVelocity(LeftVert,pct);
      RightDrive.setVelocity(LeftVert,pct);
      RightDriveMotorC.setVelocity(LeftVert,pct);
    }
  }
}

void AceBase(){
  while (true){
    if (Controller1.ButtonUp.pressing()){
      LeftDrive.spin(forward);
      RightDrive.spin(reverse);
      LeftDriveMotorC.spin(reverse);
      RightDriveMotorC.spin(forward);
    }
    else if (Controller1.ButtonRight.pressing()) {
      LeftDrive.spin(reverse);
      RightDrive.spin(forward);
      LeftDriveMotorC.spin(forward);
      RightDriveMotorC.spin(reverse);
    }
    else if (Controller1.ButtonLeft.pressing()){
      LeftDrive.spin(forward);
      RightDrive.spin(reverse);
      LeftDriveMotorC.spin(reverse);
      RightDriveMotorC.spin(forward);
    }
    else {
      LeftDrive.stop();
      RightDrive.stop();
      LeftDriveMotorC.stop();
      RightDriveMotorC.stop();
    }
  }
}

// Don't look down here there isn't anything down here but suffering :)