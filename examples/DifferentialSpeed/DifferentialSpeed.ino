// Drives the left and right sides at different speeds to follow an arc,
// and shows how out-of-range commands are rejected.

#include <MotorControl.h>

MotorControl motors;

void setup() {
  Serial.begin(115200);

  if (!motors.begin()) {
    Serial.println("LEDC attach failed, check pin assignment");
    return;
  }

  motors.speed(150, 90);  // left faster than right: wide right turn
  delay(2000);
  motors.speed(-120, -120);  // straight back
  delay(1000);
  motors.stop();

  if (!motors.speed(150, 400)) {
    Serial.println("Rejected: speed must be within -255..255");
  }
}

void loop() {}
