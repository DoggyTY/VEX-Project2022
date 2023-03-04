#include "vex_imu.h"
#include "vex_motorgroup.h"
#include "vex_rotation.h"
#include "vex_triport.h"
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group ShootMotors;
extern drivetrain Drivetrain;
extern motor_group IntakeMotors;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern pneumatics Expand;
extern rotation Xrotation;
extern rotation Yrotation;
extern inertial heading;
extern motor leftDriveMotorA;
extern motor leftDriveMotorB;
extern motor rightDriveMotorA;
extern motor rightDriveMotorB;
extern inertial inertialSensor;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );