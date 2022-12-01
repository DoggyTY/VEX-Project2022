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
void Auto1DefaultFront();
void Auto1RollersFront();
void Auto3DefaultFront();
void Auto3RollersFront();
void intakeup();
void intakedown();
void ShootMode();
int Speedcap = 1;
int Turncap = 1;
int Shootvelo = 20;
bool IntakeOn = false;
char complaint[] = "nathan blames us for everything smh my head";

/* Important Variables and Stuff
  1.22 degrees for 1 degrees
  1 inche is 1 inche, I know revolutionary
  70 percent power directly diagonal to goal
  74 percent power toward 3 disk
*/
int main(){
  vexcodeInit();
  //Drivetrain.driveFor(reverse,23,inches);
  Controller();
}
void Controller(){
  LeftDriveSmart.setVelocity(0,percent);
  RightDriveSmart.setVelocity(0,percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  ShootMotors.setVelocity(30,percent);
  while (true){
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
    } else if (Controller1.Axis4.position() > 33 || Controller1.Axis4.position() < -33){
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
      IntakeMotors.setVelocity(10,percent);
      IntakeMotors.spin(reverse); 
    } else {
      IntakeMotors.stop();
    }
    while (Controller1.ButtonR1.pressing()){
      ShootMode();
    }
    ShootMotors.stop();
  }
}
void ShootMode() {
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
}
void Auto3stackDefault(){
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(left,110,degrees);
  Drivetrain.driveFor(forward,24,inches);
  Drivetrain.turnFor(left,110,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(reverse,4,inches);
  Drivetrain.turnFor(left,110,degrees);
  Drivetrain.driveFor(forward,26,inches);
  Drivetrain.turnFor(left,110,degrees);
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,43,degrees);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3stackRollers(){
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,4,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(reverse,4,inches);
  IntakeMotors.spinFor(reverse,1,seconds);
}
void Auto3stackShoot(){
  IntakeMotors.spin(forward);
  Drivetrain.driveFor(forward,24,inches);
  IntakeMotors.stop();
  Drivetrain.turnFor(left,35,degrees);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto1stackDefault(){
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
void Auto1stackRollers(){
  IntakeMotors.spinFor(forward,1,seconds);
  Drivetrain.driveFor(forward,1,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,120,inches);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,4,inches);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto1stackShoot(){
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
void Auto1DefaultFront(){
  
}
void Auto1RollersFront(){

}
void Auto3DefaultFront(){

}
void Auto3RollersFront(){

}
//Don't look down here there isn't anything down here but suffering :)
//and our dumb methods XD
//also vex devices are painful D: