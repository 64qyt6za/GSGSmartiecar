// The ultrasonic velocity (cm/us) compensated by temperature
#define VELOCITY_TEMP(temp) ((331.5 + 0.6 * (float)(temp)) * 100 / 1000000.0)

// US sensor pin definiton
#define trigechoPin_F A1

#define trigechoPin_L A2

#define trigechoPin_R A0

uint16_t distance;

uint32_t pulseWidthUs;

int16_t dist_Left = 0;
int16_t dist_Right = 0;
int16_t dist_Front = 0;

int SpaceUltraSonicFront()
{
        // Sending the trigger pulse
        int16_t dist, temp;
        dist = 0;

        pinMode(trigechoPin_F, OUTPUT);
        digitalWrite(trigechoPin_F, LOW);
        delayMicroseconds(2);
        digitalWrite(trigechoPin_F, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigechoPin_F, LOW);
        // wait for echo pin to go high
        pinMode(trigechoPin_F, INPUT);
        pulseWidthUs = pulseIn(trigechoPin_F, HIGH);
        dist = pulseWidthUs * VELOCITY_TEMP(20) / 2.0;

        if ((dist < 2) || (dist > 350))
        {
                dist = dist_Front;
        }

        else
        {
                dist_Front = dist;
        }
        delay(20);
        // gives back as an integer in cm
        return int(dist);
}

int SpaceUltraSonicLeft()
{
        // Sending the trigger pulse
        int16_t dist, temp;
        dist = 0;

        pinMode(trigechoPin_L, OUTPUT);
        digitalWrite(trigechoPin_L, LOW);
        delayMicroseconds(2);
        digitalWrite(trigechoPin_L, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigechoPin_L, LOW);
        // wait for echo pin to go high
        pinMode(trigechoPin_L, INPUT);
        pulseWidthUs = pulseIn(trigechoPin_L, HIGH);
        dist = pulseWidthUs * VELOCITY_TEMP(20) / 2.0;

        if ((dist < 2) || (dist > 350))
        {
                dist = dist_Left;
        }

        else
        {
                dist_Left = dist;
        }
        delay(20);
        // gives back as an integer in cm
        return int(dist);
}

int SpaceUltraSonicRight()
{
        // Sending the trigger pulse
        int16_t dist, temp;
        dist = 0;

        pinMode(trigechoPin_R, OUTPUT);
        digitalWrite(trigechoPin_R, LOW);
        delayMicroseconds(2);
        digitalWrite(trigechoPin_R, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigechoPin_R, LOW);
        // wait for echo pin to go high
        pinMode(trigechoPin_R, INPUT);
        pulseWidthUs = pulseIn(trigechoPin_R, HIGH);
        dist = pulseWidthUs * VELOCITY_TEMP(20) / 2.0;

        if ((dist < 2) || (dist > 350))
        {
                dist = dist_Right;
        }

        else
        {
                dist_Right = dist;
        }
        delay(20);
        // gives back as an integer in cm
        return int(dist);
}

// empty for sensor type compatibility
void ultrasonicstart()
{
        return;
}