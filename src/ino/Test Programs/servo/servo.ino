#include <Servo.h>
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\steering.h"

unsigned long start_time;

void setup() 
{
  servosetup();
}

void loop() 
{
  //write servo to center
  center();
  delay(3000);

  //write servo to left
  left(40);
  delay(3000);

  //write servo to right
  right(40);
  delay(3000);


}
