#include "Servo.h"

#define SERVO1_PIN 9

#define MIN_MS 550
#define MAX_MS 2400

#define DEFAULT_MS 1475 //90 degrees

int servoPulse = DEFAULT_MS;

Servo Servo1;

void setup()
{
  Servo1.attach(SERVO1_PIN);
  Servo1.writeMicroseconds(DEFAULT_MS);
}

void loop()
{
  // goes up to 180 degrees
  graduallyApplyServoPulse(MAX_MS);
  delay(1000);

  // return to 0 degrees
  graduallyApplyServoPulse(MIN_MS);
  delay(1000);
}

void graduallyApplyServoPulse(int pulse)
{
  int limitedPulse = limitServoPulse(pulse);

  while (servoPulse != limitedPulse) {
    if (servoPulse > limitedPulse) {
      servoPulse--;
    }

    if (servoPulse < limitedPulse) {
      servoPulse++;
    }

    Servo1.writeMicroseconds(servoPulse);
  }
}

int limitServoPulse(int pulse)
{
  return constrain(pulse, MIN_MS, MAX_MS);
}
