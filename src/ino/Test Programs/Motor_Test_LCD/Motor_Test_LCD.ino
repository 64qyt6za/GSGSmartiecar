 #include <Wire.h>
 #include "CytronMotorDriver.h"
 #include "rgb_lcd.h"


// Configure the motor driver.
CytronMD motor(PWM_DIR, 5, 6);  // PWM = Pin 3, DIR = Pin 4.
int colorRed = 255;
 int colorGreen = 0;
 int colorBlue = 0;
 //LCD screen selbst
 rgb_lcd lcd;

// The setup routine runs once when you press reset.
void setup() {
   Serial.begin(9600);
   lcd.begin(16, 2);
  lcd.setRGB(255, 0, 0);
}


// The loop routine runs over and over again forever.
void loop() {
  Serial.println("Vorwärts");
  lcd.setCursor(0,0);
  lcd.print("Vorärts");
  for (int i=1;i<26;i++)
  {
    Serial.println(i*10);
    motor.setSpeed(i*10);  // Run forward at 50% speed.
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(i*10);
    delay(500);
  }

   

  Serial.println("Stop");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stop");
  motor.setSpeed(0);    // Stop.
  delay(2000);

  Serial.println("Rückwärts");
  for (int i=1;i<26;i++)
  {
    Serial.println(i*(-10));
    motor.setSpeed(i*(-10));  // Run forward at 50% speed.
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(i*(-10));
    delay(500);
  }

   

  motor.setSpeed(0);    // Stop.
  delay(2000);
}
