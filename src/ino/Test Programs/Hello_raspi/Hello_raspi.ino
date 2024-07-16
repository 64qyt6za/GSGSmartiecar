#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);
  lcd.setCursor(0,0);
  lcd.print("Wait for Raspi");
  Serial.print("ready");
  delay(1000);

}
void loop() 
{
  if (Serial.available() > 0) {
    lcd.clear();
    lcd.setRGB(255, 255, 255);
    String data = Serial.readStringUntil('\n');
    lcd.setCursor(0,0);
    lcd.print(data);
    data = "";
    Serial.print("go");
  }
}