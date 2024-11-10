#ifndef motorControl_h
#define motorControl_h

#include <Arduino.h>

// Driver L298 pins for right and left motors
const int frontRightMotorIn1 = 2;
const int frontRightMotorIn2 = 4;
const int backRightMotorIn3 = 17;
const int backRightMotorIn4 = 18;
const int backLeftMotorIn1 = 13;
const int backLeftMotorIn2 = 14;
const int frontLeftMotorIn3 = 15;
const int frontLeftMotorIn4 = 16;

// Motor speed and LED configuration
const int speedMotors = 75;
const int freq = 5000;
const int resolution = 8;




class MotorControl {
public:
  void begin();
  void stop();
  void forward();
  void backward();
  void right();
  void left();
  void testFunction();
  void speed(int leftSpeed, int rightSpeed);
private:
  void attachMotors();
};

#endif

// Creat by Behshad Norouzi Azad - Email: behshad.azad@gmail.com