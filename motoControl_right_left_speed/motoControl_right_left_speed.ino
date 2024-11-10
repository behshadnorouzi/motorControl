#include "src/motorControl.h"

MotorControl motor;

void setup() {
  motor.begin();
  //motor.speed(left,right);
  motor.testFunction();
  motor.speed(150, 400);
}

void loop() {
}
