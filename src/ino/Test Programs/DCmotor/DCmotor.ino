#include "DCmotor.h"

// start the DC motor
void setup() 
{

    Serial.begin(9600);
    Serial.println("DC motor test!");
    motorsetup();

}


void loop() 
{
    //run motor forward full speed
    Serial.println("runmotor forward full speed");
    runMotor(255);
    delay(3000);

    //stop motor
    Serial.println("stop motor");
    stopMotor();
    delay(3000);

    //run motor backward full speed
    Serial.println("run motor backward full speed");
    runMotor_R(255);
    delay(3000);

    //stop motor
    Serial.println("stop motor");
    stopMotor();
    
}
