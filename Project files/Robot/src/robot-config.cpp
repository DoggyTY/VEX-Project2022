#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDriveMotorA = motor(PORT9, ratio18_1, true);
motor LeftDriveMotorB = motor(PORT10, ratio18_1, false);
motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB);
motor RightDriveMotorA = motor(PORT1, ratio18_1, true);
motor RightDriveMotorB = motor(PORT2, ratio18_1, false);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB);
motor leftMotorA = motor(PORT21, ratio18_1, false);
motor leftMotorB = motor(PORT20, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT19, ratio18_1, true);
motor rightMotorB = motor(PORT18, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
motor RollMotor = motor(PORT3, ratio18_1, false);
motor IntakeMotor = motor(PORT4, ratio18_1, false);
motor ShootMotorsMotorA = motor(PORT5, ratio6_1, false);
motor ShootMotorsMotorB = motor(PORT6, ratio6_1, false);
motor_group ShootMotors = motor_group(ShootMotorsMotorA, ShootMotorsMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}