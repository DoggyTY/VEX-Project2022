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
// Drivetrain           drivetrain    1, 10           
// Motor9               motor         9               
// Claw                 motor         3               
// Itsabumber           bumper        A               
// Controller1          controller                    
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
  //Left motors: LeftDriveSmart
  //Right motors: RightDriveSmart
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
    
  }
}