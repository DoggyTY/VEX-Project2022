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

using namespace vex;
void AceBase();
void SlowAceBase();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //SlowAceBase();
  AceBase();
}
void SlowAceBase() {
  Drivetrain.setDriveVelocity(50,percent);
  while (true) {
    break;
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
  Drivetrain.turn(left);
  wait(2.95,seconds);
  Drivetrain.stop();
  wait(0.5,seconds);
  Drivetrain.drive(forward);
  wait(3*2,seconds);
  Drivetrain.stop();
  wait(0.1,seconds);
  Drivetrain.turn(right);
  wait(0.75*2,seconds);
  Drivetrain.stop();
  //Part1
  wait(0.1,seconds);
  Drivetrain.drive(forward);
  wait(3*2,seconds);
  Drivetrain.stop();
  wait(0.1,seconds);
  Drivetrain.turn(left);
  wait(0.75*2,seconds);
  Drivetrain.stop();
  //Part2
  wait(0.5,seconds);
  Drivetrain.drive(forward);
  wait(3*2,seconds);
  Drivetrain.stop();
  wait(0.1,seconds);
  Drivetrain.turn(left);
  wait(0.75*2,seconds);
  Drivetrain.stop();
  //Part3
  wait(0.5,seconds);
  Drivetrain.drive(forward);
  wait(3*2,seconds);
  Drivetrain.stop();
  wait(0.1,seconds);
  Drivetrain.turn(right);
  wait(0.75*2,seconds);
  Drivetrain.stop();
  //Part4
  wait(0.5,seconds);
  Drivetrain.drive(forward);
  wait(3*2,seconds);
  Drivetrain.stop();
}

void AceBase() {
  Drivetrain.setDriveVelocity(30,percent);
  while (true) {
    break;
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