// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "Servo.h"

#define SERVO_PAN_PIN 9
#define SERVO_TILT_PIN 10

#define MIN_ANGLE 0
#define MID_ANGLE 90
#define MAX_ANGLE 180

#define DEFAULT_PAN_ANGLE 0
#define DEFAULT_TILT_ANGLE 0

struct ServoMotion {
  Servo motor;
  int angle;
} pan, tilt;

void setup()
{
  // Attach servo pins
  pan.motor.attach(SERVO_PAN_PIN);
  tilt.motor.attach(SERVO_TILT_PIN);

  // Set default servo angles
  writeServoAngle(pan, DEFAULT_PAN_ANGLE);
  writeServoAngle(tilt, DEFAULT_TILT_ANGLE);
}

void loop()
{
  applyGraduallyServoAngle(pan, MIN_ANGLE);
  delay(1000);
  tiltRange();
  delay(1000);

  applyGraduallyServoAngle(pan, MID_ANGLE);
  delay(1000);
  tiltRange();
  delay(1000);

  applyGraduallyServoAngle(pan, MAX_ANGLE);
  delay(1000);
  tiltRange();
  delay(1000);
}

void tiltRange()
{
  applyGraduallyServoAngle(tilt, MAX_ANGLE);
  applyGraduallyServoAngle(tilt, MIN_ANGLE);
  delay(500);
}

void applyGraduallyServoAngle(ServoMotion &servo, int angle)
{
  int desiredAngle = limitServoAngle(angle);
  int currentAngle = servo.angle;

  while (currentAngle != desiredAngle) {
    if (currentAngle > desiredAngle) {
      currentAngle--;
    } else if (currentAngle < desiredAngle) {
      currentAngle++;
    }

    writeServoAngle(servo, currentAngle);

    delay(10); // Wait 10ms for the servo to reach the position
  }
}

void writeServoAngle(ServoMotion &servo, int angle)
{
  servo.angle = angle;
  servo.motor.write(servo.angle);
}

int limitServoAngle(int angle)
{
  return constrain(angle, MIN_ANGLE, MAX_ANGLE);
}
