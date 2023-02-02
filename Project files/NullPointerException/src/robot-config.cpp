#include "vex.h"
#include "vex_global.h"
#include "vex_rotation.h"
#include "vex_triport.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors, DO NOT CONNECT ANYTHING TO PORT 17
controller Controller1 = controller(primary);
motor ShootMotorsMotorA = motor(PORT7, ratio6_1, false);
motor ShootMotorsMotorB = motor(PORT8, ratio6_1, false);
motor_group ShootMotors = motor_group(ShootMotorsMotorA, ShootMotorsMotorB);
motor leftDriveMotorA = motor(PORT9, ratio18_1, false);
motor leftDriveMotorB = motor(PORT10, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftDriveMotorA, leftDriveMotorB);
motor rightDriveMotorA = motor(PORT20, ratio18_1, true);
motor rightDriveMotorB = motor(PORT19, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightDriveMotorA, rightDriveMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
motor IntakeMotorsMotorA = motor(PORT16, ratio18_1, false);
motor IntakeMotorsMotorB = motor(PORT18, ratio18_1, false);
motor_group IntakeMotors = motor_group(IntakeMotorsMotorA, IntakeMotorsMotorB);
digital_out Expand = digital_out(Brain.ThreeWirePort.A);
rotation Xrotation = rotation(PORT5);
rotation Yrotation = rotation(PORT6);
inertial heading = inertial(PORT4);
inertial inertialSensor = inertial(PORT3);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize except happiness
}