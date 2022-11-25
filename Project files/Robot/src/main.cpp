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
int Speedcap = 2;
int Turncap = 2;
bool Intakeon = false;
/*
IMPORTANT VARIBLES/UNITS
One tile on the board: 14 inches
90 degree turn: 73 degrees
1 degree turn: 0.8111111111111111111111111111111111111 (This is infinite but change it to 8 if you want to)
*/
int main(){
  vexcodeInit();
  // Auto1Default();
  // Auto3Default();

  // Auto1Rollers();
  // Auto3Rollers();
  
  // Auto1Shoot();
  // Auto3Shoot();
  Controller();
}
void Controller(){
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(reverse);
  IntakeMotors.setVelocity(10,percent);
  ShootMotors.setVelocity(75,percent);
  while (true){
     if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33){
       LeftDriveSmart.setVelocity((Controller1.Axis3.position()+Controller1.Axis4.position())/Turncap,percent);
       RightDriveSmart.setVelocity((Controller1.Axis3.position()-Controller1.Axis4.position())/Turncap,percent);
     } else{
       LeftDriveSmart.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
       RightDriveSmart.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
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
void Auto1Default(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,26,inches);
  Drivetrain.turnFor(left,90,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,35,degrees);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto1Rollers(){
  //preload 2 discs
  //once robot works I have an idea for not needing to preload 
  //and being able to just pick up 3 discs on the way
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,96,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,96,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto1Shoot(){
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,35,degrees);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3Default(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(right,135,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,45,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(right,80,degrees);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3Rollers(){
  //preload 2 discs
  //once robot works I have an idea for not needing to preload 
  //and being able to just pick up 3 discs on the way
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,96,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,96,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto3Shoot(){
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(left,135,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,20,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(right,80,degrees);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
//Don't look down here there isn't anything down here but suffering :)
//and Cody's dumb methods XD