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
// Drivetrain           drivetrain    21, 20, 19, 18  
// RollMotor            motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "v5_apitypes.h"
#include "vex.h"
#include "vex_drivetrain.h"
#include "vex_global.h"

using namespace vex;
void AceBase();
void ControlStick();
void CompAuto();
int Speedcap = 2;
int Turncap = 2;
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
  CompAuto();
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
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  RollMotor.setVelocity(100,percent);
  while (true) {
    if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33) {
      LeftDrive.setVelocity((Controller1.Axis3.position()+Controller1.Axis4.position())/Turncap,percent);
      RightDrive.setVelocity((Controller1.Axis3.position()-Controller1.Axis4.position())/Turncap,percent);
    } else {
      LeftDrive.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
      RightDrive.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
    }

    if (Controller1.ButtonR2.pressing()) {
      RollMotor.spin(forward);
    } else if (Controller1.ButtonR1.pressing()) {
      RollMotor.spin(reverse);
    } else {
      RollMotor.stop();
    }
    if (Controller1.ButtonA.pressing()){
      break;
    }
  }
}

void CompAuto() {
  Drivetrain.driveFor(1,inches);
  Drivetrain.turnFor(73,degrees);
  Drivetrain.driveFor(14,inches);
  Drivetrain.turnFor(73,degrees);
  Drivetrain.driveFor(2,inches);
  RollMotor.spin(forward);
  wait(1,seconds);
  RollMotor.stop();
}

// Don't look down here there isn't anything down here but suffering :)