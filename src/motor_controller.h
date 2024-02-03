#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

extern int IN1, IN2, ENA, IN3, IN4, ENB;
extern const int MOTOR_STOP, MOTOR_FORWARD, MOTOR_BACKWARD, MIN_SPEED, MAX_SPEED;
extern int SPEED, LEFT_MOTOR_STATE, RIGHT_MOTOR_STATE;

void setupMotorController();

void spinLeftMotor();

void setForwardLeftMotor(int newSpeed);

void setBackwardLeftMotor(int newSpeed);

void spinRightMotor();

void setForwardRightMotor(int newSpeed);

void setBackwardRightMotor(int newSpeed);

void stopLeftMotor();

void stopRightMotor();

void stopMovement();

void pauseMovement();

void setMoveForward(int newSpeed);

void setMoveBackward(int newSpeed);

void setTurnLeft(int newSpeed);

void setTurnRight(int newSpeed);

void setSpeed(int newSpeed);

#endif // MOTOR_CONTROLLER_H
