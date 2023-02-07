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
void Controller();
void Auto1stackDefault();
void Auto1stackRollers();
void Auto1stackShoot();
void Auto3stackDefault();
void Auto3stackRollers();
void Auto3stackShoot();
void Auto1stackDefaultFront();
void Auto1stackRollersFront();
void Auto3stackDefaultFront();
void Auto3stackRollersFront();
void intakeup();
void intakedown();
void ShootMode();
int Speedcap = 1;
int Turncap = 1;
int Shootvelo = 60;
bool IntakeOn = false;
char complaint[] = "nathan blames us for everything smh my head";
void Position();
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
  // Drivetrain.driveFor(reverse,6,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // Drivetrain.driveFor(reverse,26,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(reverse,14,inches);
  wait(1,seconds);
  IntakeMotors.stop();
  // Drivetrain.driveFor(forward,6,inches);
  // Drivetrain.turnFor(right,160,degrees);
  // Drivetrain.driveFor(reverse,24,inches);
  // Drivetrain.turnFor(left,109.8,degrees);
  // ShootMotors.setVelocity(65,percent);
  // ShootMotors.spin(forward);
  // wait(0.5,seconds);
  // IntakeMotors.spinFor(forward,5,seconds);
  // ShootMotors.stop();
  // IntakeMotors.stop();
}
  // Drivetrain.driveFor(reverse,4,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // Drivetrain.driveFor(reverse,24,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // IntakeMotors.spin(forward);
  // Drivetrain.driveFor(reverse,4,inches);
  // wait(0.5,seconds);
  // IntakeMotors.stop();
  // Drivetrain.driveFor(forward,4,inches);
  // Drivetrain.turnFor(right,164.7,degrees);
  // Drivetrain.driveFor(forward,48,inches);
  // Drivetrain.turnFor(right,42.7,degrees);
  // ShootMotors.setVelocity(74,percent);
  // ShootMotors.spin(forward);
  // wait(0.5,seconds);
  // IntakeMotors.spinFor(forward,5,seconds);
  // ShootMotors.stop();
  //
  // Drivetrain.driveFor(reverse,4,inches);
  // Drivetrain.turnFor(left,109.8,degrees);
  // Drivetrain.driveFor(reverse,24,inches);
  // Drivetrain.turnFor(left,109.8,degrees);
  // IntakeMotors.spin(forward);
  // Drivetrain.driveFor(reverse,10,inches);
  // wait(0.5,seconds);
  // IntakeMotors.stop();
  // Drivetrain.turnFor(left,54.9,degrees);
  // Drivetrain.spinFor(reverse,120,inches);
  // Drivetrain.turnFor(left,109.8,degrees);
  // Drivetrain.spinFor(reverse,120,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // IntakeMotors.spin(forward);
  // Drivetrain.driveFor(reverse,10,inches);
  // wait(0.5,seconds);
  // IntakeMotors.stop();
  //
  // Drivetrain.driveFor(reverse,4,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // Drivetrain.driveFor(reverse,24,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // IntakeMotors.spin(forward);
  // Drivetrain.driveFor(reverse,10,inches);
  // wait(0.5,seconds);
  // IntakeMotors.stop();
  // Drivetrain.turnFor(right,54.9,degrees);
  // Drivetrain.spinFor(reverse,120,inches);
  // Drivetrain.turnFor(right,109.8,degrees);
  // Drivetrain.spinFor(reverse,120,inches);
  // Drivetrain.turnFor(left,109.8,degrees);
  // IntakeMotors.spin(forward);
  // Drivetrain.driveFor(reverse,10,inches);
  // wait(0.5,seconds);
  // IntakeMotors.stop();
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void Controller(){
  LeftDriveSmart.setVelocity(0,percent);
  RightDriveSmart.setVelocity(0,percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  ShootMotors.setVelocity(60,percent);
  while (true){
    if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33){
      LeftDriveSmart.setVelocity(((Controller1.Axis3.position()*-1)+Controller1.Axis4.position())/Turncap,percent);
      RightDriveSmart.setVelocity(((Controller1.Axis3.position()*-1)-Controller1.Axis4.position())/Turncap,percent);
    } else{
      LeftDriveSmart.setVelocity((Controller1.Axis3.position()*-1)/Speedcap,percent);
      RightDriveSmart.setVelocity((Controller1.Axis3.position()*-1)/Speedcap,percent);
    }   
    if (Controller1.ButtonL2.pressing()) {
      IntakeMotors.setVelocity(70,percent);
      IntakeMotors.spin(forward);
    } else if (Controller1.ButtonL1.pressing()) {
      IntakeMotors.setVelocity(70,percent);
      IntakeMotors.spin(reverse); 
    } else if (Controller1.ButtonDown.pressing()){
      IntakeMotors.setVelocity(10,percent);
      IntakeMotors.spin(reverse); 
    } else if (Controller1.ButtonUp.pressing()){
      IntakeMotors.setVelocity(10,percent);
      IntakeMotors.spin(forward);
    } else {
      IntakeMotors.stop();
    }
    while (Controller1.ButtonR1.pressing()){
      ShootMode();
    }
    if (Controller1.ButtonA.pressing() && Controller1.ButtonX.pressing() && Controller1.ButtonY.pressing() && Controller1.ButtonB.pressing()) {
      Expand.set(true);
    }
    ShootMotors.stop();
  }
}
void ShootMode() {
  ShootMotors.setVelocity(Shootvelo,percent);
  if (Controller1.ButtonR2.pressing()) {
    ShootMotors.spin(forward);
  } else {
    ShootMotors.stop();
  }
  if (Controller1.ButtonL2.pressing()) {
    IntakeMotors.setVelocity(70,percent);
    IntakeMotors.spin(forward);
  } else if (Controller1.ButtonL1.pressing()) {
    IntakeMotors.setVelocity(20,percent);
    IntakeMotors.spin(reverse); 
  } else if (Controller1.ButtonA.pressing()) {
    IntakeMotors.setVelocity(30,percent);
    IntakeMotors.spin(forward);
    }else {
    IntakeMotors.stop();
  }
  if (Controller1.ButtonLeft.pressing()){
    LeftDriveSmart.setVelocity(-10,percent);
    RightDriveSmart.setVelocity(10,percent);
  } else if (Controller1.ButtonRight.pressing()){
    LeftDriveSmart.setVelocity(10,percent);
    RightDriveSmart.setVelocity(-10,percent);
  } else if (Controller1.ButtonUp.pressing()){
    LeftDriveSmart.setVelocity(-10,percent);
    RightDriveSmart.setVelocity(-10,percent);
  } else if (Controller1.ButtonDown.pressing()){
    LeftDriveSmart.setVelocity(10,percent);
    RightDriveSmart.setVelocity(10,percent);
  } else {
    LeftDriveSmart.setVelocity(0,percent);
    RightDriveSmart.setVelocity(0,percent);
  } 
  if (Controller1.ButtonB.pressing()) {
    Shootvelo = abs(Shootvelo - 5);
    ShootMotors.setVelocity(Shootvelo,percent);
    wait(0.1,seconds);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(2,0);
    wait(0.1,seconds);
    Controller1.Screen.print(Shootvelo);
    wait(0.1,seconds);
  } else if (Controller1.ButtonX.pressing()){
    Shootvelo = abs(Shootvelo + 5);
    ShootMotors.setVelocity(Shootvelo,percent);
    wait(0.1,seconds);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(2,0);
    wait(0.1,seconds);
    Controller1.Screen.print(Shootvelo);
    wait(0.1,seconds);
  }
}
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(Controller);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
//Don't look down here there isn't anything down here but suffering :)
//and Cody's dumb methods XD
//We're on strike ;p

void Position(){
  Rotation.velocity(dps);
  int Xcord;
  int Zcord;
}