// MotorControl.cpp
#include "MotorControl.h"

const int defaultSpeed = 100;

void MotorControl::begin() {
  attachMotors();
  stop();
  delay(1000);
}

void MotorControl::attachMotors() {
  // Attach pins with frequency and resolution
  ledcAttach(frontRightMotorIn1, freq, resolution);
  ledcAttach(frontRightMotorIn2, freq, resolution);
  ledcAttach(backRightMotorIn3, freq, resolution);
  ledcAttach(backRightMotorIn4, freq, resolution);
  ledcAttach(backLeftMotorIn1, freq, resolution);
  ledcAttach(backLeftMotorIn2, freq, resolution);
  ledcAttach(frontLeftMotorIn3, freq, resolution);
  ledcAttach(frontLeftMotorIn4, freq, resolution);
}

void MotorControl::stop() {
  ledcWrite(frontRightMotorIn1, LOW);
  ledcWrite(frontRightMotorIn2, LOW);
  ledcWrite(backRightMotorIn3, LOW);
  ledcWrite(backRightMotorIn4, LOW);
  ledcWrite(backLeftMotorIn1, LOW);
  ledcWrite(backLeftMotorIn2, LOW);
  ledcWrite(frontLeftMotorIn3, LOW);
  ledcWrite(frontLeftMotorIn4, LOW);
}

void MotorControl::forward() {
  ledcWrite(frontRightMotorIn1, LOW);
  ledcWrite(frontRightMotorIn2, speedMotors);
  ledcWrite(backRightMotorIn3, LOW);
  ledcWrite(backRightMotorIn4, speedMotors);
  ledcWrite(backLeftMotorIn1, speedMotors);
  ledcWrite(backLeftMotorIn2, LOW);
  ledcWrite(frontLeftMotorIn3, speedMotors);
  ledcWrite(frontLeftMotorIn4, LOW);
}

void MotorControl::backward() {
  ledcWrite(frontRightMotorIn1, speedMotors);
  ledcWrite(frontRightMotorIn2, LOW);
  ledcWrite(backRightMotorIn3, speedMotors);
  ledcWrite(backRightMotorIn4, LOW);
  ledcWrite(backLeftMotorIn1, LOW);
  ledcWrite(backLeftMotorIn2, speedMotors);
  ledcWrite(frontLeftMotorIn3, LOW);
  ledcWrite(frontLeftMotorIn4, speedMotors);
}

void MotorControl::right() {
  ledcWrite(frontRightMotorIn1, LOW);
  ledcWrite(frontRightMotorIn2, speedMotors);
  ledcWrite(backRightMotorIn3, LOW);
  ledcWrite(backRightMotorIn4, speedMotors);
  ledcWrite(backLeftMotorIn1, LOW);
  ledcWrite(backLeftMotorIn2, speedMotors);
  ledcWrite(frontLeftMotorIn3, LOW);
  ledcWrite(frontLeftMotorIn4, speedMotors);
}

void MotorControl::left() {
  ledcWrite(frontRightMotorIn1, speedMotors);
  ledcWrite(frontRightMotorIn2, LOW);
  ledcWrite(backRightMotorIn3, speedMotors);
  ledcWrite(backRightMotorIn4, LOW);
  ledcWrite(backLeftMotorIn1, speedMotors);
  ledcWrite(backLeftMotorIn2, LOW);
  ledcWrite(frontLeftMotorIn3, speedMotors);
  ledcWrite(frontLeftMotorIn4, LOW);
}

void MotorControl::testFunction() {
  stop();
  delay(2000);
  speed(defaultSpeed, defaultSpeed);
  delay(1000);
  stop();
  delay(2000);
  speed(-defaultSpeed, -defaultSpeed);
  delay(1000);
  stop();
  delay(2000);
  speed(defaultSpeed, -defaultSpeed);
  delay(1000);
  stop();
  delay(2000);
  speed(-defaultSpeed, defaultSpeed);
  delay(1000);
  stop();
}

void MotorControl::speed(int leftSpeed, int rightSpeed) {
  //Backward
  if ((leftSpeed > 255 || leftSpeed < -255) && (rightSpeed > 255 || rightSpeed < -255)) {
    Serial.println("Error: leftSpeed and right speed out of range, It should be between -255 and 255.");
  } else if (rightSpeed > 255 || rightSpeed < -255) {
    Serial.println("Error: rightSpeed out of range, It should be between -255 and 255.");
  } else if (leftSpeed > 255 || leftSpeed < -255) {
    Serial.println("Error: leftSpeed out of range, It should be between -255 and 255.");
  } else if (leftSpeed > 255 || leftSpeed < -255 && abs(rightSpeed) <= 255) {
    Serial.println("Error: leftSpeed out of range, It should be between -255 and 255.");
  } else if (rightSpeed > 255 || rightSpeed < -255 && abs(leftSpeed) <= 255) {
    Serial.println("Error: rightSpeed out of range, It should be between -255 and 255.");
  }

  else if (abs(rightSpeed) <= 255 && abs(leftSpeed) <= 255) {
    if (rightSpeed < 0 && leftSpeed < 0) {
      ledcWrite(frontRightMotorIn1, map(-rightSpeed, 0, 255, 0, 255));
      ledcWrite(frontRightMotorIn2, LOW);
      ledcWrite(backRightMotorIn3, map(-rightSpeed, 0, 255, 0, 255));
      ledcWrite(backRightMotorIn4, LOW);
      ledcWrite(backLeftMotorIn1, LOW);
      ledcWrite(backLeftMotorIn2, map(-leftSpeed, 0, 255, 0, 255));
      ledcWrite(frontLeftMotorIn3, LOW);
      ledcWrite(frontLeftMotorIn4, map(-leftSpeed, 0, 255, 0, 255));
    }
    //Forward
    else if (rightSpeed >= 0 && leftSpeed >= 0) {
      ledcWrite(frontRightMotorIn1, LOW);
      ledcWrite(frontRightMotorIn2, rightSpeed);
      ledcWrite(backRightMotorIn3, LOW);
      ledcWrite(backRightMotorIn4, rightSpeed);
      ledcWrite(backLeftMotorIn1, leftSpeed);
      ledcWrite(backLeftMotorIn2, LOW);
      ledcWrite(frontLeftMotorIn3, leftSpeed);
      ledcWrite(frontLeftMotorIn4, LOW);
    }
    //Left
    else if (rightSpeed >= 0 && leftSpeed < 0) {
      ledcWrite(frontRightMotorIn1, LOW);
      ledcWrite(frontRightMotorIn2, rightSpeed);
      ledcWrite(backRightMotorIn3, LOW);
      ledcWrite(backRightMotorIn4, rightSpeed);
      ledcWrite(backLeftMotorIn1, LOW);
      ledcWrite(backLeftMotorIn2, map(-leftSpeed, 0, 255, 0, 255));
      ledcWrite(frontLeftMotorIn3, LOW);
      ledcWrite(frontLeftMotorIn4, map(-leftSpeed, 0, 255, 0, 255));
    }
    //Right
    else if (rightSpeed < 0 && leftSpeed >= 0) {
      ledcWrite(frontRightMotorIn1, map(-rightSpeed, 0, 255, 0, 255));
      ledcWrite(frontRightMotorIn2, LOW);
      ledcWrite(backRightMotorIn3, map(-rightSpeed, 0, 255, 0, 255));
      ledcWrite(backRightMotorIn4, LOW);
      ledcWrite(backLeftMotorIn1, leftSpeed);
      ledcWrite(backLeftMotorIn2, LOW);
      ledcWrite(frontLeftMotorIn3, leftSpeed);
      ledcWrite(frontLeftMotorIn4, LOW);
    } else if (rightSpeed == 0 && leftSpeed == 0) {
      stop();
    }

  } else {
    Serial.println("Please enter an int value and check that each side's motor has speed!");
  }
}

// Creat by Behshad Norouzi Azad - Email: behshad.azad@gmail.com