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

//--------------------------------------------

// Servo section libraries
#include <Servo.h>
//-------------------------------------------------

// RGB libraries
#include <Wire.h>
#include "rgb_lcd.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 ██████╗ ██╗      ██████╗ ██████╗  █████╗ ██╗         ██╗   ██╗ █████╗ ██████╗ ██╗ █████╗ ██████╗ ██╗     ███████╗███████╗
██╔════╝ ██║     ██╔═══██╗██╔══██╗██╔══██╗██║         ██║   ██║██╔══██╗██╔══██╗██║██╔══██╗██╔══██╗██║     ██╔════╝██╔════╝
██║  ███╗██║     ██║   ██║██████╔╝███████║██║         ██║   ██║███████║██████╔╝██║███████║██████╔╝██║     █████╗  ███████╗
██║   ██║██║     ██║   ██║██╔══██╗██╔══██║██║         ╚██╗ ██╔╝██╔══██║██╔══██╗██║██╔══██║██╔══██╗██║     ██╔══╝  ╚════██║
╚██████╔╝███████╗╚██████╔╝██████╔╝██║  ██║███████╗     ╚████╔╝ ██║  ██║██║  ██║██║██║  ██║██████╔╝███████╗███████╗███████║
 ╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝╚══════╝
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// timer
unsigned long start_time;
//--------------------------------------------------

// speeds
int NormalSpeed = 190;
int SlowSpeed = 100;
int CurveSpeed = 160;
int StartSpeed = 110;

// LCD connection
int Button = 4;
int colorRed = 255;
int colorGreen = 0;
int colorBlue = 0;
// LCD screen itself
rgb_lcd lcd;

// laps corners and quadrant
int corners = 0;
int laps = 0;
int quadrant = 0;

// Distances own funcs (calculate values)
int Distance_Front;
int Distance_Left;
int Distance_Right;

// floats for gyro
float angle;
float danger;
float correction_Left = 30.0;
float correction_Right = 30.0;
float StraightAngle = 0.0;

// DrivingDirection is 'U' for Unknown
char DrivingDirection = 'U';

// last curve measured
unsigned long LastCurveTime = 0;
unsigned long NextCurveDelay = 2000;

// used for both Driving Directions (left and right)
int Walldistance = 30;

// include own modules from local library
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\DCmotor.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\gyro2.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\steering.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\ultrasonic_urm09.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\raspi.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 ██████╗ ██╗    ██╗███╗   ██╗    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
██╔═══██╗██║    ██║████╗  ██║    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
██║   ██║██║ █╗ ██║██╔██╗ ██║    █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
██║   ██║██║███╗██║██║╚██╗██║    ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
╚██████╔╝╚███╔███╔╝██║ ╚████║    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
 ╚═════╝  ╚══╝╚══╝ ╚═╝  ╚═══╝    ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////

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

  // Go straight for at least x msec
  Gyro_steer_straight();
  temporaryTime = millis();
  while (millis() < temporaryTime + 1200)
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

/////////////////////////////////////////////////////////////////////
// StartNarrow_L()
// startnarrow Left (start close to left inside wall)
/////////////////////////////////////////////////////////////////////
void StartNarrow_L()
{
  float angle;
  float TargetDirection = 360.0;
  int Speed = SlowSpeed;
  right(30);
  delay(500);
  center();
  delay(500);
  angle = IMU_getAngle();
  lcd.setCursor(0, 0);
  lcd.print(angle);
  left(30);
  while (angle > TargetDirection + correction_Left)
  {

    angle = IMU_getAngle();
    Speed = Speed + 5;
    if (Speed > CurveSpeed)
    {
      Speed = CurveSpeed;
    }
    runMotor(Speed);
    delay(50);
  }
  center();
  runMotor(SlowSpeed);
}
/////////////////////////////////////////////////////////////////////
// StartNarrow_R()
// startnarrow Right (start close to right inside wall)
/////////////////////////////////////////////////////////////////////
void StartNarrow_R()
{
  float angle;
  float TargetDirection = 0.0;
  int Speed;
  left(30);
  delay(500);
  center();
  delay(500);
  angle = IMU_getAngle();
  lcd.setCursor(0, 0);
  lcd.print(angle);
  right(30);
  while (angle < TargetDirection - correction_Right)
  {

    angle = IMU_getAngle();
    Speed = Speed + 5;
    if (Speed > CurveSpeed)
    {
      Speed = CurveSpeed;
    }
    runMotor(Speed);
    delay(50);
  }
  center();
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
  Steering = (Distance_Left - Walldistance) * 0.9;
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

  Steering = (Walldistance - Distance_Right) * 0.9;
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
// Curve_L()
// calls a left curve and counts it
/////////////////////////////////////////////////////////////////////
void Curve_L()
{
  int Speed;
  float TargetDirection;
  Speed = CurveSpeed;
  left(40);
  lcd.setRGB(0, 0, 255);
  TargetDirection = StraightAngle - 90.0;
  angle = IMU_getAngle();
  StraightAngle = TargetDirection;
  runMotor(SlowSpeed);
  while (angle > TargetDirection + correction_Left)
  {
    angle = IMU_getAngle();
    Speed = Speed + 5;
    if (Speed > CurveSpeed)
    {
      Speed = CurveSpeed;
    }
    runMotor(Speed);
    delay(50);
  }

  corners = corners + 1;
  StraightAngle = TargetDirection;
  center();
  runMotor(NormalSpeed);
  Distance_Left = SpaceUltraSonicLeft;

  // try to find the inside wall again
  while (Distance_Left > 60)
  {
    Distance_Left = SpaceUltraSonicLeft();
    Gyro_steer_straight();
  }
  lcd.setRGB(0, 255, 0);
  LastCurveTime = millis();
}

/////////////////////////////////////////////////////////////////////
// Curve_R()
// calls a right curve and counts it
/////////////////////////////////////////////////////////////////////
void Curve_R()
{
  int Speed;
  float TargetDirection;
  Speed = CurveSpeed;
  right(40);
  lcd.setRGB(0, 0, 255);
  TargetDirection = StraightAngle + 90.0;
  angle = IMU_getAngle();
  StraightAngle = TargetDirection;
  runMotor(SlowSpeed);
  // checks if the car has a greater angle than the target direction in order to correct it
  while (angle < TargetDirection - correction_Right)
  {
    angle = IMU_getAngle();
    Speed = Speed + 5;
    if (Speed > CurveSpeed)
    {
      Speed = CurveSpeed;
    }
    runMotor(Speed);
    delay(50);
  }

  corners = corners + 1;
  StraightAngle = TargetDirection;
  center();
  runMotor(NormalSpeed);
  Distance_Right = SpaceUltraSonicRight;

  // try to find the inside wall again
  while (Distance_Right > 60)
  {
    Distance_Right = SpaceUltraSonicRight();
    Gyro_steer_straight();
  }
  lcd.setRGB(0, 255, 0);
  LastCurveTime = millis();
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
void printAllDistancesToLCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Distance_Left);
  lcd.print("  ");
  lcd.print(Distance_Front);
  lcd.print("  ");
  lcd.print(Distance_Right);
  lcd.setCursor(0, 1);
  lcd.print(StraightAngle);
  lcd.print("  ");
  lcd.print(DrivingDirection);
}

/////////////////////////////////////////////////////////////////////
// waitOnButtonPress()
// waits until the button is pressed
/////////////////////////////////////////////////////////////////////
void waitOnButtonPress()
{
  while (digitalRead(Button) == LOW)
  {
    delay(50);
  }
}

/////////////////////////////////////////////////////////////////////
// slowspeedToFindCorrectDirection()
// finds the driving direction slowly while measuring the distances
/////////////////////////////////////////////////////////////////////
void slowspeedToFindCorrectDirection()
{
  if (DrivingDirection == 'U')
  {
    runMotor(SlowSpeed);
    while ((Distance_Left < 80.0) && (Distance_Right < 80.0))
    {
      Distance_Left = SpaceUltraSonicLeft();
      Distance_Right = SpaceUltraSonicRight();
      Gyro_steer_straight();
    }
    if (Distance_Left >= 80.0)
    {
      DrivingDirection = 'L';
      Curve_L();
    }
    else if (Distance_Right >= 80.0)
    {
      DrivingDirection = 'R';
      Curve_R();
    }
  }

  else if (DrivingDirection == 'R')
  {
    runMotor(SlowSpeed);
    delay(100);
    StartNarrow_R();
    Distance_Right = SpaceUltraSonicRight();
    while (Distance_Right < 80.0)
    {
      Distance_Right = SpaceUltraSonicRight();
      Gyro_steer_straight();
    }
    Curve_R();
  }

  else if (DrivingDirection == 'L')
  {
    runMotor(SlowSpeed);
    delay(100);
    StartNarrow_L();
    Distance_Left = SpaceUltraSonicLeft();
    while (Distance_Left < 80.0)
    {
      Distance_Left = SpaceUltraSonicLeft();
      Gyro_steer_straight();
    }
    Curve_L();
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

/////////////////////////////////////////////////////////////////////
// wallDirectionCheck()
// checks if the car is closer to the left or right wall
/////////////////////////////////////////////////////////////////////
void wallDirectionCheck()
{
  if (Distance_Left < 10)
  {
    DrivingDirection = 'L';
  }

  if (Distance_Right < 10)
  {
    DrivingDirection = 'R';
  }
}

/////////////////////////////////////////////////////////////////////
// operateNavigationThroughTurns()
// uses the gyro to navigate through the turns while counting corners
/////////////////////////////////////////////////////////////////////
void operateNavigationThroughTurns()
{
  if (DrivingDirection == 'R')
  {
    while (corners < 12)
    {
      // clockwise running for right
      Distance_Right = SpaceUltraSonicRight();

      // check for Right Turn
      if ((Distance_Right > 80) && (millis() - LastCurveTime >= NextCurveDelay))
      {
        Curve_R();
      }
      else
      {
        alignRight();
      }
    }
  }

  else
  {
    while (corners < 12)
    {

      // counterclockwise running for left
      Distance_Left = SpaceUltraSonicLeft();
      // check for Left Turn
      if ((Distance_Left > 80) && (millis() - LastCurveTime >= NextCurveDelay))
      {
        Curve_L();
      }
      else
      {
        alignLeft();
      }
    }
  }
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

  // LCD SETUP
  pinMode(Button, INPUT); // Button

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);
  lcd.print("Opening race");

  // setup servo
  servosetup();

  delay(5000); // 5 second stop in order for the gyro to calibrate

  // setup gyroscope
  startGyroscope();

  // initalises motor pinmodes from DCmotor.h
  motorsetup();

  // enable raspi handshake
  raspi_handshake();

  // measures all the current reading values
  measureAllCurrentDistances();

  // checks which wall the car is starting from
  wallDirectionCheck();

  // set the straightangle to the current IMU angle
  StraightAngle = IMU_getAngle();

  // gets all distances and prints them
  printAllDistancesToLCD();

  // setup done - show green light
  lcd.setRGB(255, 130, 0);

  // wait for button press
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

  // lcd green
  lcd.setRGB(0, 255, 0);

  saveCurrentTime();

  // Steering to center
  center();

  // drive slow to find the correct DrivingDirection
  slowspeedToFindCorrectDirection();
}

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

  operateNavigationThroughTurns();

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
*/
  ////////////////////////////////////////////////////

  ProgramStopUsingGyro();
}