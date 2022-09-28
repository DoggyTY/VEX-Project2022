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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
void AceBase();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  AceBase();
}

void AceBase() {
  while (true) {
    if (Controller1.ButtonUp.pressing()) {
      LeftDrive.spin(forward);
      RightDrive.spin(forward);
    } else if (Controller1.ButtonDown.pressing()) {
      LeftDrive.spin(reverse);
      RightDrive.spin(reverse);
    } else if (Controller1.ButtonLeft.pressing()) {
      LeftDrive.spin(reverse);
      RightDrive.spin(forward);
    } else if(Controller1.ButtonRight.pressing()) {
      LeftDrive.spin(forward);
      RightDrive.spin(reverse);
    } else {
      LeftDrive.stop();
      RightDrive.stop();
    }
    if (Controller1.ButtonA.pressing()) {
      LeftDrive.stop();
      RightDrive.stop();
      break;
    }
  }
  wait(0.5,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  wait(3,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  wait(0.1,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(reverse);
  wait(0.75,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  //Part1
  wait(0.1,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  wait(3,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  wait(0.1,seconds);
  LeftDrive.spin(reverse);
  RightDrive.spin(forward);
  wait(0.75,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  //Part2
  wait(0.5,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  wait(3,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  wait(0.1,seconds);
  LeftDrive.spin(reverse);
  RightDrive.spin(forward);
  wait(0.75,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  //Part3
  wait(0.5,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  wait(3,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  wait(0.1,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(reverse);
  wait(0.75,seconds);
  LeftDrive.stop();
  RightDrive.stop();
  //Part4
  wait(0.5,seconds);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  wait(3,seconds);
  LeftDrive.stop();
  RightDrive.stop();
}
