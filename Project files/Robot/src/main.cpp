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
// LeftDrive            motor_group   11, 12          
// RightDrive           motor_group   1, 2            
// Drivetrain           drivetrain    21, 20, 19, 18  
// ShootMotors          motor_group   5, 6            
// IntakeMotors         motor_group   3, 4            
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
void intakeup(double i);
void intakedown(double i);
int Speedcap = 2;
int Turncap = 2;
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
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  IntakeMotors.setVelocity(100,percent);
  ShootMotors.setVelocity(75,percent);
  while (true){
    if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33){
      LeftDrive.setVelocity((Controller1.Axis3.position()+Controller1.Axis4.position())/Turncap,percent);
      RightDrive.setVelocity((Controller1.Axis3.position()-Controller1.Axis4.position())/Turncap,percent);
    } else{
      LeftDrive.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
      RightDrive.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
    }
    while (Controller1.ButtonL1.pressing()){
      intakeup(0.1);
    }
    while (Controller1.ButtonL2.pressing()){
      intakedown(0.1);
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
void roller(double i){
  IntakeMotors.spinFor(i,seconds);
}
void shoot(double i){
  ShootMotors.spinFor(i,seconds);
}
void intakeup(double i){
  IntakeMotors.spinFor(i,seconds);
}
void intakedown(double i){
  IntakeMotors.spinFor(i,seconds);
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