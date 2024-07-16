// RGB libraries
#include <Wire.h>
#include "rgb_lcd.h"


rgb_lcd lcd;

// Block variables
char P_color = 'U'; // Unknown
char P_wall_L = 'N';
char P_wall_R = 'N';
int P_x = 0;
int P_height = 0;


#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\raspi.h"
#include "C:\Users\WRO_FE2\Desktop\GSG_SmartiecarV2\src\ino\smartiecar_libs\cam.h"


int counter = 0;
unsigned long start_time;
unsigned long delta_time;
float update_freq;

//setup dcmotor and servo in the void setup() and drive straight
void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);
  lcd.print("raspi comm test");
  
   // raspi handshake
  raspi_handshake();
  delay(2000);
  lcd.clear();
  lcd.setRGB(255,255,255);

  counter = 0;
  start_time = millis();
  delta_time = 0;
  update_freq = 0.0;

}

//empty loop because everything is done is the setup
void loop()
{
 while (counter < 50)
 {
    findNextPillar();
    if (P_color == 'R')
    {
      lcd.setRGB(255,0,0);
    }
    else if (P_color == 'G')
    {
      lcd.setRGB(0,255,0);
    }
    else
    {
      lcd.setRGB(255,255,255);
    }
    lcd.setCursor(0,0);
    lcd.print(P_color);
    lcd.print(" ");
    lcd.print(P_x);
    lcd.print(" ");
    lcd.print(P_height);
    lcd.print("      ");
    counter = counter + 1;
  }
  delta_time = millis() - start_time;
  update_freq = counter * 1000.0/delta_time;

  lcd.clear();
  lcd.print(update_freq);
  delay(9999999999);

}