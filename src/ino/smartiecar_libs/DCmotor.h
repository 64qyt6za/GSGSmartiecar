// DC Motor 1
int GSM1 = 5;
int in1 = 6;
int in2 = 7;

// backward
void runMotor_R(int Speed)
{
  int tmpSpeed;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  if (Speed < 185)
  {
    tmpSpeed = 185;
    analogWrite(GSM1, Speed);
    delay(100);
  }
  analogWrite(GSM1, Speed);
}

// stop
void stopMotor()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(GSM1, 0);
  // active breaking then stop
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(GSM1, 185);
  delay(50);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(GSM1, 0);
}

// run motor
void runMotor(int Speed)
{
  int tmpSpeed;
  digitalWrite(in1, HIGH); // motor 1 begins to rotate forward
  digitalWrite(in2, LOW);
  if (Speed < 185)
  {
    tmpSpeed = 185;
    analogWrite(GSM1, Speed); // motor 1 should drive forward with the maximum speed
    delay(100);
  }
  analogWrite(GSM1, Speed);
}

void motorsetup()
{
  // pinmodes motor
  pinMode(GSM1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}