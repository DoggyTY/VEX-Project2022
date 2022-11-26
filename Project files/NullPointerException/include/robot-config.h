#include "vex_motorgroup.h"
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group ShootMotors;
extern drivetrain Drivetrain;
extern motor_group IntakeMotors;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );