//////////////////////////////////////////////////////////////////////
// Select a maze solving algorithm. Select only one, comment the rest
//////////////////////////////////////////////////////////////////////
#define LEFTWALLFOLLOW
// #define RIGHTWALLFOLLOW
// #define DFS
// #define FLOODFILL
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following section consists of all offsets and factors for the robot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const float alpha = 0.65; // Smoothing factor (range 0 - 1) (value directly proportional to somoothness)

int wallSense = 70; // Threshold value to detect walls by the diagonal sensors while moving straight.
int WallSenseDuringTurn = wallSense - 35;

int leftWallOffset = 110;
int rightWallOffset = 110;

float leftTurnSense = 15.5;
float rightTurnSense = 15.5;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following section consists of all pin configurations for the robot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Proximity sensor address and colour sensor address connected to TCA9548 I2C multiplexer
//////////////////////////////////////////////////////////////////////
#define FL 3 // Forward facing left side
#define FR 6 // Forward facing right side
#define DL 2 // Diagonal facing left side
#define DR 7 // Diagonal facing right side
#define CRGB 8 //Colour Sensor
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Encoder pinouts
//////////////////////////////////////////////////////////////////////
#define enc1 8
#define enc2 9
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// General purpose Outputs
//////////////////////////////////////////////////////////////////////
#define BUZZPIN 23
#define LED13 LED_BUILTIN
#define LEFTLED 20
#define RIGHTLED 20
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Motor pinouts
//////////////////////////////////////////////////////////////////////
#define LMF 14 // Left motor forward
#define LMR 13  // Left motor reverse
#define PWML 15 // PWM channel left
#define RMF 12  // Right motor forward
#define RMR 11  // Right motor reverse
#define PWMR 10 // PWM channel right
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following section consists of all PD parameters for the robot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Turning PD parameter(s)
//////////////////////////////////////////////////////////////////////
#define kp_turn 4.5
#define kd_turn 3.2
#define MAXSPEED_turning 135
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Front wall align PD parameter(s)
//////////////////////////////////////////////////////////////////////
#define kp_wallalign 2.23
#define MAXSPEED_wallalign 95
#define OFFSET_wallalign 155
#define OFFSET_wallalign_sense 65
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// move to distance PD parameter(s)
//////////////////////////////////////////////////////////////////////
#define kp_move_distance 23
#define kd_move_distance 2
#define MINSPEED_move_distance 25
#define MAXSPEED_move_distance MAXSPEED_move
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Front wall align PD parameter(s)
//////////////////////////////////////////////////////////////////////
#define LEFTWALLOFFSET 155
#define RIGHTWALLOFFSET 125
#define kp_align 2.2
#define kd_align 2.8
#define MAXSPEED_align 90
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// move straight PD parameter(s)
//////////////////////////////////////////////////////////////////////
#define kp_move 0.35
#define kd_move 0.5
#define BASESPEED_move 125
#define MAXSPEED_move BASESPEED_move
#define MAX_error 75
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/*  Gyro assisted robot alignment parameter(s)
NOTE: This value affects move straight PD aswell.
both are directly proportional to each other
*/
//////////////////////////////////////////////////////////////////////
#define kp_gyroAssist 2.5
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following section consists of miscellaneous parameters for the robot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Navigation settings
//////////////////////////////////////////////////////////////////////
#define BACKALIGN_UTURN // align by bumping into the wall by reversing during u-turn
#define DISTANCE_TO_TRAVEL_AFTER_FRONTWALL_DETECT 0
#define DISTANCE_TO_TRAVEL_AFTER_SIDEWALL_DETECT 6.5
//////////////////////////////////////////////////////////////////////