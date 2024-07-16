// includes
#include "rgb_lcd.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (10)

// gyroscope
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
sensors_event_t event;

static float save_orientation = 0.0;
static float total_turn = 0.0;

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
██╗███╗   ███╗██╗   ██╗    ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
██║████╗ ████║██║   ██║    ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
██║██╔████╔██║██║   ██║    █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
██║██║╚██╔╝██║██║   ██║    ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
██║██║ ╚═╝ ██║╚██████╔╝    ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
╚═╝╚═╝     ╚═╝ ╚═════╝     ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////

byte IMU_start()
{
  if (!bno.begin())
  {
    lcd.setCursor(0, 0);
    lcd.print("IMU ERR!");
    while (1)
      ;
  }
  return 0;
}

void IMU_calibrate()
{
  uint8_t system, gyroscope, accel, mag;
  system = gyroscope = accel = mag = 0;
  bno.getCalibration(&system, &gyroscope, &accel, &mag);

  // Operation mode IMUPLUS switches magnetometer off
  // Result: Initial orientation at startup is always 0
  bno.setMode(OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
}

void IMU_calculate()
{

  float orientation = 0.0;
  float orientation_change = 0.0;

  bno.getEvent(&event);
  orientation = event.orientation.x;

  // calculate orientation as -180.0 to +180.0
  if (orientation > 180.0)
  {
    orientation = orientation - 360.0;
  }

  orientation_change = orientation - save_orientation;
  if (orientation_change > 180.0)
  {
    orientation_change = orientation_change - 360.0;
  }
  else if (orientation_change < -180.0)
  {
    orientation_change = orientation_change + 360.0;
  }

  // save orientation and total turn
  save_orientation = orientation;
  total_turn = total_turn + orientation_change;

  return;
}

// returns orientation in degrees
float IMU_getOrientation()
{
  float angle;
  IMU_calculate();
  angle = save_orientation;
  return angle;
}

// gets total turn in degrees
float IMU_getAngle()
{
  float angle;
  IMU_calculate();
  angle = total_turn;
  return angle;
}

// setup the gyroscope
void startGyroscope()
{
  byte status = IMU_start();
  while (status != 0)
  {
    delay(10);
  }                // stop everything if could not connect to BNO055
  IMU_calibrate(); // gyroscope and accelerometer
}
