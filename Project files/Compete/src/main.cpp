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
void AutoSkills();
void AutoComp();
void ShootMode();
int PID();
float Speedcap = 0.8;
float Turncap = 0.8;
int Shootvelo = 80;
bool IntakeOn = false;
char complaint[] = "captain blames us for everything smh my head"; 
bool PTUactive = true;

// Global GPS vars
double Anglelooking = 0;
double Rotation = 0;
double dpr = 299.236700254; //Distance per rotation, need to test numbers, also should be in mm, because else it would break resulting in Robot Position Fault
bool Left = false;
bool PosFault = false; // This is something to use if having problems with robot going to far that it gps goes out the arena, making any system that uses gps disable until problem is resolved.
double prevoustimer = 0;
double Xrpm, Yrpm, Xdis, Ydis, rotationchange;
double Xaxis = 1;
double Yaxis = 1;
double FieldX = 3650*0.23333333333333333333333333333333333333333; // 12 feet, if need inches/feet. Position 0 is the corner of own low goal
double FieldY = 3650*0.23333333333333333333333333333333333333333;
double LowGoal = 1200*0.23333333333333333333333333333333333333333; // 1 Tile is 600 by 600, or 24 by 24 inches
double LowGoalHeight = 543.56*0.23333333333333333333333333333333333333333; // 21.4 inches
double HeighGoalX = 3050*0.23333333333333333333333333333333333333333;
double HeightGoalY = 3050*0.23333333333333333333333333333333333333333;
double XDistoGoal, YDistoGoal, VectorDistoGoal,AngleToGoal,DisAngleGoal,VelocityToGoal; //All Varibles to support Shoot Setup Modular
double ShootAngleFault = 300;
int zAnimation = 15;
int BackzAnimation = 30;

//PID Settings and Variables
bool enablePID = true;
bool resetEncoders = false;

float kP = 0.0225;   //0.5 might be better // or 0.25
float kI = 0.00125; //0.00025 might be better // or 0.00125
float kD = 0.005; //0.005 might be better //or 0.0025
float turnkP = 0.125; // 0.1 is really nice, at least for only P values and no intertial 
                  //0.5 or 0.6 seems to work for only P values with intertial but you need to add +1 to your angle
                  //2 also work for intertial for turning
float turnkI = 0.0005; 
float turnkD = 0.00005; //might be better to have this low so that it does zig zag when driving straight (worth testing though)

float desiredValue = 0;
int desiredTurnValue = 0;

int error; //Desired Value - Sensor Value: Position
int prevError = 0; //Position 20ms ago
int derivative; // error - prevError : Speed
int totalError = 0; // totalError += error : Integral 

int turnError; //Desired Value - Sensor Value: Position
int turnPrevError = 0; //Position 20ms ago
int turnDerivative; // error - prevError : Speed
int turnTotalError = 0; // totalError += error : Integral 

int maxTurnIntegral = 20; // These cap the integrals
int maxIntegral = 3000;
int integralBound = 3; //If error is outside the bounds, then apply the integral. This is a buffer with +-integralBound degrees
float TurnSpeed = 1;
float LaderalSpeed = 1;
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
  Expand.close();
  heading.calibrate();
  inertialSensor.calibrate();
  ShootMotors.setStopping(coast);
  Yrotation.resetPosition();
  Xrotation.resetPosition();
  wait(2,seconds); 
  heading.resetRotation();
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
  thread sPID = thread(PID);
  // AutoSkills(); // choose one when ready
  AutoComp();
}
  void AutoSkills(){
  IntakeMotors.setVelocity(10,pct);
  LaderalSpeed = 0.1;
  desiredValue = -10;
  wait(2,sec);
  IntakeMotors.spinFor(forward,180,degrees);
  wait(1,sec);
  LaderalSpeed = 1; 
  desiredValue = 5;
  wait(2,sec);
  IntakeMotors.spinFor(reverse,0.5,sec);
  desiredTurnValue = 270;
  wait(4,sec);
  //
  IntakeMotors.setVelocity(70,pct);
  ShootMotors.setVelocity(75,pct);
  ShootMotors.spin(forward);
  wait(1.5,sec);
  IntakeMotors.spin(forward);
  wait(2,sec);
  ShootMotors.stop();
  desiredValue += 40;
  wait(1,sec);
  desiredTurnValue -= 135;
  wait(4,sec);
  desiredValue -= 75;
  wait(6,sec);
  desiredTurnValue -= 90;
  IntakeMotors.stop();
  IntakeMotors.spinFor(reverse,0.3,sec);
  //
  ShootMotors.setVelocity(85,pct);
  ShootMotors.spin(forward);
  wait(1.5,sec);
  IntakeMotors.spin(forward);
  wait(2,sec);
  ShootMotors.stop();
  desiredTurnValue += 90;
  wait(5,sec);
  desiredValue -= 65;
  wait(8,sec);
  desiredTurnValue += 45;
  IntakeMotors.stop();
  IntakeMotors.setVelocity(10,pct);
  wait(0.1,sec);
  IntakeMotors.spinFor(reverse,0.2,sec);
  wait(5,sec);
  //Shoot
  ShootMotors.setVelocity(75,pct);
  ShootMotors.spin(forward);
  ShootMotors.stop();
  IntakeMotors.spin(forward);
  wait(5,sec);
  ShootMotors.stop();
  desiredValue -= 40;
  IntakeMotors.stop();
  wait(5,sec);
  desiredTurnValue -= 90;
  LaderalSpeed = 0.1;
  desiredValue -= 50;
  wait(2,sec);
  IntakeMotors.spinFor(forward,180,degrees);
  wait(3,sec);
  desiredValue += 40;
  wait(3,sec);
  // desiredTurnValue += 90;
  // wait(5,sec);
  // desiredValue -= 75;
  // wait(5,sec);
  // desiredValue += 50;
  // wait(5,sec);
  // desiredTurnValue += 135;
  // wait(5,sec);
  // desiredValue -= 175;
  // wait(5,sec);
  // IntakeMotors.stop();
  // desiredTurnValue = 45+180;
  // IntakeMotors.spinFor(reverse,0.2,sec);
  // wait(5,sec);
  // //Shoot
  // IntakeMotors.spin(forward);
  // wait(5,sec);
  // desiredTurnValue += 270;
  // wait(5,sec);
  // desiredValue -= 180;
  // wait(5,sec);
  // IntakeMotors.stop();
  // desiredTurnValue = 270+180;
  // IntakeMotors.spinFor(reverse,0.2,sec);
  // wait(5,sec);
  // //Shoot
  // IntakeMotors.spin(forward);
  // wait(5,sec);
  // desiredValue -= 40;
  // wait(5, sec);
  // desiredValue += 40;
  desiredTurnValue = 315;
  //Expand
  // Expand.open();
  while(true){
    this_thread::sleep_for(25);
  }
}

void AutoComp(){
  wait(8,sec);
  IntakeMotors.setVelocity(100,pct);
  IntakeMotors.spin(reverse);
  // heading.calibrate();
  // wait(2,sec);
  // wait(1,sec);
  // desiredValue += 20;
  // wait(1,sec);
  // desiredTurnValue -= 90;
  // wait(100,sec);
  // IntakeMotors.setVelocity(10,pct);
  // IntakeMotors.spin(forward);
  // LaderalSpeed = 0.3;
  // desiredValue = -10;
  // wait(3,sec);
  // LaderalSpeed = 1; 
  // desiredValue = 6;
  // wait(3,sec);
  // IntakeMotors.spinFor(reverse,0.5,sec);
  // desiredTurnValue -= 10;
  // wait(4,sec);
  // IntakeMotors.setVelocity(70,pct);
  // ShootMotors.setVelocity(75,pct);
  // ShootMotors.spin(forward);
  // wait(1.5,sec);
  // IntakeMotors.spin(forward);
  // wait(2,sec);
  // ShootMotors.stop();
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

void Controller(){
enablePID = false;
  LeftDriveSmart.setVelocity(0,percent);
  RightDriveSmart.setVelocity(0,percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  ShootMotors.setVelocity(60,percent);

  while (true){
    if (Controller1.Axis4.position() > 10 || Controller1.Axis4.position() < -10){
      LeftDriveSmart.setVelocity(((Controller1.Axis3.position())+Controller1.Axis4.position()*-1)*Turncap,percent);
      RightDriveSmart.setVelocity(((Controller1.Axis3.position())-Controller1.Axis4.position()*-1)*Turncap,percent);
    } else{
      LeftDriveSmart.setVelocity(Controller1.Axis3.position()*Speedcap,percent);
      RightDriveSmart.setVelocity(Controller1.Axis3.position()*Speedcap,percent);
    }   
    if (Controller1.ButtonL2.pressing()) {
    IntakeMotors.setVelocity(70,percent);
    IntakeMotors.spin(forward);
    } else if (Controller1.ButtonL1.pressing()) {
      IntakeMotors.setVelocity(70,percent);
      IntakeMotors.spin(reverse);
    } else {
      IntakeMotors.stop();
    }
    if(Controller1.ButtonR1.pressing()){
      //Shootsetup(); haven't finished
      LeftDriveSmart.stop();
      RightDriveSmart.stop();
    while (Controller1.ButtonR1.pressing()){
      ShootMode();
    }
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
    }
    if (Controller1.ButtonR2.pressing() && Controller1.ButtonA.pressing()) {
      Expand.open();
    }
    if (Controller1.ButtonUp.pressing()){
      Speedcap = 1;
      Turncap = 1;
    } else {
      Speedcap = 0.7;
      Turncap = 0.7;
    }
    ShootMotors.stop();
    this_thread::sleep_for(25);
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
  } else {
    IntakeMotors.stop();
  }
  if (Controller1.ButtonLeft.pressing()){
    LeftDriveSmart.setVelocity(10,percent);
    RightDriveSmart.setVelocity(-10,percent);
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
  } else if (Controller1.ButtonRight.pressing()){
    LeftDriveSmart.setVelocity(-10,percent);
    RightDriveSmart.setVelocity(10,percent);
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
  } else if (Controller1.ButtonUp.pressing()){
    LeftDriveSmart.setVelocity(10,percent);
    RightDriveSmart.setVelocity(10,percent);
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
  } else if (Controller1.ButtonDown.pressing()){
    LeftDriveSmart.setVelocity(-10,percent);
    RightDriveSmart.setVelocity(-10,percent);
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
  } else {
    LeftDriveSmart.setVelocity(0,percent);
    RightDriveSmart.setVelocity(0,percent);
    LeftDriveSmart.stop();
    RightDriveSmart.stop();
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
  this_thread::sleep_for(25);
}
int PID(){
  while (enablePID) {
    float calculatedDesiredValue = desiredValue*(dpr/10);
    // In cm now

    // Get motor positions

    int averageMotorPosition = (Yrotation.position(deg) - Xrotation.position(deg))/2;

    ///////////////////////////////////
    // Lateral Movement PID
    ///////////////////////////////////

    // Potential 
    error = calculatedDesiredValue - averageMotorPosition; //may need to flip
    // pidError =  pidRequestedValue - pidSensorCurrentValue;

    // Derivative 
    derivative =  error - prevError; //may need to flip

    // Velocity -> Position -> Absement // Integral
    // Integral
    if(abs(error) < integralBound){
    totalError+=error; 
    }  else {
      totalError = 0; 
    }
    //totalError += error;

    //This would cap the integral
    totalError = abs(totalError) > maxIntegral ? -1*(totalError) * maxIntegral : totalError;

    // Calculate motor power
    double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI))*LaderalSpeed; 
    //   pidDrive = (pid_Kp * pidError);

    // limit drive
    if( lateralMotorPower > 60 )
        lateralMotorPower = 60;
    if( lateralMotorPower < -60)
        lateralMotorPower = -60;
    ///////////////////////////////////
    // Turning Movement PID
    ///////////////////////////////////
    // Get average motor positions
    // double turnDifference = frontLeftMotorPosition - backRightMotorPosition;
        
    // Potential 
    // turnError = desiredTurnValue - turnDifference;
    turnError = desiredTurnValue - heading.rotation();
    // pidError =  pidRequestedValue - pidSensorCurrentValue;

    // Derivative 
    turnDerivative = turnError - turnPrevError;

    // Velocity -> Position -> Absement // Integral
    //Integral
    if(abs(turnError) < integralBound){
    turnTotalError+=error; 
    }  else {
      turnTotalError = 0; 
    }
    //totalError += error;

    //This would cap the integral
    turnTotalError = abs(turnTotalError) > maxTurnIntegral ? -1*(turnTotalError) * maxTurnIntegral : turnTotalError;

    // Calculate motor power
    double turnMotorPower = ((turnError * turnkP) + (turnDerivative * turnkD) + (turnTotalError * turnkI)) * TurnSpeed;

    // limit drive
    if( turnMotorPower > 60 )
        turnMotorPower = 60;
    if( turnMotorPower < -60 )
        turnMotorPower = -60;

    leftDriveMotorA.spin(forward, lateralMotorPower - turnMotorPower, velocityUnits::pct); // could use voltage
    leftDriveMotorB.spin(forward, lateralMotorPower - turnMotorPower, velocityUnits::pct); // could use voltage
    rightDriveMotorA.spin(forward, lateralMotorPower + turnMotorPower, velocityUnits::pct); // could use voltage
    rightDriveMotorB.spin(forward, lateralMotorPower + turnMotorPower, velocityUnits::pct); // could use voltage

    prevError = error;
    turnPrevError = turnError;

    // printf("\n Turn Error %d", turnError);
    // printf("\n Drive Error %d", error);
    // printf("\n Calculated Desired Value %f", calculatedDesiredValue);
    // printf("\n Average Motor Position %d", averageMotorPosition);
    // printf("\n Ypos, %f, Xpos, %f", Yrotation.position(deg), Xrotation.position(deg));
    // printf("\n Inertial Sensor %f", heading.rotation());

    // Don't hog cpu
    this_thread::sleep_for(20);
  }
  while(true){
    this_thread::sleep_for(100000000);
  }
  return 0;
}
//Don't look down here there isn't anything down here but suffering :)
//and Cody's dumb methods XD
//We're on strike ;p