// Runs the built-in motion check once after reset:
// forward, backward, spin right, spin left.

#include <MotorControl.h>

MotorControl motors;

void setup() {
  Serial.begin(115200);

  if (!motors.begin()) {
    Serial.println("LEDC attach failed, check pin assignment");
    return;
  }

  motors.testFunction();
  Serial.println("Test finished");
}

void loop() {}
