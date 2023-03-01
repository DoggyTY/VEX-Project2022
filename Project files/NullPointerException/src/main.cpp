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
#include "vex_brain.h"
#include "vex_drivetrain.h"
#include "vex_global.h"
#include "vex_task.h"
#include "vex_thread.h"
#include "vex_timer.h"
#include "vex_units.h"
#include <cmath>

using namespace vex;
void Controller();
void AutoSkills();
void intakeup();
void intakedown();
void ShootMode();
int PTU();
bool Shootsetup();
void ScreenAnime();
int PID();
void gotoPTD(int x, int y);
float Speedcap = 0.8;
float Turncap = 0.8;
int Shootvelo = 80;
bool IntakeOn = false;
char complaint[] = "nathan blames us for everything smh my head"; 
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

float kP = 0.32;   //0.5 might be better // or 0.25
float kI = 0.000025; //0.00025 might be better // or 0.00125
float kD = 0.00005; //0.005 might be better //or 0.0025
float turnkP = 1; // 0.1 is really nice, at least for only P values and no intertial 
                  //0.5 or 0.6 seems to work for only P values with intertial but you need to add +1 to your angle
                  //2 also work for intertial for turning
float turnkI = 0.0; 
float turnkD = 0.0; //might be better to have this low so that it does zig zag when driving straight (worth testing though)

float desiredValue = 0;
int desiredTurnValue = 180;

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

// The table of numbers below is not relevent to the competition
float Raidan = 0.0f;
int Entry = 0;
int FocalLength = 30;
double ProjectedXY[368][2]; // Need amount of verties
int XYZ[368][3] = { // this was a pain to write out, took me like 2 hours
// First 8 Top
{50,20,zAnimation},{70,20,zAnimation},
{45,25,zAnimation},{85,25,zAnimation},
{35,35,zAnimation},{95,35,zAnimation},
{20,50,zAnimation},{100,50,zAnimation},
{20,90,zAnimation},{100,90,zAnimation},
{35,105,zAnimation},{95,105,zAnimation},
{45,115,zAnimation},{85,115,zAnimation},
{50,120,zAnimation},{70,120,zAnimation}, // 15
// First 8 Middle Top
{60,30,zAnimation},{60,30,zAnimation},
{55,35,zAnimation},{75,35,zAnimation},
{45,45,zAnimation},{85,45,zAnimation},
{30,60,zAnimation},{90,60,zAnimation},
{30,80,zAnimation},{90,80,zAnimation},
{45,95,zAnimation},{85,95,zAnimation},
{55,105,zAnimation},{75,105,zAnimation},
{60,110,zAnimation},{60,110,zAnimation}, // 31
// First 8 Bottom
{45,125,zAnimation},{85,125,zAnimation},
{35,135,zAnimation},{95,135,zAnimation},
{20,150,zAnimation},{100,150,zAnimation},
{20,190,zAnimation},{100,190,zAnimation},
{35,205,zAnimation},{95,205,zAnimation},
{45,215,zAnimation},{85,215,zAnimation},
{50,220,zAnimation},{70,220,zAnimation}, //45
// First 8 Middle Bottom
{60,130,zAnimation},{60,130,zAnimation},
{55,135,zAnimation},{75,135,zAnimation},
{45,145,zAnimation},{85,145,zAnimation},
{30,160,zAnimation},{90,160,zAnimation},
{30,180,zAnimation},{90,180,zAnimation},
{45,195,zAnimation},{85,195,zAnimation},
{55,205,zAnimation},{75,205,zAnimation},
{60,210,zAnimation},{60,210,zAnimation}, // 61
// Second 8 Top
{160,20,zAnimation},{180,20,zAnimation},
{155,25,zAnimation},{195,25,zAnimation},
{145,35,zAnimation},{205,35,zAnimation},
{130,50,zAnimation},{210,50,zAnimation},
{130,90,zAnimation},{210,90,zAnimation},
{145,105,zAnimation},{205,105,zAnimation},
{155,115,zAnimation},{195,115,zAnimation},
{160,120,zAnimation},{180,120,zAnimation}, // 77
// Second 8 Middle Top
{170,30,zAnimation},{170,30,zAnimation},
{165,35,zAnimation},{185,35,zAnimation},
{155,45,zAnimation},{195,45,zAnimation},
{140,60,zAnimation},{200,60,zAnimation},
{140,80,zAnimation},{200,80,zAnimation},
{155,95,zAnimation},{195,95,zAnimation},
{165,105,zAnimation},{185,105,zAnimation},
{170,110,zAnimation},{170,110,zAnimation}, // 93
// Second 8 Bottom
{155,125,zAnimation},{195,125,zAnimation},
{145,135,zAnimation},{205,135,zAnimation},
{130,150,zAnimation},{210,150,zAnimation},
{130,190,zAnimation},{210,190,zAnimation},
{145,205,zAnimation},{205,205,zAnimation},
{155,215,zAnimation},{195,215,zAnimation},
{160,220,zAnimation},{180,220,zAnimation}, // 107
// Second 8 Middle Bottom
{170,130,zAnimation},{170,130,zAnimation},
{165,135,zAnimation},{185,135,zAnimation},
{155,145,zAnimation},{195,145,zAnimation},
{140,160,zAnimation},{200,160,zAnimation},
{140,180,zAnimation},{200,180,zAnimation},
{155,195,zAnimation},{195,195,zAnimation},
{165,205,zAnimation},{185,205,zAnimation},
{170,210,zAnimation},{170,210,zAnimation}, // 123_
// 6 Top
{320,20,zAnimation},{315,20,zAnimation},
{310,25,zAnimation},{300,35,zAnimation},
{290,45,zAnimation},{280,65,zAnimation},
{270,85,zAnimation},{260, 110, zAnimation}, // 131
// {255, 135,zAnimation} - connects to
// 6 Bottom
{270,120,zAnimation},{290,120,zAnimation},
{265,125,zAnimation},{305,125,zAnimation},
{255,135,zAnimation},{315,135,zAnimation},
{240,150,zAnimation},{320,150,zAnimation},
{240,190,zAnimation},{320,190,zAnimation},
{255,205,zAnimation},{315,205,zAnimation},
{265,215,zAnimation},{305,215,zAnimation},
{270,220,zAnimation},{290,220,zAnimation}, //147
// 6 Middle Bottom
{170,130,zAnimation},{170,130,zAnimation},
{165,135,zAnimation},{185,135,zAnimation},
{155,145,zAnimation},{195,145,zAnimation},
{140,160,zAnimation},{200,160,zAnimation},
{140,180,zAnimation},{200,180,zAnimation},
{155,195,zAnimation},{195,195,zAnimation},
{165,205,zAnimation},{185,205,zAnimation},
{170,210,zAnimation},{170,210,zAnimation}, //163
// 1, like the simplist one
{330,20,zAnimation},{360,20,zAnimation},
{330,220,zAnimation},{360,220,zAnimation}, // 167
// J
{405,20,zAnimation},{460,20,zAnimation},
{460,50,zAnimation},{455,100,zAnimation},
{445,140,zAnimation},{415,200,zAnimation},
{395,220,zAnimation},{370,220,zAnimation}, // 175
{405,40,zAnimation},{440,20,zAnimation},
{440,50,zAnimation},{435,100,zAnimation},
{425,140,zAnimation},{395,200,zAnimation},
{375,205,zAnimation},{370,200,zAnimation}, // 183

/*
/// BACK OF LETTERS ///
*/

// First 8 Top
{50,20,BackzAnimation},{70,20,BackzAnimation},
{45,25,BackzAnimation},{85,25,BackzAnimation},
{35,35,BackzAnimation},{95,35,BackzAnimation},
{20,50,BackzAnimation},{100,50,BackzAnimation},
{20,90,BackzAnimation},{100,90,BackzAnimation},
{35,105,BackzAnimation},{95,105,BackzAnimation},
{45,115,BackzAnimation},{85,115,BackzAnimation},
{50,120,BackzAnimation},{70,120,BackzAnimation},
// First 8 Middle Top
{60,30,BackzAnimation},{60,30,BackzAnimation},
{55,35,BackzAnimation},{75,35,BackzAnimation},
{45,45,BackzAnimation},{85,45,BackzAnimation},
{30,60,BackzAnimation},{90,60,BackzAnimation},
{30,80,BackzAnimation},{90,80,BackzAnimation},
{45,95,BackzAnimation},{85,95,BackzAnimation},
{55,105,BackzAnimation},{75,105,BackzAnimation},
{60,110,BackzAnimation},{60,110,BackzAnimation},
// First 8 Bottom
{45,125,BackzAnimation},{85,125,BackzAnimation},
{35,135,BackzAnimation},{95,135,BackzAnimation},
{20,150,BackzAnimation},{100,150,BackzAnimation},
{20,190,BackzAnimation},{100,190,BackzAnimation},
{35,205,BackzAnimation},{95,205,BackzAnimation},
{45,215,BackzAnimation},{85,215,BackzAnimation},
{50,220,BackzAnimation},{70,220,BackzAnimation},
// First 8 Middle Bottom
{60,130,BackzAnimation},{60,130,BackzAnimation},
{55,135,BackzAnimation},{75,135,BackzAnimation},
{45,145,BackzAnimation},{85,145,BackzAnimation},
{30,160,BackzAnimation},{90,160,BackzAnimation},
{30,180,BackzAnimation},{90,180,BackzAnimation},
{45,195,BackzAnimation},{85,195,BackzAnimation},
{55,205,BackzAnimation},{75,205,BackzAnimation},
{60,210,BackzAnimation},{60,210,BackzAnimation},
// Second 8 Top
{160,20,BackzAnimation},{180,20,BackzAnimation},
{155,25,BackzAnimation},{195,25,BackzAnimation},
{145,35,BackzAnimation},{205,35,BackzAnimation},
{130,50,BackzAnimation},{210,50,BackzAnimation},
{130,90,BackzAnimation},{210,90,BackzAnimation},
{145,105,BackzAnimation},{205,105,BackzAnimation},
{155,115,BackzAnimation},{195,115,BackzAnimation},
{160,120,BackzAnimation},{180,120,BackzAnimation},
// Second 8 Middle Top
{170,30,BackzAnimation},{170,30,BackzAnimation},
{165,35,BackzAnimation},{185,35,BackzAnimation},
{155,45,BackzAnimation},{195,45,BackzAnimation},
{140,60,BackzAnimation},{200,60,BackzAnimation},
{140,80,BackzAnimation},{200,80,BackzAnimation},
{155,95,BackzAnimation},{195,95,BackzAnimation},
{165,105,BackzAnimation},{185,105,BackzAnimation},
{170,110,BackzAnimation},{170,110,BackzAnimation},
// Second 8 Bottom
{155,125,BackzAnimation},{195,125,BackzAnimation},
{145,135,BackzAnimation},{205,135,BackzAnimation},
{130,150,BackzAnimation},{210,150,BackzAnimation},
{130,190,BackzAnimation},{210,190,BackzAnimation},
{145,205,BackzAnimation},{205,205,BackzAnimation},
{155,215,BackzAnimation},{195,215,BackzAnimation},
{160,220,BackzAnimation},{180,220,BackzAnimation},
// Second 8 Middle Bottom
{170,130,BackzAnimation},{170,130,BackzAnimation},
{165,135,BackzAnimation},{185,135,BackzAnimation},
{155,145,BackzAnimation},{195,145,BackzAnimation},
{140,160,BackzAnimation},{200,160,BackzAnimation},
{140,180,BackzAnimation},{200,180,BackzAnimation},
{155,195,BackzAnimation},{195,195,BackzAnimation},
{165,205,BackzAnimation},{185,205,BackzAnimation},
{170,210,BackzAnimation},{170,210,BackzAnimation},
// 6 Top
{320,20,BackzAnimation}, {315,20,BackzAnimation},
{310,25,BackzAnimation}, {300,35,BackzAnimation},
{290,45,BackzAnimation}, {280,65,BackzAnimation},
{270,85,BackzAnimation}, {260, 110, BackzAnimation},
// {255, 135,zAnimation} - connects to
// 6 Bottom
{270,120,BackzAnimation},{290,120,BackzAnimation},
{265,125,BackzAnimation},{305,125,BackzAnimation},
{255,135,BackzAnimation},{315,135,BackzAnimation},
{240,150,BackzAnimation},{320,150,BackzAnimation},
{240,190,BackzAnimation},{320,190,BackzAnimation},
{255,205,BackzAnimation},{315,205,BackzAnimation},
{265,215,BackzAnimation},{305,215,BackzAnimation},
{270,220,BackzAnimation},{290,220,BackzAnimation},
// 6 Middle Bottom
{170,130,BackzAnimation},{170,130,BackzAnimation},
{165,135,BackzAnimation},{185,135,BackzAnimation},
{155,145,BackzAnimation},{195,145,BackzAnimation},
{140,160,BackzAnimation},{200,160,BackzAnimation},
{140,180,BackzAnimation},{200,180,BackzAnimation},
{155,195,BackzAnimation},{195,195,BackzAnimation},
{165,205,BackzAnimation},{185,205,BackzAnimation},
{170,210,BackzAnimation},{170,210,BackzAnimation},
// 1, like the simplist one
{330,20,BackzAnimation},{360,20,BackzAnimation},
{330,220,BackzAnimation},{360,220,BackzAnimation},
// J
{405,20,BackzAnimation},{460,20,BackzAnimation},
{460,50,BackzAnimation},{455,100,BackzAnimation},
{445,140,BackzAnimation},{415,200,BackzAnimation},
{395,220,BackzAnimation}, {370,220,BackzAnimation},
{405,40,BackzAnimation},{440,20,BackzAnimation},
{440,50,BackzAnimation},{435,100,BackzAnimation},
{425,140,BackzAnimation},{395,200,BackzAnimation},
{375,205,BackzAnimation}, {370,200,BackzAnimation}
};
int Connections[664][2] = { // 0 -> 367, but this ones worse... than the one above
//First 8 top
{0,1},{0,2},{0,16},
{1,3},{1,17},
{2,4},{2,18},
{3,5},{3,19},
{4,6},{4,20},
{5,7},{5,21},
{6,8},{6,22},
{7,9},{7,23},
{8,10},{8,24},
{9,11},{9,25},
{10,12},{10,26},
{11,13},{11,27},
{12,14},{12,28},
{13,15},{13,29},
{14,15},{14,30}, {14,32}, {14,46},
//First 8 Bottom
{15,33},{15,47},
{32,34},{32,48},
{33,35},{33,49},
{34,36},{34,50},
{35,37,},{35,51},
{36,38,},{36,52},
{37,39},{37,53},
{38,40},{38,54},
{39,41},{39,55},
{40,42},{40,56},
{41,43},{41,57},
{42,44},{42,58},
{43,45},{43,59},
{44,46},{44,60},
{45,46},{45,61},
{46,59},
//First 8 Middle Top
{15,16}, {15,17},
{16,18},
{17,19},
{18,20},
{19,21},
{20,22},
{21,23},
{22,24},
{23,25},
{24,26},
{25,27},
{26,28},
{27,29},
{28,30},
{29,31},
{30,31},
// First 8 Middle Bottom
{46,47}, {46,48},
{47,49},
{48,50},
{49,51},
{50,52},
{51,53},
{52,54},
{53,55},
{54,56},
{55,57},
{56,58},
{57,59},
{58,60},
{59,61},
{60,61},
// Second 8 top
{62,63}, {62,64}, {62,78},
{63,65},{63,79},
{64,66},{64,80},
{65,67},{65,81},
{66,68},{66,82},
{67,69},{67,83},
{68,70},{68,84},
{69,71},{69,85},
{70,72},{70,86},
{71,73},{71,87},
{72,74},{72,88},
{73,75},{73,89},
{74,76},{74,90},
{75,77},{75,91},
{76,77},{76,92},
{77,93},
// Second 8 Bottom
{62+32,63+32},{62+32,64+32},{62+32,78+32},
{63+32,65+32},{63+32,79+32},
{64+32,66+32},{64+32,80+32},
{65+32,67+32},{65+32,81+32},
{66+32,68+32},{66+32,82+32},
{67+32,69+32},{67+32,83+32},
{68+32,70+32},{68+32,84+32},
{69+32,71+32},{69+32,85+32},
{70+32,72+32},{70+32,86+32},
{71+32,73+32},{71+32,87+32},
{72+32,74+32},{72+32,88+32},
{73+32,75+32},{73+32,89+32},
{74+32,76+32},{74+32,90+32},
{75+32,77+32},{75+32,91+32},
{76+32,77+32},{76+32,92+32},
{77+32,93+32},
//Second 8 Middle Top
{46+32,47+32}, {46+32,48+32},
{47+32,49+32},
{48+32,50+32},
{49+32,51+32},
{50+32,52+32},
{51+32,53+32},
{52+32,54+32},
{53+32,55+32},
{54+32,56+32},
{55+32,57+32},
{56+32,58+32},
{57+32,59+32},
{58+32,60+32},
{59+32,61+32},
{60+32,61+32},
//Second 8 Middle Bottom
{46+62,47+62}, {46+62,48+62},
{47+62,49+62},
{48+62,50+62},
{49+62,51+62},
{50+62,52+62},
{51+62,53+62},
{52+62,54+62},
{53+62,55+62},
{54+62,56+62},
{55+62,57+62},
{56+62,58+62},
{57+62,59+62},
{58+62,60+62},
{59+62,61+62},
{60+62,61+62},
// 6 top
{124,125},
{125,126},
{126,127},
{128, 129},
{129,130},
{130,131},
{131,136},
// 6 Bottom
{46+86,47+86}, {46+86,48+86},
{47+86,49+86},
{48+86,50+86},
{49+86,51+86},
{50+86,52+86},
{51+86,53+86},
{52+86,54+86},
{53+86,55+86},
{54+86,56+86},
{55+86,57+86},
{56+86,58+86},
{57+86,59+86},
{58+86,60+86},
{59+86,61+86},
{60+86,61+86},
// 1
{164,165},
{167,166},
{166,164},
{167,165},
// J
{168,169}, {168,176},
{169,170}, {169,177},
{170,171}, {170,178},
{171,172}, {171,179},
{172,173}, {172,180},
{173,174}, {173,181},
{174,175}, {174,182},
{175,183},
{176,177},
{178,179},
{180,181},
{181,182},
{182,183},
/*
/// BACK CONNECTIONS
*/
{0+184,1+184},{0+184,2+184},{0+184,16+184},
{1+184,3+184},{1+184,17+184},
{2+184,4+184},{2+184,18+184},
{3+184,5+184},{3+184,19+184},
{4+184,6+184},{4+184,20+184},
{5+184,7+184},{5+184,21+184},
{6+184,8+184},{6+184,22+184},
{7+184,9+184},{7+184,23+184},
{8+184,10+184},{8+184,24+184},
{9+184,11+184},{9+184,25+184},
{10+184,12+184},{10+184,26+184},
{11+184,13+184},{11+184,27+184},
{12+184,14+184},{12+184,28+184},
{13+184,15+184},{13+184,29+184},
{14+184,15+184},{14+184,30+184}, {14+184,32+184}, {14+184,46+184},
//First 8 Bottom
{15+184,33+184},{15+184,47+184},
{32+184,34+184},{32+184,48+184},
{33+184,35+184},{33+184,49+184},
{34+184,36+184},{34+184,50+184},
{35+184,37+184,},{35+184,51+184},
{36+184,38+184,},{36+184,52+184},
{37+184,39+184},{37+184,53+184},
{38+184,40+184},{38+184,54+184},
{39+184,41+184},{39+184,55+184},
{40+184,42+184},{40+184,56+184},
{41+184,43+184},{41+184,57+184},
{42+184,44+184},{42+184,58+184},
{43+184,45+184},{43+184,59+184},
{44+184,46+184},{44+184,60+184},
{45+184,46+184},{45+184,61+184},
{46+184,59+184},
//First 8 Middle Top
{15+184,16+184}, {15+184,17+184},
{16+184,18+184},
{17+184,19+184},
{18+184,20+184},
{19+184,21+184},
{20+184,22+184},
{21+184,23+184},
{22+184,24+184},
{23+184,25+184},
{24+184,26+184},
{25+184,27+184},
{26+184,28+184},
{27+184,29+184},
{28+184,30+184},
{29+184,31+184},
{30+184,31+184},
// First 8 Middle Bottom
{46+184,47+184}, {46+184,48+184},
{47+184,49+184},
{48+184,50+184},
{49+184,51+184},
{50+184,52+184},
{51+184,53+184},
{52+184,54+184},
{53+184,55+184},
{54+184,56+184},
{55+184,57+184},
{56+184,58+184},
{57+184,59+184},
{58+184,60+184},
{59+184,61+184},
{60+184,61+184},
// Second 8 top
{62+184,63+184},{62+184,64+184},{62+184,78+184},
{63+184,65+184},{63+184,79+184},
{64+184,66+184},{64+184,80+184},
{65+184,67+184},{65+184,81+184},
{66+184,68+184},{66+184,82+184},
{67+184,69+184},{67+184,83+184},
{68+184,70+184},{68+184,84+184},
{69+184,71+184},{69+184,85+184},
{70+184,72+184},{70+184,86+184},
{71+184,73+184},{71+184,87+184},
{72+184,74+184},{72+184,88+184},
{73+184,75+184},{73+184,89+184},
{74+184,76+184},{74+184,90+184},
{75+184,77+184},{75+184,91+184},
{76+184,77+184},{76+184,92+184},
{77+184,93+184},
// Second 8 Bottom
{62+32+184,63+32+184},{62+32+184,64+32+184},{62+32+184,78+32+184},
{63+32+184,65+32+184},{63+32+184,79+32+184},
{64+32+184,66+32+184},{64+32+184,80+32+184},
{65+32+184,67+32+184},{65+32+184,81+32+184},
{66+32+184,68+32+184},{66+32+184,82+32+184},
{67+32+184,69+32+184},{67+32+184,83+32+184},
{68+32+184,70+32+184},{68+32+184,84+32+184},
{69+32+184,71+32+184},{69+32+184,85+32+184},
{70+32+184,72+32+184},{70+32+184,86+32+184},
{71+32+184,73+32+184},{71+32+184,87+32+184},
{72+32+184,74+32+184},{72+32+184,88+32+184},
{73+32+184,75+32+184},{73+32+184,89+32+184},
{74+32+184,76+32+184},{74+32+184,90+32+184},
{75+32+184,77+32+184},{75+32+184,91+32+184},
{76+32+184,77+32+184},{76+32+184,92+32+184},
{77+32+184,93+32+184},
//Second 8 Middle Top
{46+32+184,47+32+184}, {46+32+184,48+32+184},
{47+32+184,49+32+184},
{48+32+184,50+32+184},
{49+32+184,51+32+184},
{50+32+184,52+32+184},
{51+32+184,53+32+184},
{52+32+184,54+32+184},
{53+32+184,55+32+184},
{54+32+184,56+32+184},
{55+32+184,57+32+184},
{56+32+184,58+32+184},
{57+32+184,59+32+184},
{58+32+184,60+32+184},
{59+32+184,61+32+184},
{60+32+184,61+32+184},
//Second 8 Middle Bottom
{46+62+184,47+62+184}, {46+62+184,48+62+184},
{47+62+184,49+62+184},
{48+62+184,50+62+184},
{49+62+184,51+62+184},
{50+62+184,52+62+184},
{51+62+184,53+62+184},
{52+62+184,54+62+184},
{53+62+184,55+62+184},
{54+62+184,56+62+184},
{55+62+184,57+62+184},
{56+62+184,58+62+184},
{57+62+184,59+62+184},
{58+62+184,60+62+184},
{59+62+184,61+62+184},
{60+62+184,61+62+184},
// 6 top
{124+184,125+184},
{125+184,126+184},
{126+184,127+184},
{128+184,129+184},
{129+184,130+184},
{130+184,131+184},
{131+184,136+184},
// 6 Bottom
{46+86+184,47+86+184}, {46+86+184,48+86+184},
{47+86+184,49+86+184},
{48+86+184,50+86+184},
{49+86+184,51+86+184},
{50+86+184,52+86+184},
{51+86+184,53+86+184},
{52+86+184,54+86+184},
{53+86+184,55+86+184},
{54+86+184,56+86+184},
{55+86+184,57+86+184},
{56+86+184,58+86+184},
{57+86+184,59+86+184},
{58+86+184,60+86+184},
{59+86+184,61+86+184},
{60+86+184,61+86+184},
// 1
{164+184,165+184},
{167+184,166+184},
{166+184,164+184},
{167+184,165+184},
// J
{168+184,169+184}, {168+184,176+184},
{169+184,170+184}, {169+184,177+184},
{170+184,171+184}, {170+184,178+184},
{171+184,172+184}, {171+184,179+184},
{172+184,173+184}, {172+184,180+184},
{173+184,174+184}, {173+184,181+184},
{174+184,175+184}, {174+184,182+184},
{175+184,183+184},
{176+184,177+184},
{178+184,179+184},
{180+184,181+184},
{181+184,182+184},
{182+184,183+184},
//Connection from back to front
{0,184},
{1,185},
{2,186},
{3,187},
{4,188},
{5,189},
{6,190},
{7,191},
{8,192},
{9,193},
{10,194},
{11,195},
{12,196},
{13,197},
{14,198},
{15,199},
{16,200},
{17,201},
{18,202},
{19,203},
{20,204},
{21,205},
{22,206},
{23,207},
{24,208},
{25,209},
{26,210},
{27,211},
{28,212},
{29,213},
{30,214},
{31,215},
{32,216},
{33,217},
{34,218},
{35,219},
{36,220},
{37,221},
{38,222},
{39,223},
{40,224},
{41,225},
{42,226},
{43,227},
{44,228},
{45,229},
{46,230},
{47,231},
{48,232},
{49,233},
{50,234},
{51,235},
{52,236},
{53,237},
{54,238},
{55,239},
{56,240},
{57,241},
{58,242},
{59,243},
{60,244},
{61,245},
{62,246},
{63,247},
{64,248},
{65,249},
{66,250},
{67,251},
{68,252},
{69,253},
{70,254},
{71,255},
{72,256},
{73,257},
{74,258},
{75,259},
{76,260},
{77,261},
{78,262},
{79,263},
{80,264},
{81,265},
{82,266},
{83,267},
{84,268},
{85,269},
{86,270},
{87,271},
{88,272},
{89,273},
{90,274},
{91,275},
{92,276},
{93,277},
{94,278},
{95,279},
{96,280},
{97,281},
{98,282},
{99,283},
{100,284},
{101,285},
{102,286},
{103,287},
{104,288},
{105,289},
{106,290},
{107,291},
{108,292},
{109,293},
{110,294},
{111,295},
{112,296},
{113,297},
{114,298},
{115,299},
{116,300},
{117,301},
{118,302},
{119,303},
{120,304},
{121,305},
{122,306},
{123,307},
{124,308},
{125,309},
{126,310},
{127,311},
{128,312},
{129,313},
{130,314},
{131,315},
{132,316},
{133,317},
{134,318},
{135,319},
{136,320},
{137,321},
{138,322},
{139,323},
{140,324},
{141,325},
{142,326},
{143,327},
{144,328},
{145,329},
{146,330},
{147,331},
{148,332},
{149,333},
{150,334},
{151,335},
{152,336},
{153,337},
{154,338},
{155,339},
{156,340},
{157,341},
{158,342},
{159,343},
{160,344},
{161,345},
{162,346},
{163,347},
{164,348},
{165,349},
{166,350},
{167,351},
{168,352},
{169,353},
{170,354},
{171,355},
{172,356},
{173,357},
{174,358},
{175,359},
{176,360},
{177,361},
{178,362},
{179,363},
{180,364},
{181,365},
{182,366},
{183,367},
};

//If you tink that I will annotate my code I won't. have fun 

int main(){
  vexcodeInit();
  heading.calibrate();
  inertialSensor.calibrate();
  ShootMotors.setStopping(coast);
  Yrotation.resetPosition();
  Xrotation.resetPosition();
  Expand.set(false);
  wait(2,seconds); 
  heading.resetRotation();
  // //Threads
  // thread PTUupdate = thread(PTU);
  // thread sPID = thread(PID);
  // AutoSkills();
  thread control = thread(Controller);
  // thread Logo = thread(ScreenAnime);
  while(true){
    wait(25,msec);
  }
  //while(true){
  //ScreenAnime();
  //wait(1,seconds);
  //}
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
      LeftDriveSmart.setVelocity((Controller1.Axis3.position())*Speedcap,percent);
      RightDriveSmart.setVelocity((Controller1.Axis3.position())*Speedcap,percent);
    }   
    if (Controller1.ButtonL2.pressing()) {
    IntakeMotors.setVelocity(70,percent);
    IntakeMotors.spin(forward);
    } else if (Controller1.ButtonL1.pressing()) {
      IntakeMotors.setVelocity(70,percent);
      IntakeMotors.spin(reverse);
    } else if (Controller1.ButtonA.pressing()){
      IntakeMotors.spinTo(180,degrees,false);
    }
    else {
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
    if (Controller1.ButtonA.pressing() && Controller1.ButtonX.pressing() && Controller1.ButtonY.pressing() && Controller1.ButtonB.pressing()) {
      Expand.set(true);
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
bool Shootsetup() {
  Left = false;
  if (PosFault == true){
    return false;
  }
  XDistoGoal = HeighGoalX - Xaxis;
  YDistoGoal = HeightGoalY - Yaxis;
  VectorDistoGoal = sqrt(pow(XDistoGoal,2) + pow(YDistoGoal,2));
  if(XDistoGoal < 0) {
    Left = true;
  }
  XDistoGoal = std::abs(XDistoGoal);
  AngleToGoal = acos(YDistoGoal/VectorDistoGoal) * 180/3.1415;
  DisAngleGoal = Anglelooking - DisAngleGoal;
  if (Left){
    Drivetrain.turnFor(left,DisAngleGoal,degrees);
  } else{
    Drivetrain.turnFor(right,DisAngleGoal,degrees);
  }

  // Velocity setup is next but is too hard to finish now, Rain don't do it, it needs to be specific to other varibles as we talked about.

  this_thread::sleep_for(25);
  return true;
}
void ShootMode() {
  ShootMotors.setVelocity(Shootvelo,percent);
  if (Controller1.ButtonR2.pressing()) {
    ShootMotors.spin(forward);
  } else {
    ShootMotors.stop();
  }
  if (Controller1.ButtonL2.pressing()) {
    IntakeMotors.setVelocity(80,percent);
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
void gotoPTD(double x, double y){
  while(true){
  double differencex = Xaxis - x;
  double differencey = Yaxis - y;
  double diffencevector = sqrt(pow(differencex,2) + pow(differencey,2));
  double angleofblank = asin(differencey/diffencevector);
  if (differencex < 0){
    angleofblank += M_PI;
  }
  thread PIDcontrol = thread(PID);
  PIDcontrol.detach();
  Drivetrain.turnFor(angleofblank * 180/M_PI,deg);
  Drivetrain.driveFor(diffencevector/0.23333333333333333,mm);
  this_thread::sleep_for(50);
  PIDcontrol.interrupt();
  if((Xaxis < x+1 && Xaxis > x-1) && (Yaxis < y+1 && Yaxis> y-1)){
    break;
  }
  }
}

int PTU() {
  // This is all prototype code and none of it really can fuction well, all theoretical
  // Also need to rewrite some of it to make sure that its correctly formatting gps, with x and y.
  while(true){
  double timebetweengps = vex::timer::systemHighResolution() - prevoustimer;
  double LocalXrpm = Xrotation.velocity(rpm) / 60; // divide by 60 to get rps, which would be useful later... also need to convert it to a smaller number, like 0.01 millisecond because brain processes things at 1.3 trillion inputs a seconds
  double LocalYrpm = Yrotation.velocity(rpm) / 60;
  if (Rotation != heading.heading(deg)){
    continue;
  }
  Rotation = (heading.heading(deg)) * (M_PI /180);
  Xrpm = (((sin(Rotation)*LocalYrpm) + (sin(Rotation+90)*LocalXrpm))/ 1000) * timebetweengps;
  Yrpm = (((cos(Rotation)*LocalYrpm) + (cos(Rotation+90)*LocalXrpm))/ 1000) * timebetweengps;
  Xdis = Xrpm * dpr;
  Ydis = Yrpm * dpr;
  // VectorRPM = sqrt(pow(Xrpm,2) + pow(Yrpm,2));
  // VectorDis = sqrt(pow(Xdis,2) + pow(Ydis,2));
  Xaxis = Xaxis + Xdis;
  Yaxis = Yaxis + Ydis;
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(Xaxis);
  Brain.Screen.newLine();
  Brain.Screen.print(Yaxis);
  Brain.Screen.newLine();
  Brain.Screen.print(Xdis);
  Brain.Screen.newLine();
  Brain.Screen.print(Ydis);
  Brain.Screen.newLine();
  Brain.Screen.print(Rotation);
  Brain.Screen.newLine();
  Brain.Screen.print(Yrpm);
  Brain.Screen.newLine();
  Brain.Screen.print(Xrpm);
  Brain.Screen.newLine();

  if (Xaxis > FieldX or Yaxis > FieldY){
    Controller1.Screen.setCursor(2,3);
    Controller1.Screen.print("Robot Position Fault"); // Making it known to driver of PosFault, Should do this with other things but yeah
    PosFault = true;
  } else {
    Controller1.Screen.setCursor(2,3);
    Controller1.Screen.clearLine();
    PosFault = false;
  }
  prevoustimer = vex::timer::systemHighResolution();
  this_thread::sleep_for(100);
  }
  return 0;
}

int PID() {
  // float  pidSensorCurrentValue;
  // float  pidError;
  // float  pidDrive;

  while (true) {
    float calculatedDesiredValue = 360 * desiredValue/100/(0.1*M_PI);
    // In cm now

    // Get motor positions
    
    // int backRightMotorPosition = Yrotation.position(deg);

    // pidSensorCurrentValue = rotationRight.position(rotationUnits::deg);


    int averageMotorPosition = (Yrotation.position(deg) + Xrotation.position(deg))/2;

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
    double lateralMotorPower = (error * kP) + (derivative * kD) + (totalError * kI); 
    //   pidDrive = (pid_Kp * pidError);

    // limit drive
    if( lateralMotorPower > 60 )
        lateralMotorPower = 60;
    if( lateralMotorPower < (-60) )
        lateralMotorPower = (-60);

    ///////////////////////////////////
    // Turning Movement PID
    ///////////////////////////////////
    // Get average motor positions
    // double turnDifference = frontLeftMotorPosition - backRightMotorPosition;
        
    // Potential 
    // turnError = desiredTurnValue - turnDifference;
    turnError = desiredTurnValue + 180 - heading.rotation();
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
    double turnMotorPower = (turnError * turnkP) + (turnDerivative * turnkD) + (turnTotalError * turnkI); 

    // limit drive
    if( turnMotorPower > 40 )
        turnMotorPower = 40;
    if( turnMotorPower < (-40) )
        turnMotorPower = (-40);

    leftDriveMotorA.spin(forward, lateralMotorPower - turnMotorPower, velocityUnits::pct); // could use voltage
    leftDriveMotorB.spin(forward, lateralMotorPower - turnMotorPower, velocityUnits::pct); // could use voltage
    rightDriveMotorA.spin(forward, lateralMotorPower + turnMotorPower, velocityUnits::pct); // could use voltage
    rightDriveMotorB.spin(forward, lateralMotorPower + turnMotorPower, velocityUnits::pct); // could use voltage

    prevError = error;
    turnPrevError = turnError;

    printf("\n Turn Error %d", turnError);
    printf("\n Drive Error %d", error);
    printf("\n Inertial Sensor %f", heading.rotation());

    // Don't hog cpu
    this_thread::sleep_for(20);
  }

  return 0;
}

void AutoSkills(){
  wait(50,sec);
  // IntakeMotors.setVelocity(80,pct);
  // IntakeMotors.spin(forward);
  desiredValue -= 20;
  wait(3,sec);
  desiredValue += 40;
  wait(3,sec);
  // IntakeMotors.spinFor(reverse,0.5,sec);
  desiredTurnValue = 90;
  wait(3,sec);
  //Shoot
  // IntakeMotors.spin(forward);
  wait(3,sec);
  ShootMotors.stop();
  desiredTurnValue -= 135;
  wait(3,sec);
  desiredValue -= 180;
  wait(3,sec);
  desiredTurnValue += 90;
  // IntakeMotors.stop();
  // IntakeMotors.spinFor(reverse,0.2,sec);
  wait(3,sec);
  //Shoot
  // IntakeMotors.spin(forward);
  wait(3,sec);
  desiredTurnValue -= 90;
  wait(3,sec);
  desiredValue -= 180;
  wait(3,sec);
  desiredTurnValue -= 45;
  // IntakeMotors.stop();
  // IntakeMotors.spinFor(reverse,0.2,sec);
  wait(3,sec);
  //Shoot
  // IntakeMotors.spin(forward);
  wait(3,sec);
  desiredValue -= 20;
  wait(3,sec);
  desiredValue += 70;
  wait(3,sec);
  desiredTurnValue += 90;
  wait(3,sec);
  desiredValue -= 80;
  wait(3,sec);
  desiredValue += 40;
  wait(3,sec);
  desiredTurnValue -= 90;
  wait(3,sec);
  desiredValue -= 180;
  wait(3,sec);
  // IntakeMotors.stop();
  desiredTurnValue = 225;
  // IntakeMotors.spinFor(reverse,0.2,sec);
  wait(3,sec);
  //Shoot
  // IntakeMotors.spin(forward);
  wait(3,sec);
  desiredTurnValue += 270;
  wait(3,sec);
  desiredValue -= 180;
  wait(3,sec);
  IntakeMotors.stop();
  desiredTurnValue = 90;
  // IntakeMotors.spinFor(reverse,0.2,sec);
  wait(3,sec);
  //Shoot
  // IntakeMotors.spin(forward);
  wait(3,sec);
  desiredValue -= 40;
  wait(3, sec);
  desiredValue += 40;
  desiredTurnValue = 135;
  //Expand
  while(true){
    this_thread::sleep_for(25);
  }
}

// this is just for the animation on the screen it has no use other than that :D
void ScreenAnime() {
  while (true){
  double starttimer = vex::timer::system();
  Entry = 0;
  Brain.Screen.clearScreen();
  for (int i = 0; i <368; i++){
    float x0 = XYZ[i][0];
        float y0 = XYZ[i][1];
        float z0 = XYZ[i][2];
        float x1 = x0;
        float y1 = y0;
        float z1 = y0 * sin(Raidan) + z0 * cos(Raidan);
        x0 = x1;
        y0 = y1;
        z0 = -z1 * sin(Raidan) + z1 * cos(Raidan);
        XYZ[i][0] = x0;
        XYZ[i][1] = y0;
        XYZ[i][2] = z0;
  }
  for (int i = 0; i < 664; i++) {
        int x0 = XYZ[Connections[i][0]][0];
        int y0 = XYZ[Connections[i][0]][1];
        int x1 = XYZ[Connections[i][1]][0];
        int y1 = XYZ[Connections[i][1]][1];
        Brain.Screen.drawLine(x0, y0, x1, y1);
    }
  
  Brain.Screen.setCursor(12,40);
  Brain.Screen.print(starttimer - vex::timer::system());
  Raidan += 0.001f;
  if(Raidan >= 2*M_PI){
    Raidan -= 2*M_PI;
  }
  this_thread::sleep_for(50);
  }
}
//Don't look down here there isn't anything down here but suffering :)
//and our dumb methods XD
//also vex devices are painful D
//Lines 110 - 864 (754 lines worth :D) are definitly useful, yep definitly ;p