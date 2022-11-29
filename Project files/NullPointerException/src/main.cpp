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
void intakeup();
void intakedown();
void ShootMode();
int Speedcap = 1;
int Turncap = 1;
int Shootvelo = 20;
bool IntakeOn = false;
int main(){
  vexcodeInit();
  // Auto Code Start

  // Auto Code End
  Controller();
}
void Controller(){
  LeftDriveSmart.setVelocity(0,percent);
  RightDriveSmart.setVelocity(0,percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  IntakeMotors.setVelocity(65,percent);
  ShootMotors.setVelocity(20,percent);
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
    } else if (Controller1.Axis4.position() > 15 || Controller1.Axis4.position() < -15){
      LeftDriveSmart.setVelocity(((Controller1.Axis3.position()*-1)+Controller1.Axis4.position())/Turncap,percent);
      RightDriveSmart.setVelocity(((Controller1.Axis3.position()*-1)-Controller1.Axis4.position())/Turncap,percent);
    } else{
      LeftDriveSmart.setVelocity((Controller1.Axis3.position()*-1)/Speedcap,percent);
      RightDriveSmart.setVelocity((Controller1.Axis3.position()*-1)/Speedcap,percent);
    }   
    if (Controller1.ButtonL1.pressing()) {
      IntakeMotors.spin(forward);
    } else if (Controller1.ButtonL2.pressing()){
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
  if (Controller1.ButtonL1.pressing()) {
    IntakeMotors.spin(forward);
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
void Auto1Default(){
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value, seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.spinFor(forward,1,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);  
  wait(Value,seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.spin(forward);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.stop();
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto1Rollers(){
  //preload 2 discs
  //once robot works I have an idea for not needing to preload 
  //and being able to just pick up 3 discs on the way
  IntakeMotors.spinFor(forward,1,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto1Shoot(){
  IntakeMotors.spin(forward);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.stop();
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3Default(){
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value, seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.spinFor(forward,1,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);  
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  IntakeMotors.spin(forward);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.stop();
  LeftDriveSmart.Spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
void Auto3Rollers(){
  //preload 2 discs
  //once robot works I have an idea for not needing to preload 
  //and being able to just pick up 3 discs on the way
  IntakeMotors.spinFor(forward,1,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.spinFor(forward,1,seconds);
}
void Auto3Shoot(){
  IntakeMotors.spin(forward);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  wait(Value,seconds);
  IntakeMotors.stop();
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);
  wait(Value,seconds);
  ShootMotors.spin(forward);
  IntakeMotors.spinFor(forward,5,seconds);
  ShootMotors.stop();
}
//Don't look down here there isn't anything down here but suffering :)
//and Cody's dumb methods XD