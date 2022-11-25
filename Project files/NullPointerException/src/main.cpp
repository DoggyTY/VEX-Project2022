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
// ShootMotors          motor_group   3, 4            
// Drivetrain           drivetrain    9, 10, 20, 21   
// IntakeMotors         motor_group   1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "v5_apitypes.h"
#include "vex.h"
#include "vex_drivetrain.h"
#include "vex_global.h"

using namespace vex;
void Controller();
void Auto1Default();
void Auto1Rollers();
void Auto1Shoot();
void Auto3Default();
void Auto3Rollers();
void Auto3Shoot();
void driveforward(int i);
void driveback(int i);
void turnleft(double i);
void turnright(double i);
void shoot(double i);
void intakeup();
void intakedown();
int Speedcap = 1;
int Turncap = 2;

int main(){
  vexcodeInit();
  // Auto Code Start

  // Auto Code End
  Controller();
}
void Controller(){
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  IntakeMotors.setVelocity(10,percent);
  ShootMotors.setVelocity(75,percent);
  while (true){
     if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33){
       LeftDriveSmart.setVelocity(((Controller1.Axis3.position()*-1)+Controller1.Axis4.position())/Turncap,percent);
       RightDriveSmart.setVelocity(((Controller1.Axis3.position()*-1)-Controller1.Axis4.position())/Turncap,percent);
     } else{
       LeftDriveSmart.setVelocity((Controller1.Axis3.position()*-1)/Speedcap,percent);
       RightDriveSmart.setVelocity((Controller1.Axis3.position()*-1)/Speedcap,percent);
     }   
    if (Controller1.ButtonL1.pressing()){
      intakeup();
    } else if (!Controller1.ButtonL1.pressing()) {
      IntakeMotors.stop();
    }
    if (Controller1.ButtonL2.pressing()){
      intakedown();
    } else if (!Controller1.ButtonL2.pressing()) {
      IntakeMotors.stop();
    }
    while (Controller1.ButtonR1.pressing()){
      shoot(0.1);
    }
    if (Controller1.ButtonX.pressing()){
      break;
    }
  }
}
void driveforward(int i){
  Drivetrain.driveFor(forward,i,inches);
}
void driveback(int i){
  Drivetrain.driveFor(reverse,i,inches);
}
void turnleft(double i){
  Drivetrain.turnFor(left,i,degrees);
}
void turnright(double i){
  Drivetrain.turnFor(right,i,degrees);
}
void shoot(double i){
  ShootMotors.spinFor(forward, i,seconds);
}
void intakeup(){
  IntakeMotors.spin(forward);
}
void intakedown(){
  IntakeMotors.spin(reverse);
}
//Don't look down here there isn't anything down here but suffering :)
//and Cody's dumb methods XD