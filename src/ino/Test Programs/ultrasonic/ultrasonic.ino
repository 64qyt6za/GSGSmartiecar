#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\ultrasonic_urm09.h"
#include "rgb_lcd.h"

//create the lcd object
rgb_lcd lcd;

//setup the ultrasonic sensor
void setup()
{
    Serial.begin(9600);
    ultrasonicstart();
    lcd.begin(16,2);
    //set the color of the lcd
    lcd.setRGB(255,255,255);
}



//loop to print the distance for all three sensors
void loop()
{
    //distance definitions
    int Distance_Left = SpaceUltraSonicLeft();
    int Distance = SpaceUltraSonicFront();
    int Distance_Right = SpaceUltraSonicRight();

    //print all distances
    lcd.setCursor(0,0);
    lcd.print(Distance_Left);
    lcd.print("  ");
    lcd.print(Distance);
    lcd.print("  ");
    lcd.print(Distance_Right);
    lcd.print("  ");
}