#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

extern int IN1, IN2, ENA, IN3, IN4, ENB;
extern const int MOTOR_STOP, MOTOR_FORWARD, MOTOR_BACKWARD;
extern int speed, LEFT_MOTOR_STATE, RIGHT_MOTOR_STATE;

void setupMotorController();
void spinLeftMotor();
void setForwardLeftMotor(int speed);
void setBackwardLeftMotor(int speed);
void spinRightMotor();
void setForwardRightMotor(int speed);
void setBackwardRightMotor(int speed);
void stopLeftMotor();
void stopRightMotor();
void stopMovement();
void setMoveForward(int speed);
void setMoveBackward(int speed);
void setTurnLeft(int speed);
void setTurnRight(int speed);
void setSpeed(int speed);

#endif // MOTOR_CONTROLLER_H
