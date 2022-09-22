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
// LeftDrive            motor_group   1, 2, 3
// RightDrive           motor_group   8, 9, 10        
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
  
  //while(!Controller1.ButtonA.pressing()){
    //Brain.Screen.print(Axisone);
    //Brain.Screen.newLine();
    //Brain.Screen.print(Axistwo);
    //Brain.Screen.newLine();
    //Brain.Screen.print(Axisthree);
    //Brain.Screen.newLine();
  //  Brain.Screen.print(Axisfour);
  //  Brain.Screen.newLine();
  //}
  //while (!Itsabumber.pressing()) {
  //  Drivetrain.setDriveVelocity(25,percent);
  //  Drivetrain.drive(reverse);
  //}
  //Drivetrain.stop();
  //Drivetrain.driveFor(reverse,i,mm);
  //Drivetrain.turnFor(left,180,degrees);
  //Motor9.spinFor(forward,50,degrees);
  //Claw.spinFor(forward,10,degrees);
  //Drivetrain.driveFor(forward,i,mm);
  //Claw.spinFor(reverse,10,degrees); //This needs to be done
}

double FindGoal(int x, int z){
  return sqrt(pow(abs(GoalX-x),2)+pow(abs(z-GoalZ),2));
}


// Player control
void Player() {
  while (true){
    LeftDrive.setVelocity(LeftVert,pct);
    RightDrive.setVelocity(LeftVert,pct);
    //LeftDrive, Left wheels
    //RightDrive, Right wheels
    LeftDrive.Spin(forward);
    RightDrive.Spin(forward);
    if (LeftSide != 0) {
      LeftDrive.setVelocity(LeftVert+LeftSide,pct);
      RightDrive.setVelocity(LeftVert-RightVert,pct);
    } else {
      LeftDrive.setVelocity(LeftVert,pct);
      LeftDrive.setVelocity(LeftVert,pct);
    }

  }
}