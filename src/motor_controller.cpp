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

int speed = 0;

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
    analogWrite(ENA, speed);
  }
  else if (LEFT_MOTOR_STATE == MOTOR_BACKWARD) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);
  }
  else {
    stopLeftMotor();
  }
}

void setForwardLeftMotor(int speed) {
  LEFT_MOTOR_STATE = MOTOR_FORWARD;
  speed = speed;
}

void setBackwardLeftMotor(int speed) {
  LEFT_MOTOR_STATE = MOTOR_BACKWARD;
  speed = speed;
}

void spinRightMotor() {
  if (RIGHT_MOTOR_STATE == MOTOR_FORWARD) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, speed);
  }
  else if (RIGHT_MOTOR_STATE == MOTOR_BACKWARD) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, speed);
  }
  else {
    stopRightMotor();
  }
}

void setForwardRightMotor(int speed) {
  RIGHT_MOTOR_STATE = MOTOR_FORWARD;
  speed = speed;
}

void setBackwardRightMotor(int speed) {
  RIGHT_MOTOR_STATE = MOTOR_BACKWARD;
  speed = speed;
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
}

void setMoveForward(int speed) {
  LEFT_MOTOR_STATE = MOTOR_FORWARD;
  RIGHT_MOTOR_STATE = MOTOR_FORWARD;
  speed = speed;
}

void setMoveBackward(int speed) {
  LEFT_MOTOR_STATE = MOTOR_BACKWARD;
  RIGHT_MOTOR_STATE = MOTOR_BACKWARD;
  speed = speed;
}

void setTurnLeft(int speed) {
  LEFT_MOTOR_STATE = MOTOR_BACKWARD;
  RIGHT_MOTOR_STATE = MOTOR_FORWARD;
  speed = speed;
}

void setTurnRight(int speed) {
  LEFT_MOTOR_STATE = MOTOR_FORWARD;
  RIGHT_MOTOR_STATE = MOTOR_BACKWARD;
  speed = speed;
}

void setSpeed(int speed) {
  speed = speed;
}