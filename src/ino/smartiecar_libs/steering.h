// servo library
#include <Servo.h>
//---------------------------------------------------------------

// servo pin
int Servopin = 3;
int centered = 70;

// create servo object
Servo servo;

//---------------------------------------------------------------

// Servo steering

// left steering
void right(int Angle)
{
  int P1;
  P1 = centered + Angle;
  servo.write(P1);
}

// right steering
void left(int Angle)
{
  int P2;
  P2 = centered - Angle;
  servo.write(P2);
}

// steering straight
void center()
{
  servo.write(centered);
}

// servo setup
void servosetup()
{
  servo.attach(Servopin);
  center();
}
