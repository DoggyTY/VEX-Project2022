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
void gps();
void Shootsetup();

int Speedcap = 1;
int Turncap = 1;
int Shootvelo = 60;
bool IntakeOn = false;
char complaint[] = "nathan blames us for everything smh my head";

// Global GPS vars
double Anglelooking = 0;
dpr = 3; //Distance per rotation, need to test numbers, also should be in mm, because else it would break resulting in Robot Position Fault
bool Left = false;
bool PosFault = false; // This is something to use if having problems with robot going to far that it gps goes out the arena, making any system that uses gps disable until problem is resolved.
double Xrpm; 
double Yrpm;
double Xdis;
double Ydis;
double VectorRPM;
double VectorDis;
// Measured in mm by default
double Xaxis;
double Yaxis;
double FieldX = 3650; // 12 feet, if need inches/feet. Position 0 is the corner of own low goal
double FieldY = 3650;
double LowGoal = 1200; // 1 Tile is 600 by 600, or 24 by 24 inches
double LowGoalHeight = 543.56; // 21.4 inches
double HeighGoalX = 3050;
double HeightGoalY = 3050;
int XDistoGoal, YDistoGoal, VectorDistoGoal,AngleToGoal,DisAngleGoal,VelocityToGoal; //All Varibles to support Shoot Setup Modular
double ShootAngleFault = 300;



/* Important Variables and Stuff
  1 Rotation is __ distance
  1.22 degrees for 1 degrees
  1 inche is 1 inche, I know revolutionary
  70 percent power directly diagonal to goal
  74 percent power toward 3 disk
*/
int main(){
  vexcodeInit();
  Drivetrain.driveFor(reverse,6,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(reverse,26,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(reverse,14,inches);
  // Drivetrain.driveFor(forward,6,inches);
  // Drivetrain.turnFor(right,160,degrees);
  // Drivetrain.driveFor(reverse,24,inches);
  // Drivetrain.turnFor(left,109.8,degrees);
  // ShootMotors.setVelocity(65,percent);
  // ShootMotors.spin(forward);
  wait(2,seconds);
  // IntakeMotors.spinFor(forward,5,seconds);
  // ShootMotors.stop();
  IntakeMotors.stop();
  Controller();
}
void Controller(){
  LeftDriveSmart.setVelocity(0,percent);
  RightDriveSmart.setVelocity(0,percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  ShootMotors.setVelocity(60,percent);
  while (true){
    if (Controller1.ButtonLeft.pressing()){
      LeftDriveSmart.setVelocity(-10,percent);
      RightDriveSmart.setVelocity(10,percent);
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
    }
    else {
      IntakeMotors.stop();
    }
    if(Controller1.ButtonR1.pressing()){
      Shootsetup();
    while (Controller1.ButtonR1.pressing()){
      ShootMode();
    }
    }
    if (Controller1.ButtonA.pressing() && Controller1.ButtonX.pressing() && Controller1.ButtonY.pressing() && Controller1.ButtonB.pressing()) {
      Expand.set(true);
    }
    ShootMotors.stop();
  }
  gps();
}
Shootsetup() {
  if (PosFault == true){
    return NULL
  }
  XDistoGoal = HeighGoalX - Xaxis;
  YDistoGoal = HeightGoalY - Yaxis;
  VectorDistoGoal = sqrt(pow(XDistoGoal,2) + pow(YDistoGoal,2));
  if(XDistoGoal < 0) {
    Left = true;
  }
  XDistoGoal = abs(XDistoGoal);
  AngleToGoal = acos(YDistoGoal/VectorDistoGoal);
  if (Left == true){
    AngleToGoal = AngleToGoal + 180
  }
  DisAngleGoal = Anglelooking - DisAngleGoal;
  DriveTrain.TurnFor(left,DisAngleGoal);
  // Velocity setup is next but is too hard to finish now, Rain don't do it, it needs to be specific to other varibles as we talked about.
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
  } else {
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
    Shootvelo = abs(Shootvelo - 2);
    ShootMotors.setVelocity(Shootvelo,percent);
    wait(0.1,seconds);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(2,0);
    wait(0.1,seconds);
    Controller1.Screen.print(Shootvelo);
    wait(0.1,seconds);
  } else if (Controller1.ButtonX.pressing()){
    Shootvelo = abs(Shootvelo + 2);
    ShootMotors.setVelocity(Shootvelo,percent);
    wait(0.1,seconds);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(2,0);
    wait(0.1,seconds);
    Controller1.Screen.print(Shootvelo);
    wait(0.1,seconds);
  }
  gps();
}
void Auto1stackDefault(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(reverse,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(reverse,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(right,43,degrees);
  ShootMotors.setVelocity(70,percent);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto1stackRollers(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(reverse,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,1,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto1stackShoot(){
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(reverse,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,43,degrees);
  ShootMotors.setVelocity(70,percent);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3stackDefault(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(reverse,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(right,164.7,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,45,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(right,97.6,degrees);
  ShootMotors.setVelocity(74,percent);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3stackRollers(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(reverse,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,1,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto3stackShoot(){
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(right,164.7,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,20,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,97.6,degrees);
  ShootMotors.setVelocity(74,percent);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto1stackDefaultFront(){
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(right,164.7,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,45,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(right,97.6,degrees);
  ShootMotors.setVelocity(70,percent);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto1stackRollersFront(){
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,1,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto3stackDefaultFront(){
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,26,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,43,degrees);
  ShootMotors.setVelocity(74,percent);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3stackRollersFront(){
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,109.8,degrees);
  Drivetrain.driveFor(forward,96,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(forward,96,inches);
  Drivetrain.turnFor(left,109.8,degrees);
  Drivetrain.driveFor(reverse,4,inches);
  IntakeMotors.spinFor(reverse,1,seconds);
}

void gps() {
  // This is all prototype code and none of it really can fuction well, all theoretical
  // Also need to rewrite some of it to make sure that its correctly formatting gps, with x and y.
  Xrpm = Xrotation.velocity(rpm) / 60; // divide by 60 to get rps, which would be useful later... also need to convert it to a smaller number, like 0.01 millisecond because brain processes things at 1.3 trillion inputs a seconds
  Yrpm = Yrotation.velocity(rpm) / 60;
  if (Xrpm == 0 and Yrpm == 0){
    return NULL;
  }
  Xdis = Xrpm * dpr;
  Ydis = Yrpm * dpr;
  VectorRPM = sqrt(pow(Xrpm,2) + pow(Yrpm,2));
  VectorDis = sqrt(pow(Xdis,2) + pow(Ydis,2));
  if(Yrpm < 0) {
    Left = true;
  }
  Yrpm = abs(Yrpm);
  Anglelooking = acos(Xrpm/VectorRPM);
  if (Left) {
    Anglelooking = Anglelooking + 180;
  }
  Xaxis = Xaxis + Xdis;
  Yaxis = Yaxis + Ydis;
  if (Xaxis > FieldX or Yaxis > FieldY){
    Controller1.Screen.setCursor(2,3);
    Controller1.Screen.print("Robot Position Fault"); // Making it known to driver of PosFault, Should do this with other things but yeah
    PosFault = true;
  } else {
    Controller1.Screen.ClearScreen();
    PosFault = false;
  }
  Controller1.Screen.setCursor(0,0); // Mainly for trouble shooting but could be useful for other things
  Controller1.Screen.print(Xaxis);
  Controller1.Screen.setCursor(0,1);
  Controller1.Screen.print(Yaxis);
  return true;
}
//Don't look down here there isn't anything down here but suffering :)
//and our dumb methods XD
//also vex devices are painful D: