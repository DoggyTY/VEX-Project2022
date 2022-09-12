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
// Right Joystick Down
int Axisone = Controller1.Axis1.position(percent);
// Right Joystick Up
int Axistwo = Controller1.Axis2.position(percent);
// Left Joystick Up
int Axisthree = Controller1.Axis3.position(percent);
// Left Joystick Down
int Axisfour = Controller1.Axis4.position(percent);

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

double FindGoal(int x int z){
  double xDist = sqrt(pow(abs(GoalX-x),2)+pow(abs(z-GoalZ),2));
  return sqrt(pow(xDist,2)+pow(GoalY))
}

// Player control
void player() {

}