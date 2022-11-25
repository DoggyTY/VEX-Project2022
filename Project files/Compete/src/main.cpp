/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    8, 9, 20, 21    
// IntakeMotors         motor_group   1, 2            
// ShootMotors          motor_group   3, 4            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_global.h"

using namespace vex;
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
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  Auto();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(reverse);
  IntakeMotors.setVelocity(20,percent);
  ShootMotors.setVelocity(75,percent);
  while (true){
     if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33){
       LeftDriveSmart.setVelocity((Controller1.Axis3.position()-Controller1.Axis4.position())/Turncap,percent);
       RightDriveSmart.setVelocity((Controller1.Axis3.position()+Controller1.Axis4.position())/Turncap,percent);
     } else{
       LeftDriveSmart.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
       RightDriveSmart.setVelocity(Controller1.Axis3.position()/Speedcap,percent);
     }
    if (Controller1.ButtonL1.pressing() && Intakeon == false){
      intakeup();
    } else {
      IntakeMotors.stop();
      Intakeon = false;
      wait(0.1, seconds);
    }
    if (Controller1.ButtonL2.pressing() && Intakeon == false){
      intakedown();
    } else {
      IntakeMotors.stop();
      Intakeon = false;
      wait(0.1, seconds);
    }
    while (Controller1.ButtonR1.pressing()){
      shoot(0.1);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
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
void intakeup(){
  IntakeMotors.spin(forward);
  Intakeon = true;
  wait(0.1, seconds);
}
void intakedown(){
  IntakeMotors.spin(reverse);
  Intakeon = true;
  wait(0.1, seconds);
}
//Don't look down here there isn't anything down here but suffering :)
//and Cody's dumb methods XD