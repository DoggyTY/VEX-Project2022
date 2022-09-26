#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDriveMotorA = motor(PORT1, ratio18_1, false);
motor LeftDriveMotorB = motor(PORT3, ratio18_1, false);
motor RightDriveMotorA = motor(PORT8, ratio18_1, false);
motor RightDriveMotorB = motor(PORT10, ratio18_1, false);
motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB);
motor LeftDriveMotorC = motor(PORT2, ratio18_1, false);
motor RightDriveMotorC = motor(PORT9, ratio18_1, false);

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