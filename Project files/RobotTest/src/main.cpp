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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
int i = 215;
int main() {
  //Left motors: LeftDriveSmart
  //Right motors: RightDriveSmart
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  while (!Itsabumber.pressing()) {
    Drivetrain.setDriveVelocity(25,percent);
    Drivetrain.drive(reverse);
  }
  Drivetrain.stop();
  Drivetrain.driveFor(reverse,i,mm);
  Drivetrain.turnFor(left,180,degrees);
  Motor9.spinFor(forward,50,degrees);
  Claw.spinFor(forward,10,degrees);
  Drivetrain.driveFor(forward,i,mm);
  Claw.spinFor(reverse,10,degrees); //This needs to be done
}
