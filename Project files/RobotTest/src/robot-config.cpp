#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDriveMotorA = motor(PORT1, ratio18_1, true);
motor LeftDriveMotorB = motor(PORT3, ratio18_1, true);
motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB);
motor RightDriveMotorA = motor(PORT8, ratio18_1, true);
motor RightDriveMotorB = motor(PORT10, ratio18_1, true);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB);

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