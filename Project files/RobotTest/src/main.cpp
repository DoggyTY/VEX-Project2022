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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
bool b = false;
int i = 0;
int main() {
  //Left motors: LeftDriveSmart
  //Right motors: RightDriveSmart
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (!b) {
    Drivetrain.setDriveVelocity(25,percent);
    Drivetrain.drive(forward);
  }
  Drivetrain.stop();
  Drivetrain.driveFor(reverse,i,mm);
  Drivetrain.turnFor(left,180,degrees);
  Motor9.spinFor(forward,50,degrees);
  //other motor open
  Drivetrain.driveFor(forward,i,mm);
  //other motor close
}
