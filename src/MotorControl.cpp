// Copyright (c) 2024 Behshad Norouzi Azad
// SPDX-License-Identifier: MIT

#include "MotorControl.h"

bool MotorControl::begin(uint32_t pwmFrequency) {
  const uint8_t pins[] = {
      pins_.frontRightIn1, pins_.frontRightIn2, pins_.backRightIn3, pins_.backRightIn4,
      pins_.backLeftIn1,   pins_.backLeftIn2,   pins_.frontLeftIn3, pins_.frontLeftIn4,
  };

  bool ok = true;
  for (uint8_t pin : pins) {
    ok &= ledcAttach(pin, pwmFrequency, kPwmResolutionBits);
  }

  stop();
  return ok;
}

void MotorControl::stop() {
  driveRight(0);
  driveLeft(0);
}

void MotorControl::forward(uint8_t speed) {
  driveRight(speed);
  driveLeft(speed);
}

void MotorControl::backward(uint8_t speed) {
  driveRight(-speed);
  driveLeft(-speed);
}

void MotorControl::right(uint8_t speed) {
  driveRight(-speed);
  driveLeft(speed);
}

void MotorControl::left(uint8_t speed) {
  driveRight(speed);
  driveLeft(-speed);
}

bool MotorControl::speed(int leftSpeed, int rightSpeed) {
  if (!inRange(leftSpeed) || !inRange(rightSpeed)) {
    return false;
  }
  driveRight(rightSpeed);
  driveLeft(leftSpeed);
  return true;
}

void MotorControl::testFunction() {
  const int s = 100;
  const int steps[][2] = {{s, s}, {-s, -s}, {s, -s}, {-s, s}};  // {left, right}

  stop();
  for (const auto& step : steps) {
    delay(2000);
    speed(step[0], step[1]);
    delay(1000);
    stop();
  }
}

void MotorControl::driveMotor(uint8_t forwardPin, uint8_t reversePin, int speed) {
  if (speed >= 0) {
    ledcWrite(reversePin, 0);
    ledcWrite(forwardPin, speed);
  } else {
    ledcWrite(forwardPin, 0);
    ledcWrite(reversePin, -speed);
  }
}

// Forward inputs follow the robot wiring: IN2/IN4 on the right side,
// IN1/IN3 on the left side (the two sides face opposite directions).
void MotorControl::driveRight(int speed) {
  driveMotor(pins_.frontRightIn2, pins_.frontRightIn1, speed);
  driveMotor(pins_.backRightIn4, pins_.backRightIn3, speed);
}

void MotorControl::driveLeft(int speed) {
  driveMotor(pins_.backLeftIn1, pins_.backLeftIn2, speed);
  driveMotor(pins_.frontLeftIn3, pins_.frontLeftIn4, speed);
}
