// MotorControl - 4WD drive control for ESP32 with two L298N motor drivers.
//
// Each motor uses two driver inputs. Direction is selected by which input
// carries the PWM signal; the other input is held low. Requires the
// Arduino-ESP32 core 3.x (pin-based LEDC API: ledcAttach / ledcWrite).
//
// Copyright (c) 2024 Behshad Norouzi Azad
// SPDX-License-Identifier: MIT

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

class MotorControl {
 public:
  // L298N input pins. Defaults match the original robot wiring.
  struct Pins {
    uint8_t frontRightIn1 = 2;
    uint8_t frontRightIn2 = 4;
    uint8_t backRightIn3 = 17;
    uint8_t backRightIn4 = 18;
    uint8_t backLeftIn1 = 13;
    uint8_t backLeftIn2 = 14;
    uint8_t frontLeftIn3 = 15;
    uint8_t frontLeftIn4 = 16;
  };

  static constexpr int kMaxSpeed = 255;      // 8-bit PWM resolution
  static constexpr uint8_t kDefaultSpeed = 75;
  static constexpr uint32_t kDefaultPwmFrequency = 5000;  // Hz

  MotorControl() = default;
  explicit MotorControl(const Pins& pins) : pins_(pins) {}

  // Attaches all eight pins to LEDC channels and stops the motors.
  // Returns false if any pin could not be attached.
  bool begin(uint32_t pwmFrequency = kDefaultPwmFrequency);

  void stop();
  void forward(uint8_t speed = kDefaultSpeed);
  void backward(uint8_t speed = kDefaultSpeed);
  void right(uint8_t speed = kDefaultSpeed);  // spin clockwise in place
  void left(uint8_t speed = kDefaultSpeed);   // spin counter-clockwise in place

  // Sets each side independently. Positive values drive forward, negative
  // values drive backward, range -255..255. Out-of-range input is rejected
  // (returns false) and the current motor state is left unchanged.
  bool speed(int leftSpeed, int rightSpeed);

  // Short motion check: forward, backward, spin right, spin left,
  // with a stop between each step. Blocks for about 12 s.
  void testFunction();

 private:
  static constexpr uint8_t kPwmResolutionBits = 8;

  static bool inRange(int value) { return value >= -kMaxSpeed && value <= kMaxSpeed; }
  static void driveMotor(uint8_t forwardPin, uint8_t reversePin, int speed);

  void driveRight(int speed);
  void driveLeft(int speed);

  Pins pins_;
};

#endif  // MOTOR_CONTROL_H
