#include "motor_controller.h"

int IN1 = D1;
int IN2 = D2;
int ENA = D0;

int IN3 = D5;
int IN4 = D4;
int ENB = D3;

const int MOTOR_STOP = 0;
const int MOTOR_FORWARD = 1;
const int MOTOR_BACKWARD = 2;
const int MIN_SPEED = 110;
const int MAX_SPEED = 255;

int SPEED = MIN_SPEED;

int LEFT_MOTOR_STATE = MOTOR_STOP;
int RIGHT_MOTOR_STATE = MOTOR_STOP;

void setupMotorController() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  stopMovement();
}

void spinLeftMotor() {
  if (LEFT_MOTOR_STATE == MOTOR_FORWARD) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, SPEED);
  }
  else if (LEFT_MOTOR_STATE == MOTOR_BACKWARD) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, SPEED);
  }
  else {
    stopLeftMotor();
  }
}

void setForwardLeftMotor(int newSpeed) {
  LEFT_MOTOR_STATE = MOTOR_FORWARD;
  setSpeed(newSpeed);
}

void setBackwardLeftMotor(int newSpeed) {
  LEFT_MOTOR_STATE = MOTOR_BACKWARD;
  setSpeed(newSpeed);
}

void spinRightMotor() {
  if (RIGHT_MOTOR_STATE == MOTOR_FORWARD) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, SPEED);
  }
  else if (RIGHT_MOTOR_STATE == MOTOR_BACKWARD) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, SPEED);
  }
  else {
    stopRightMotor();
  }
}

void setForwardRightMotor(int newSpeed) {
  RIGHT_MOTOR_STATE = MOTOR_FORWARD;
  setSpeed(newSpeed);
}

void setBackwardRightMotor(int newSpeed) {
  RIGHT_MOTOR_STATE = MOTOR_BACKWARD;
  setSpeed(newSpeed);
}

void stopLeftMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  LEFT_MOTOR_STATE = MOTOR_STOP;
}

void stopRightMotor() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  RIGHT_MOTOR_STATE = MOTOR_STOP;
}

void stopMovement() {
  stopLeftMotor();
  stopRightMotor();
  setSpeed(MIN_SPEED);
}

void setMoveForward(int newSpeed) {
  LEFT_MOTOR_STATE = MOTOR_FORWARD;
  RIGHT_MOTOR_STATE = MOTOR_FORWARD;
  setSpeed(newSpeed);
}

void setMoveBackward(int newSpeed) {
  LEFT_MOTOR_STATE = MOTOR_BACKWARD;
  RIGHT_MOTOR_STATE = MOTOR_BACKWARD;
  setSpeed(newSpeed);
}

void setTurnLeft(int newSpeed) {
  if (LEFT_MOTOR_STATE == MOTOR_STOP || LEFT_MOTOR_STATE == MOTOR_FORWARD) {
    LEFT_MOTOR_STATE = MOTOR_BACKWARD;
  }
  else {
    LEFT_MOTOR_STATE = MOTOR_FORWARD;
  }
  RIGHT_MOTOR_STATE = MOTOR_STOP;
  setSpeed(newSpeed);
}

void setTurnRight(int newSpeed) {
  if (RIGHT_MOTOR_STATE == MOTOR_STOP || RIGHT_MOTOR_STATE == MOTOR_FORWARD) {
    RIGHT_MOTOR_STATE = MOTOR_BACKWARD;
  }
  else {
    RIGHT_MOTOR_STATE = MOTOR_FORWARD;
  }
  LEFT_MOTOR_STATE = MOTOR_STOP;
  setSpeed(newSpeed);
}

void setSpeed(int newSpeed) {
  if (newSpeed <= MIN_SPEED) {
    SPEED = MIN_SPEED;
  }
  else if (newSpeed >= MAX_SPEED) {
    SPEED = MAX_SPEED;
  }
  else {
    SPEED = newSpeed;
  }
}