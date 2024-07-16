/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
██████╗ ██╗███╗   ██╗     █████╗ ███████╗███████╗██╗ ██████╗ ███╗   ██╗███╗   ███╗███████╗███╗   ██╗████████╗
██╔══██╗██║████╗  ██║    ██╔══██╗██╔════╝██╔════╝██║██╔════╝ ████╗  ██║████╗ ████║██╔════╝████╗  ██║╚══██╔══╝
██████╔╝██║██╔██╗ ██║    ███████║███████╗███████╗██║██║  ███╗██╔██╗ ██║██╔████╔██║█████╗  ██╔██╗ ██║   ██║
██╔═══╝ ██║██║╚██╗██║    ██╔══██║╚════██║╚════██║██║██║   ██║██║╚██╗██║██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║
██║     ██║██║ ╚████║    ██║  ██║███████║███████║██║╚██████╔╝██║ ╚████║██║ ╚═╝ ██║███████╗██║ ╚████║   ██║
╚═╝     ╚═╝╚═╝  ╚═══╝    ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// button                      = D4
// Ultrasonic F,R,L            = A0-A2
// I2C Bus                     = A4-A5 -> LCD, Gyro
// MotorSpeed                  = D5
// Moto direction              = D6
// Servo steering (pwm signal) = D3

///////////////////////////////////////////////////////////////
/*
██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗███████╗███████╗
██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║██╔════╝██╔════╝
██║     ██║██████╔╝██████╔╝███████║██████╔╝██║█████╗  ███████╗
██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗██║██╔══╝  ╚════██║
███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║██║███████╗███████║
╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝
*/
///////////////////////////////////////////////////////////////

#include <math.h>
// Servo section libraries
#include <Servo.h>
//-------------------------------------------------

// RGB libraries
#include <Wire.h>
#include "rgb_lcd.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 ██████╗ ██╗      ██████╗ ██████╗  █████╗ ██╗         ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
██╔════╝ ██║     ██╔═══██╗██╔══██╗██╔══██╗██║         ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
██║  ███╗██║     ██║   ██║██████╔╝███████║██║         ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
██║   ██║██║     ██║   ██║██╔══██╗██╔══██║██║         ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
╚██████╔╝███████╗╚██████╔╝██████╔╝██║  ██║███████╗     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
 ╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// timer
unsigned long start_time;
//--------------------------------------------------

// LCD connections
int Button = 4;
int colorRed = 255;
int colorGreen = 0;
int colorBlue = 0;
// LCD screen itself
rgb_lcd lcd;

// corners/edge detection
int corners;

// own variables for distances
// int Distance;
int Distance_Front;
int Distance_Left;
int Distance_Right;

float angle;
float danger;
float correction_Left = 10.0;
float correction_Right = 10.0;
float StraightAngle = 0.0;

// Driving direction 'U' for Unknown
char DrivingDirection = 'U';

// Speeds
int NormalSpeed = 100;
int SlowSpeed = 110;
int CurveSpeed = 90;
int StartSpeed = 100;

// obstacle block 'U' for unknown
char Block = 'U';

// Block variables
char P_color = 'U'; // Unknown
char P_wall_L = 'N';
char P_wall_R = 'N';
char LastPillarColor = 'U';
int P_x = 0;
int P_height = 0;

// last counted corners
unsigned long LastCurveTime;
unsigned long NextCurveDelay = 5000;

// both allignments (L/R)
int walldistance = 40;

// own Module
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\DCmotor.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\gyro2.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\steering.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\ultrasonic_urm09.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\raspi.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\cam.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 ██████╗ ██╗    ██╗███╗   ██╗    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
██╔═══██╗██║    ██║████╗  ██║    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
██║   ██║██║ █╗ ██║██╔██╗ ██║    █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
██║   ██║██║███╗██║██║╚██╗██║    ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
╚██████╔╝╚███╔███╔╝██║ ╚████║    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
 ╚═════╝  ╚══╝╚══╝ ╚═╝  ╚═══╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// ProgramStopUsingGyro()
// stops the car using the gyrovalues saved from beginning
/////////////////////////////////////////////////////////////////////
void ProgramStopUsingGyro()
{
  unsigned long DrivingTime; // driving time
  unsigned long temporaryTime;

  runMotor(SlowSpeed); // slow down
  // slight countersteering to compensate for overshooting
  if (DrivingDirection == 'R')
  {
    left(10);
  }

  else
  {
    right(10);
  }

  delay(400);
  center();

  // Go straight for at least 400 msec
  Gyro_steer_straight();
  temporaryTime = millis();
  while (millis() < temporaryTime + 3000)
  {
    Gyro_steer_straight();
  }

  // drive straight to finish and stop
  Distance_Front = SpaceUltraSonicFront();
  while (Distance_Front > 140)
  {
    Gyro_steer_straight();
    Distance_Front = SpaceUltraSonicFront();
  }

  stopMotor();
  // save current time in milliseconds
  DrivingTime = millis() - start_time;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("time: ");
  lcd.print(DrivingTime);
  lcd.print(Distance_Front);
  delay(9999999); // wait forever
}

////////////////////////////////////////////////////////////////////
// Gyro_steer_straight()
// uses the gyro to orient itself straight to the track
////////////////////////////////////////////////////////////////////
void Gyro_steer_straight()
{
  float angle;
  int Speed;
  int Steering;
  angle = IMU_getAngle();

  Steering = (angle - StraightAngle) * 0.8; // 0.8 = wiggle factor
  if (Steering > 15.0)
  {
    Steering = 15;
  }
  else if (Steering < -15.0)
  {
    Steering = -15;
  }

  if (Steering < 0)
  {
    Steering = Steering * (-1);
    right(Steering);
  }

  else
  {
    left(Steering);
  }

  // delay(20);
}

/////////////////////////////////////////////////////////////////////
// CalculateTargetDirection()
// calculates the target direction for the next curve
/////////////////////////////////////////////////////////////////////
float CalculateTargetDirection()
{
  float CalculateAngle = 0.0;

  if (DrivingDirection == 'R')
  {
    CalculateAngle = StraightAngle + 90.0;
  }

  else if (DrivingDirection == 'L')
  {
    CalculateAngle = StraightAngle - 90.0;
  }

  return CalculateAngle;
}

/////////////////////////////////////////////////////
// CalculateStraightAngle()
// calculates the target angle for the next curve
/////////////////////////////////////////////////////
float CalculateStraightAngle(float angle)
{
  float StraightAngle = 0.0;
  int factor = 0;

  // calculate straight direction
  factor = int((angle + 44.0) / 90.0); // int cuts off fractions
  StraightAngle = factor * 90.0;

  return StraightAngle;
}

/////////////////////////////////////////////////////////////////////
// TurnLeft()
// turns left until 90 degrees
/////////////////////////////////////////////////////////////////////
void TurnLeft()
{
  float TargetDirection;
  int Speed;
  int backtime;
  lcd.setRGB(125, 0, 125);
  Speed = SlowSpeed;
  stopMotor();
  Distance_Right = SpaceUltraSonicRight();
  if (Distance_Right > 50)
  {
    // position left of center
    backtime = 1500;
  }
  else
  {
    backtime = 200;
  }
  runMotor(SlowSpeed);
  right(45);

  angle = IMU_getAngle();
  // replaces complicated quadrantSYS
  TargetDirection = CalculateTargetDirection();

  runMotor_R(SlowSpeed); // backwards turn
  // turn until 90 degrees or block in sight
  // turn backward for 45 degrees
  while (angle > StraightAngle - 45.0)
  {
    angle = IMU_getAngle();
    delay(20);
  }
  center();
  delay(1000);
  stopMotor();

  // turn forward
  left(45);
  runMotor(SlowSpeed);
  while (angle > TargetDirection)
  {
    angle = IMU_getAngle();
    delay(20);
  }
  stopMotor();

  corners = corners + 1;
  StraightAngle = TargetDirection;
  center();
  stopMotor();
  Distance_Left = SpaceUltraSonicLeft();
  Distance_Right = SpaceUltraSonicRight();
  Distance_Front = SpaceUltraSonicFront();
  runMotor_R(SlowSpeed);
  delay(backtime);
  stopMotor();
  runMotor(SlowSpeed);
  lcd.setRGB(255, 255, 255);
  LastCurveTime = millis();
  runMotor(SlowSpeed);
}

/////////////////////////////////////////////////////////////////////
// TurnRight()
// turns right until 90 degrees
/////////////////////////////////////////////////////////////////////
void TurnRight()
{
  float TargetDirection;
  int Speed;
  int backtime;
  lcd.setRGB(125, 0, 125);
  Speed = SlowSpeed;
  stopMotor();
  Distance_Left = SpaceUltraSonicLeft();
  if (Distance_Left > 50)
  {
    // position left of center
    backtime = 1500;
  }
  else
  {
    backtime = 200;
  }
  runMotor(SlowSpeed);

  left(45);

  angle = IMU_getAngle();
  // replaces complicated quadrantSYS
  TargetDirection = CalculateTargetDirection();

  runMotor_R(SlowSpeed); // backwards turn
  // turn until 90 degrees or block in sight
  // turn backward for 45 degrees
  while (angle < StraightAngle + 45.0)
  {
    angle = IMU_getAngle();
    delay(20);
  }
  center();
  delay(1000);
  stopMotor();

  // turn forward
  right(45);
  runMotor(SlowSpeed);
  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
    delay(20);
  }
  stopMotor();

  corners = corners + 1;
  StraightAngle = TargetDirection;
  center();
  stopMotor();
  Distance_Left = SpaceUltraSonicLeft();
  Distance_Right = SpaceUltraSonicRight();
  Distance_Front = SpaceUltraSonicFront();
  runMotor_R(SlowSpeed);
  delay(backtime);
  stopMotor();
  runMotor(SlowSpeed);
  lcd.setRGB(255, 255, 255);
  LastCurveTime = millis();
  runMotor(SlowSpeed);
}

/////////////////////////////////////////////////////////////////////
// alignCenter()
// aligns to the center of the track
/////////////////////////////////////////////////////////////////////
void alignCenter()
{
  int Steering;
  Steering = (Distance_Left - Distance_Right) * 0.3;
  if (Steering > 30.0)
  {
    Steering = 30;
  }
  else if (Steering < -30.0)
  {
    Steering = -30;
  }

  if (Steering < 0)
  {
    Steering = Steering * (-1);
    right(Steering);
  }

  else
  {
    left(Steering);
  }

  delay(20);
}

/////////////////////////////////////////////////////////////////////
// alignLeft()
// aligns to the left wall
/////////////////////////////////////////////////////////////////////
void alignLeft()
{
  int Steering;
  Distance_Left = SpaceUltraSonicLeft();
  Steering = (Distance_Left - walldistance) * 0.9;
  if (Steering > 30.0)
  {
    Steering = 30;
  }
  else if (Steering < -30.0)
  {
    Steering = -30;
  }

  if (Steering < 0)
  {
    Steering = Steering * (-1);
    right(Steering);
  }

  else
  {
    left(Steering);
  }

  delay(20);
}

/////////////////////////////////////////////////////////////////////
// alignRight()
// aligns to the right wall
/////////////////////////////////////////////////////////////////////
void alignRight()
{
  int Steering;

  Distance_Right = SpaceUltraSonicRight();

  Steering = (walldistance - Distance_Right) * 0.9;
  if (Steering > 30.0)
  {
    Steering = 30;
  }
  else if (Steering < -30.0)
  {
    Steering = -30;
  }

  if (Steering < 0)
  {
    Steering = Steering * (-1);
    right(Steering);
  }

  else
  {
    left(Steering);
  }

  delay(20);
}

/////////////////////////////////////////////////////////////////////
// CurveLeftUntilBlock()
// makes left turn until 90 degrees or block in sight to adjust speed
/////////////////////////////////////////////////////////////////////
void CurveLeftUntilBlock()
{
  int Speed;
  float TargetDirection;
  Speed = SlowSpeed;
  lcd.setRGB(0, 0, 255);
  TargetDirection = CalculateTargetDirection();
  lcd.setCursor(0, 0);
  lcd.print(TargetDirection);
  Distance_Front = SpaceUltraSonicFront();
  // go straight to opposite wall
  while (Distance_Front > 50)
  {
    Gyro_steer_straight();
    Distance_Front = SpaceUltraSonicFront();
  }
  // wall reached
  stopMotor();
  // start turning
  left(45);
  runMotor(SlowSpeed);
  angle = IMU_getAngle();
  // replaces quadrantenSYS
  runMotor(SlowSpeed);

  while (angle > StraightAngle - 45.0)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  center();
  runMotor(SlowSpeed);
  delay(500);
  stopMotor();
  right(45);
  runMotor_R(SlowSpeed);
  while (angle > TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  center();
  runMotor(SlowSpeed);
  delay(500);
  corners = corners + 1;
  StraightAngle = TargetDirection;
  runMotor(SlowSpeed);
  lcd.setRGB(255, 255, 255);
  LastCurveTime = millis();
}

/////////////////////////////////////////////////////////////////////
// CurveRightUntilBlock()
// makes right turn until 90 degrees or block in sight to adjust speed
/////////////////////////////////////////////////////////////////////
void CurveRightUntilBlock()
{
  int Speed;
  float TargetDirection;
  Speed = SlowSpeed;
  lcd.setRGB(0, 0, 255);
  TargetDirection = CalculateTargetDirection();
  lcd.setCursor(0, 0);
  lcd.print(TargetDirection);
  Distance_Front = SpaceUltraSonicFront();
  // go straight to opposite wall
  while (Distance_Front > 50)

  {
    Gyro_steer_straight();
    Distance_Front = SpaceUltraSonicFront();
  }
  // wall reached
  stopMotor();
  // start turning
  right(45);
  runMotor(SlowSpeed);
  angle = IMU_getAngle();
  // replaces quadrantenSYS
  runMotor(SlowSpeed);

  while (angle < StraightAngle + 45.0)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  center();
  runMotor(SlowSpeed);
  delay(500);
  stopMotor();
  left(45);
  runMotor_R(SlowSpeed);
  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  center();
  runMotor(SlowSpeed);
  delay(500);
  corners = corners + 1;
  StraightAngle = TargetDirection;
  runMotor(SlowSpeed);
  lcd.setRGB(255, 255, 255);
  LastCurveTime = millis();
}

/////////////////////////////////////////////////////////////////////
// DriveUntilFirstPillarInLane()
// drive straight until next pillar in lane is found
/////////////////////////////////////////////////////////////////////
void DriveUntilFirstPillarInLane()
{
  runMotor(SlowSpeed);
  findNextPillar();
  if (DrivingDirection == 'L')
  {
    // go straight, until pillar is in sight,
    // ignore pillars on the extrem left, we have already passed them,
    // they are in the last lane
    while ((P_color == 'U') || (P_x < 50))
    {
      Gyro_steer_straight();
      findNextPillar();
    }
  }
  else
  {
    // go straight, until pillar is in sight,
    // ignore pillars on the extrem right, we have already passed them,
    // they are in the last lane
    while ((P_color == 'U') || (P_x > 270))
    {
      Gyro_steer_straight();
      findNextPillar();
    }
  }
}

/////////////////////////////////////////////////////////////////////
// DriveUntilNextCurve()
// drive straight until curve is found
/////////////////////////////////////////////////////////////////////
void DriveUntilNextCurve()
{
  Distance_Front = SpaceUltraSonicFront();
  while (Distance_Front > 100)
  {
    Gyro_steer_straight();
    Distance_Front = SpaceUltraSonicFront();
  }
}
/////////////////////////////////////////////////////////////////////
// steerToLaneCenter()
// make a small move toward the lane center
/////////////////////////////////////////////////////////////////////

void steerToLaneCenter()
{

  float TargetDirection;
  unsigned long start;
  TargetDirection = StraightAngle;
  Distance_Front = SpaceUltraSonicFront();
  Distance_Left = SpaceUltraSonicLeft();
  Distance_Right = SpaceUltraSonicRight();

  if (Distance_Left < 25)
  {
    // steer to the middle of the lane
    right(25);
    delay(500);
    center();
    delay(500);
    // back to straight
    left(25);

    angle = IMU_getAngle();
    while (angle > TargetDirection /*- correction_Left*/)
    {
      angle = IMU_getAngle();
      delay(20);
    }
    center();
    runMotor(SlowSpeed);
  }
  else if (Distance_Right < 25)
  {
    // steer to the middle of the lane
    left(25);
    delay(500);
    center();
    delay(500);
    // back to straight
    right(25);

    angle = IMU_getAngle();
    while (angle > TargetDirection /*- correction_Left*/)
    {
      angle = IMU_getAngle();
      delay(20);
    }
    center();
    runMotor(SlowSpeed);
  }
  else
  {
    // just go straight for 500 msec
    start = millis();
    while (millis() < start + 500)
    {
      Gyro_steer_straight();
      delay(20);
    }
  }
}
/////////////////////////////////////////////////////////////////////
// ApproachPillar()
// drive towards green pillar
/////////////////////////////////////////////////////////////////////
void ApproachPillar()
{
  runMotor(SlowSpeed);
  findNextPillar();
  if (P_color == 'R')
  {
    lcd.setRGB(255, 0, 0);
  }
  else if (P_color == 'G')
  {
    lcd.setRGB(0, 255, 0);
  }

  while (P_height < 30)
  {
    SteerToPillar();
    findNextPillar();
    lcd.setCursor(0, 0);
    lcd.print(P_height);
    lcd.print("    ");
  }
}
/////////////////////////////////////////////////////////////////////
// SteerToPillar()
// steers towards pillar
/////////////////////////////////////////////////////////////////////
void SteerToPillar()
{
  int Steering;
  int SteerTarget;

  if (P_color == 'R')
  {
    SteerTarget = P_x + 20;
  }

  else
  {
    SteerTarget = P_x - 20;
  }

  Steering = (160 - SteerTarget) * 0.3;
  if (Steering > 30.0)
  {
    Steering = 30;
  }
  else if (Steering < -30.0)
  {
    Steering = -30;
  }

  if (Steering < 0)
  {
    Steering = Steering * (-1);
    right(Steering);
  }

  else
  {
    left(Steering);
  }
}

/////////////////////////////////////////////////////////////////////
// EvadeGreenPillar()
// evades green block to the left until it is not in sight
/////////////////////////////////////////////////////////////////////
void EvadeGreenPillar()
{
  float angle;
  float TargetDirection;
  int Speed;
  int prev_x;
  lcd.setRGB(0, 255, 0);
  // save orientation
  angle = IMU_getAngle();
  // calculate next straight direction
  // TargetDirection = CalculateStraightAngle(angle);
  TargetDirection = StraightAngle;
  runMotor(SlowSpeed);
  left(35);
  // runMotor(CurveSpeed);
  findNextPillar();
  // turn until block is on the left
  while ((P_x < 290) && (P_color == 'G'))
  {
    findNextPillar();
  }
  // Go past pillar, until it is not longer seen or wall collision
  // while ((P_color != 'U') && (P_wall_R == 'N'))
  center();
  delay(200); // go straigh minimum 200 msec

  while (P_color == 'G')
  {
    findNextPillar();
  }

  delay(200);
  // back to straight
  right(35);

  angle = IMU_getAngle();
  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
    delay(10);
  }
  center();
  runMotor(SlowSpeed);
  // drive past
  prev_x = P_x;
  findNextPillar();
  while ((P_color == 'G') && (P_x >= prev_x))
  {
    P_x = prev_x;
    findNextPillar();
    Gyro_steer_straight();
  }

  delay(100);
  lcd.setRGB(255, 255, 255);
  LastPillarColor = 'G';
}

/////////////////////////////////////////////////////////////////////
// EvadeRedPillar()
// evades red block to the right until it is not in sight
/////////////////////////////////////////////////////////////////////
void EvadeRedPillar()
{
  float angle;
  float TargetDirection;
  int Speed;
  int prev_x;

  lcd.setRGB(255, 0, 0);
  // save orientation
  angle = IMU_getAngle();
  // calculate next straight direction
  // TargetDirection = CalculateStraightAngle(angle);
  TargetDirection = StraightAngle;
  runMotor(SlowSpeed);
  right(35);
  // runMotor(CurveSpeed);
  findNextPillar();
  // turn until block is on the right
  while ((P_x > 30) && (P_color == 'R'))
  {
    findNextPillar();
  }
  // Go past pillar, until it is not longer seen or wall collision
  // while ((P_color != 'U') && (P_wall_R == 'N'))

  center();
  delay(200);

  while (P_color == 'R')
  {
    findNextPillar();
  }

  delay(200);
  // back to straight
  left(35);

  angle = IMU_getAngle();
  while (angle > TargetDirection /*- correction_Left*/)
  {
    angle = IMU_getAngle();
    delay(10);
  }
  center();
  runMotor(SlowSpeed);
  // drive past
  prev_x = P_x;
  findNextPillar();
  while ((P_color == 'R') && (P_x <= prev_x))
  {
    P_x = prev_x;
    findNextPillar();
    Gyro_steer_straight();
  }

  delay(100);
  lcd.setRGB(255, 255, 255);
  LastPillarColor = 'R';
}

void runCurvesimple()
{
  if (DrivingDirection == 'L')
  {
    CurveLeftUntilBlock();
  }

  else
  {
    CurveRightUntilBlock();
  }
}

/////////////////////////////////////////////////////////////////////
// runCurve()
// runs a curve phase
/////////////////////////////////////////////////////////////////////
void runCurve()
{

  // Turn
  if (DrivingDirection == 'L')
  {

    Distance_Right = SpaceUltraSonicRight();
    if (Distance_Right < 25)
    {
      CurveLeftUntilBlock();
    }
    else
    {
      // Go straight to opposite wall
      Distance_Front = SpaceUltraSonicFront();
      while (Distance_Front > 10)
      {
        Gyro_steer_straight();
        Distance_Front = SpaceUltraSonicFront();
      }
      // wall reached
      stopMotor();
      TurnLeft();
    }
  }
  else
  {
    Distance_Left = SpaceUltraSonicLeft();
    if (Distance_Left < 25)
    {
      CurveRightUntilBlock();
    }
    else
    {
      // Go straight to opposite wall
      Distance_Front = SpaceUltraSonicFront();
      while (Distance_Front > 10)
      {
        Gyro_steer_straight();
        Distance_Front = SpaceUltraSonicFront();
      }
      // wall reached
      stopMotor();

      TurnRight();
    }
  }
}

/////////////////////////////////////////////////////////////////////
// runLanesimple()
// run along one lane with obstacles
// checks for minimum 1 obstacle, maximum 2 obstacles
/////////////////////////////////////////////////////////////////////
void runLanesimple()
{
  bool check = false;
  stopMotor();
  findNextPillar();
  lcd.setCursor(0, 0);
  lcd.print(P_color);
  lcd.print(" ");
  lcd.print(P_height);
  delay(200);

  DriveUntilFirstPillarInLane();
  ApproachPillar();
  if (P_color == 'R')
  {
    EvadeRedPillar();
  }
  else
  {
    EvadeGreenPillar();
  }
  stopMotor();

  DriveUntilNextCurve();
}
/////////////////////////////////////////////////////////////////////
// runLane()
// run along one lane with obstacles
// checks for minimum 1 obstacle, maximum 2 obstacles
/////////////////////////////////////////////////////////////////////
/*void runLane()
{
  bool check = false;
  stopMotor();
  findNextPillar();
  lcd.setCursor(0, 0);
  lcd.print(P_color);
  lcd.print(" ");
  lcd.print(P_height);
  delay(200);

  if (P_height > 20)
  {
    // lane may have 2 pillars
    DriveUntilFirstPillarInLane();
    ApproachPillar();
    if (P_color == 'R')
    {
      EvadeRedPillar();
    }
    else
    {
      EvadeGreenPillar();
    }
    stopMotor();
    // Another pillar in this lane?
    findNextPillar();
    lcd.setCursor(0, 0);
    lcd.print(P_color);
    lcd.print(" ");
    lcd.print(P_height);
    delay(200);

    if (P_height > 20)
    {
      // lane may have 2 pillars
      DriveUntilFirstPillarInLane();
      ApproachPillar();
      if (P_color == 'R')
      {
        EvadeRedPillar();
      }
      else
      {
        EvadeGreenPillar();
      }
      stopMotor();
      // Another pillar in this lane?
      /*findNextPillar();
      // check if pillar is in lane
      lcd.setCursor(0, 0);
      lcd.print(P_color);
      if (P_color != 'U')
      {
        check = CheckPillarIsInLane();
      }
      else
      {
        check = false;
      }

      runMotor(SlowSpeed);
      if ((P_color == 'R') && (check == true))
      {
        ApproachPillar();
        EvadeRedPillar();
      }
      else if ((P_color == 'G') && (check == true))
      {
        ApproachPillar();
        EvadeGreenPillar();
      }
    }

else
{
  // lane has ony 1 pillar
  DriveUntilFirstPillarInLane();
  ApproachPillar();
  if (P_color == 'R')
  {
    EvadeRedPillar();
  }
  else
  {
    EvadeGreenPillar();
  }
}

DriveUntilNextCurve();
}
}
}
*/

/////////////////////////////////////////////////////////////////////
// CheckPillarIsInLane()
// Checks, if a Pillar in view is in the current lane #
// or behind the next curve
/////////////////////////////////////////////////////////////////////
bool CheckPillarIsInLane()
{
  findNextPillar();
  if ((DrivingDirection == 'L') && (P_color != 'U') && (P_x > 90))
  {
    return true;
  }
  else if ((DrivingDirection == 'R') && (P_color != 'U') && (P_x < 215))
  {
    return true;
  }
  else
  {
    return false;
  }
}
/////////////////////////////////////////////////////////////////////
// measureAllDistances()
// measures all distances and saves them in global variables
/////////////////////////////////////////////////////////////////////
void measureAllCurrentDistances()
{
  Distance_Front = SpaceUltraSonicFront();
  Distance_Left = SpaceUltraSonicLeft();
  Distance_Right = SpaceUltraSonicRight();
}

/////////////////////////////////////////////////////////////////////
// printAllDistancesToLCD()
// prints all distances to the LCD aswell as DrivingDirection
/////////////////////////////////////////////////////////////////////
void printAllCurrentDistancesToLCD()
{
  lcd.setCursor(0, 0);
  lcd.print(Distance_Left);
  lcd.print("  ");
  lcd.print(Distance_Front);
  lcd.print("  ");
  lcd.print(Distance_Right);
  lcd.setCursor(0, 1);
  lcd.print(angle);
  lcd.print("  ");
  lcd.print(DrivingDirection);
  lcd.print("  ");
  lcd.print(P_color);
}

/////////////////////////////////////////////////////////////////////
// waitOnButtonPress()
// waits until the button is pressed
/////////////////////////////////////////////////////////////////////
void waitOnButtonPress()
{
  // switch lcd to yellow and wait on button press
  lcd.setRGB(255, 130, 0);
  while (digitalRead(Button) == LOW)
  {
    delay(50);
  }
}

/////////////////////////////////////////////////////////////////////
// saveCurrentTime()
// saves the current time in milliseconds subtracting NextCurveDelay
/////////////////////////////////////////////////////////////////////

void saveCurrentTime()
{
  start_time = millis();
  LastCurveTime = millis() - NextCurveDelay;
}

///////////////////////////////////////////////////////////////////////
// evaluateRaspiData()
// evaluates the data from the raspi handshake
///////////////////////////////////////////////////////////////////////
void evaluateRaspiData()
{
  if (P_color != 'U')
  {
    if (P_x < 110)
    {
      DrivingDirection = 'L';
    }
    else if (P_x > 210)
    {
      DrivingDirection = 'R';
    }
  }
}

///////////////////////////////////////////////////////////
// startPhase();
// starts the phase
///////////////////////////////////////////////////////////
void startPhase()
{
  bool centerRight = false;
  bool centerLeft = false;
  float TargetDirection;
  float angle;

  runMotor(SlowSpeed);
  findNextPillar(); // requests what is seen in front
  //  Check if pillar is right ahead
  if ((P_color == 'R') && (P_x < 210) && (P_x > 110))
  {
    ApproachPillar();
    EvadeRedPillar();

    runMotor(SlowSpeed);
    while (Distance_Front > 10)
    {
      Gyro_steer_straight();
      Distance_Front = SpaceUltraSonicFront();
    }
    stopMotor();
    if (DrivingDirection == 'U')
    {
      Distance_Left = SpaceUltraSonicLeft();
      Distance_Right = SpaceUltraSonicRight();

      if (Distance_Left > 150)
      {
        DrivingDirection = 'L';
      }

      else if (Distance_Right > 150)
      {
        DrivingDirection = 'R';
      }
      else
      {
        // Problem: cannot find driving direction
        // try with direction of next pillar
        runMotor_R(SlowSpeed);
        delay(800);
        stopMotor();
        findNextPillar();
        if (P_x > 160)
        {
          DrivingDirection = 'R';
        }
        else
        {
          DrivingDirection = 'L';
        }
        Distance_Front = SpaceUltraSonicFront();
        runMotor(SlowSpeed);
        while (Distance_Front > 10)
        {
          Gyro_steer_straight();
          Distance_Front = SpaceUltraSonicFront();
        }
        stopMotor();
      }
    }
  }

  else if ((P_color == 'G') && (P_x < 210) && (P_x > 110))
  {
    ApproachPillar();
    EvadeGreenPillar();

    runMotor(SlowSpeed);
    Distance_Front = SpaceUltraSonicFront();
    while (Distance_Front > 10)
    {
      Gyro_steer_straight();
      Distance_Front = SpaceUltraSonicFront();
    }
    stopMotor();
    if (DrivingDirection == 'U')
    {
      Distance_Left = SpaceUltraSonicLeft();
      Distance_Right = SpaceUltraSonicRight();

      if (Distance_Left > 150)
      {
        DrivingDirection = 'L';
      }

      else if (Distance_Right > 150)
      {
        DrivingDirection = 'R';
      }
      else
      {
        // Problem: cannot determine Driving direction,
        // try with direction of next pillar
        runMotor_R(SlowSpeed);
        delay(800);
        stopMotor();
        findNextPillar();
        if (P_x > 160)
        {
          DrivingDirection = 'R';
        }
        else
        {
          DrivingDirection = 'L';
        }
        Distance_Front = SpaceUltraSonicFront();
        runMotor(SlowSpeed);
        while (Distance_Front > 10)
        {
          Gyro_steer_straight();
          Distance_Front = SpaceUltraSonicFront();
        }
        stopMotor();
      }
    }
  }

  else
  {
    // No pillar directly ahead
    while (Distance_Front > 10)
    {
      Gyro_steer_straight();
      Distance_Front = SpaceUltraSonicFront();
    }
    // wall reached
    stopMotor();
    // if driving direction is unclear, find out
    if (DrivingDirection == 'U')
    {
      Distance_Left = SpaceUltraSonicLeft();
      Distance_Right = SpaceUltraSonicRight();

      if (Distance_Left > 80)
      {
        DrivingDirection = 'L';
      }

      else if (Distance_Right > 80)
      {
        DrivingDirection = 'R';
      }
      else
      {
        // Problem: cannot find driving drection
      }
    }
  }

  stopMotor();
  lcd.setCursor(0, 0);
  lcd.print(DrivingDirection);
  lcd.print("  ");
  lcd.print(Distance_Left);
  lcd.print("  ");
  lcd.print(Distance_Right);
  delay(500);
  runMotor(SlowSpeed);

  // Turn
  if (DrivingDirection == 'L')
  {
    if (Distance_Right < 25)
    {
      Distance_Front = SpaceUltraSonicFront();
      runMotor_R(SlowSpeed);
      while (Distance_Front < 50)
      {
        Distance_Front = SpaceUltraSonicFront();
      }
      stopMotor();
      runMotor(SlowSpeed);
      CurveLeftUntilBlock();
    }
    else
    {
      TurnLeft();
    }
  }
  else
  {
    if (Distance_Left < 25)
    {
      Distance_Front = SpaceUltraSonicFront();
      runMotor_R(SlowSpeed);
      while (Distance_Front < 50)
      {
        Distance_Front = SpaceUltraSonicFront();
      }
      stopMotor();
      runMotor(SlowSpeed);
      CurveRightUntilBlock();
    }
    else
    {
      TurnRight();
    }
  }
}

void startPhaseSimple()
{
  bool centerRight = false;
  bool centerLeft = false;
  float TargetDirection;
  float angle;

  findNextPillar();
  // wenn ein hindernis hinter der kurve ist wird die richtung geaendert
  if (P_x < 110)
  {
    DrivingDirection = 'L';
  }
  else if (P_x > 210)
  {
    DrivingDirection = 'R';
  }

  runMotor(SlowSpeed);

  while ((Distance_Left < 80.0) && (Distance_Right < 80.0) && (P_color == 'U'))
  {
    Distance_Left = SpaceUltraSonicLeft();
    Distance_Right = SpaceUltraSonicRight();
    Gyro_steer_straight();
    findNextPillar();
  }

  if (Distance_Left >= 80.0)
  {
    DrivingDirection = 'L';
    CurveLeftUntilBlock();
  }
  else if (Distance_Right >= 80.0)
  {
    DrivingDirection = 'R';
    CurveRightUntilBlock();
  }

  if (P_color != 'U')
  {
    ApproachPillar();

    if (P_color == 'R')
    {
      EvadeRedPillar();
    }
    else
    {
      EvadeGreenPillar();
    }
  }
  else
  {
    runMotor(SlowSpeed);
  }
}

///////////////////////////////////////////
// LanewithUTurn()
// special func for lane with unknown turn
///////////////////////////////////////////
void LanewithUTurn()
{
  bool check = false;
  DriveUntilFirstPillarInLane();
  ApproachPillar();
  if (P_color == 'R')
  {
    EvadeRedPillar();
  }
  else
  {
    EvadeGreenPillar();
  }

  if (LastPillarColor == 'R')
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UTurn");
    UTurn();
    if (DrivingDirection == 'R')
    {
      DrivingDirection = 'L';
    }

    else
    {
      DrivingDirection = 'R';
    }
  }
  // Another pillar in this lane?
  findNextPillar();
  // check if pillar is in lane
  if (P_color != 'U')
  {
    check = CheckPillarIsInLane();
  }
  else
  {
    check = false;
  }

  runMotor(SlowSpeed);
  if ((P_color == 'R') && (check == true))
  {
    ApproachPillar();
    EvadeRedPillar();
  }
  else if ((P_color == 'G') && (check == true))
  {
    ApproachPillar();
    EvadeGreenPillar();
  }
  else
  {
    DriveUntilNextCurve();
  }
}

float UTurnRight()
{
  float TargetDirection;
  float angle;
  runMotor(SlowSpeed);
  TargetDirection = StraightAngle + 45.0;
  right(45);
  angle = IMU_getAngle();
  runMotor(SlowSpeed);

  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  left(45);
  TargetDirection = StraightAngle + 90.0;
  runMotor_R(SlowSpeed);
  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();

  TargetDirection = StraightAngle + 135.0;
  right(45);
  angle = IMU_getAngle();
  runMotor(SlowSpeed);

  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  left(45);
  TargetDirection = StraightAngle + 180.0;
  runMotor_R(SlowSpeed);
  while (angle < TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();

  center();

  runMotor(SlowSpeed);

  return TargetDirection;
}

float UTurnLeft()
{
  float TargetDirection;
  float angle;
  runMotor(SlowSpeed);
  TargetDirection = StraightAngle - 45.0;
  left(45);
  angle = IMU_getAngle();
  runMotor(SlowSpeed);

  while (angle > TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  right(45);
  TargetDirection = StraightAngle - 90.0;
  runMotor_R(SlowSpeed);
  while (angle > TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();

  TargetDirection = StraightAngle - 135.0;
  left(45);
  angle = IMU_getAngle();
  runMotor(SlowSpeed);

  while (angle > TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();
  right(45);
  TargetDirection = StraightAngle - 180.0;
  runMotor_R(SlowSpeed);
  while (angle > TargetDirection)
  {
    angle = IMU_getAngle();
  }
  stopMotor();

  center();

  runMotor(SlowSpeed);

  return TargetDirection;
}
void UTurn()
{
  float TargetDirection;
  runMotor(SlowSpeed);
  delay(1000);
  stopMotor();
  Distance_Left = SpaceUltraSonicLeft();
  Distance_Right = SpaceUltraSonicRight();
  if (Distance_Left > Distance_Right)
  {
    TargetDirection = UTurnLeft();
  }

  else
  {
    TargetDirection = UTurnRight();
  }

  StraightAngle = TargetDirection;
}

///////////////////////////////////////////
// start_test()
// example test race
///////////////////////////////////////////
void start_test()
{
  // Test: Fixed sequence
  DrivingDirection = 'L';
  findNextPillar();
  ApproachPillar();
  findNextPillar();
  EvadeRedPillar();
  runCurve();
  findNextPillar();
  ApproachPillar();
  EvadeGreenPillar();
  ApproachPillar();
  EvadeRedPillar();
  runCurve();
  ApproachPillar();
  EvadeGreenPillar();
  DriveUntilNextCurve();
  runCurve();
  ApproachPillar();
  EvadeRedPillar();
  ApproachPillar();
  EvadeGreenPillar();
  runCurve();
  stopMotor();
  delay(1000000000);
}
void start_test2()
{
  DrivingDirection = 'L';
  corners = 8;
  LanewithUTurn();
  stopMotor();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(DrivingDirection);
  delay(3000);
  runMotor(SlowSpeed);
  runCurve();
  stopMotor();
  delay(1000000000);
}
///////////////////////////////////////////
/*
███████╗███████╗████████╗██╗   ██╗██████╗
██╔════╝██╔════╝╚══██╔══╝██║   ██║██╔══██╗
███████╗█████╗     ██║   ██║   ██║██████╔╝
╚════██║██╔══╝     ██║   ██║   ██║██╔═══╝
███████║███████╗   ██║   ╚██████╔╝██║
╚══════╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝
*/
///////////////////////////////////////////

void setup()
{

  //////////////////////////////////////////////////////
  /*
   _       _ _           _
  (_)     (_) |         | |
   _ _ __  _| |_   _ __ | |__   __ _ ___  ___
  | | '_ \| | __| | '_ \| '_ \ / _` / __|/ _ \
  | | | | | | |_  | |_) | | | | (_| \__ \  __/
  |_|_| |_|_|\__| | .__/|_| |_|\__,_|___/\___|
                  | |
                  |_|
  init phase initalises all components and waits for button press
  */
  //////////////////////////////////////////////////////

  Wire.begin();

  pinMode(Button, INPUT); // button

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);
  lcd.print("obstacle race");

  // raspi handshake
  raspi_handshake();

  // from Steering.h
  servosetup();

  // setup from ultrasonic_urm09.h
  ultrasonicstart();

  // initalises motor pinmodes from DCmotor.h
  motorsetup();

  delay(5000); // wait for 5 seconds

  // gyro setup gyro2.h
  startGyroscope();

  // Get initial image processing result
  findNextPillar();
  evaluateRaspiData();

  // distance to wall
  measureAllCurrentDistances();

  // count corners
  angle = IMU_getAngle();

  // prints all distances to LCD
  printAllCurrentDistancesToLCD();

  // waits for button press
  waitOnButtonPress();

  //////////////////////////////////////////////////////
  /*
        _             _           _
       | |           | |         | |
    ___| |_ __ _ _ __| |_   _ __ | |__   __ _ ___  ___
   / __| __/ _` | '__| __| | '_ \| '_ \ / _` / __|/ _ \
   \__ \ || (_| | |  | |_  | |_) | | | | (_| \__ \  __/
   |___/\__\__,_|_|   \__| | .__/|_| |_|\__,_|___/\___|
                           | |
                           |_|
  Start phase run:
  drive straight until first curve is detected,
  detect driving direction clockwise or counterclockwise
  run until first curve is completed
  */
  //////////////////////////////////////////////////////

  lcd.clear();

  // LCD goes White
  lcd.setRGB(255, 255, 255);

  // save time in millis
  saveCurrentTime();

  // Steering centered
  center();

  startPhaseSimple();
}
// Done

//////////////////////////////////
/*
██╗      ██████╗  ██████╗ ██████╗
██║     ██╔═══██╗██╔═══██╗██╔══██╗
██║     ██║   ██║██║   ██║██████╔╝
██║     ██║   ██║██║   ██║██╔═══╝
███████╗╚██████╔╝╚██████╔╝██║
╚══════╝ ╚═════╝  ╚═════╝ ╚═╝
 */
//////////////////////////////////

void loop()
{
  /////////////////////////////////////////////////////
  /*
                             _
                            | |
    _ __ _   _ _ __    _ __ | |__   __ _ ___  ___
   | '__| | | | '_ \  | '_ \| '_ \ / _` / __|/ _ \
   | |  | |_| | | | | | |_) | | | | (_| \__ \  __/
   |_|   \__,_|_| |_| | .__/|_| |_|\__,_|___/\___|
                      | |
                      |_|
  run phase:
  checks if curve is detected and calls curve(L/R) function
  if no curve alligned to inner wall with fixxed distance
  runs until 12 curves are counted
  */
  /////////////////////////////////////////////////////

  // LanewithUTurn();

  while (corners < 12)
  {
    runLanesimple();
    runCurvesimple();
  }

  ////////////////////////////////////////////////////
  /*
                 _         _
                | |       | |
   ___ _ __   __| |  _ __ | |__   __ _ ___  ___
  / _ \ '_ \ / _` | | '_ \| '_ \ / _` / __|/ _ \
 |  __/ | | | (_| | | |_) | | | | (_| \__ \  __/
  \___|_| |_|\__,_| | .__/|_| |_|\__,_|___/\___|
                    | |
                    |_|
end phase:
stops car and shows counted time in milliseconds
Finish after 12 corners/curves
*/
  ////////////////////////////////////////////////////
  ProgramStopUsingGyro();
}