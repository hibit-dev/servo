#include "Servo.h"

#define SERVO1_PIN 9

#define MIN_ANGLE 0
#define MAX_ANGLE 180

#define DEFAULT_ANGLE 90

int servoAngle = DEFAULT_ANGLE;

Servo Servo1;

void setup()
{
  Servo1.attach(SERVO1_PIN);
  Servo1.write(DEFAULT_ANGLE);
}

void loop()
{
  // goes up to 180 degrees
  graduallyApplyServoAngle(MAX_ANGLE);
  delay(1000);

  // return to 0 degrees
  graduallyApplyServoAngle(MIN_ANGLE);
  delay(1000);
}

void graduallyApplyServoAngle(int angle)
{
  int limitedAngle = limitServoAngle(angle);

  while (servoAngle != limitedAngle) {
    if (servoAngle > limitedAngle) {
      servoAngle--;
    }

    if (servoAngle < limitedAngle) {
      servoAngle++;
    }

    Servo1.write(servoAngle);

    delay(5);
  }
}

int limitServoAngle(int angle)
{
  return constrain(angle, MIN_ANGLE, MAX_ANGLE);
}
