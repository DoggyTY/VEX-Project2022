/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       e2622588                                                  */
/*    Created:      Wed Sep 28 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor_group   1, 3            
// RightDrive           motor_group   8, 10           
// Drivetrain           drivetrain
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_drivetrain.h"
#include "vex_global.h"

using namespace vex;
void AceBase();
void ControlStick();


/* 
IMPORTANT VARIBLES/UNITS

One tile on the board: 14 inches
90 degree turn: 73 degrees
1 degree turn: 0.8111111111111111111111111111111111111 (This is infinite but change it to 8 if you want to)
*/
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  ControlStick();
  //AceBase();
}

void AceBase() {
  Drivetrain.setDriveVelocity(30,percent);
  while (true) {
    if (Controller1.ButtonUp.pressing()) {
      Drivetrain.drive(forward);
    } else if (Controller1.ButtonDown.pressing()) {
      Drivetrain.drive(reverse);
    } else if (Controller1.ButtonLeft.pressing()) {
      Drivetrain.turn(left);
    } else if(Controller1.ButtonRight.pressing()) {
      Drivetrain.turn(right);
    } else {
      Drivetrain.stop();
    }
    if (Controller1.ButtonA.pressing()) {
      Drivetrain.stop();
      break;
    }
  }
  Drivetrain.driveFor(forward,65,inches);
  Drivetrain.turnFor(left,73,degrees);
  Drivetrain.driveFor(forward,50,inches);
  Drivetrain.turnFor(right,73,degrees);
  Drivetrain.driveFor(forward,83,inches);
  Drivetrain.turnFor(right,73,degrees);
  Drivetrain.driveFor(forward,50,inches);
  Drivetrain.turnFor(left,73,degrees);
  Drivetrain.driveFor(forward,65,inches);
}

void ControlStick() {
  int AxisThree = Controller1.Axis3.position();
  int AxisFour = Controller1.Axis4.position();
  while (true) {
    LeftDrive.spin(forward);
    RightDrive.spin(forward);
    if (AxisFour > 33 or AxisFour < -33) {
      LeftDrive.setVelocity(AxisThree+AxisFour,pct);
      RightDrive.setVelocity(AxisThree-AxisFour,pct);
    } else {
      LeftDrive.setVelocity(AxisThree,pct);
      RightDrive.setVelocity(AxisThree,pct);
    }
  }
}

// Don't look down here there isn't anything down here but suffering :)