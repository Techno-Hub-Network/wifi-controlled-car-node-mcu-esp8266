#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include "motor.controller.cpp"

ESP8266WebServer server(80);

void handleRoot();
void handleForward();
void handlePostRequests(void (*callbackFunction)(int));
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleSpeed();

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");

  if (file) {
    server.streamFile(file, "text/html");
    file.close();
  }
  else {
    server.send(404, "text/plain", "File Not Found");
  }
}

void handlePostRequests(void (*callbackFunction)(int)) {
  if (server.hasArg("speed")) {
    speed = server.arg("speed").toInt();
    callbackFunction(speed);
  }

  server.send(200, "text/plain", "Ok");
}

void handleForward() {
  handlePostRequests(setMoveForward);
}

void handleBackward() {
  handlePostRequests(setMoveBackward);
}

void handleLeft() {
  handlePostRequests(setTurnLeft);
}

void handleRight() {
  handlePostRequests(setTurnRight);
}

void handleStop() {
  stopMovement();
  server.send(200, "text/plain", "Ok");
}

void handleSpeed() {
  if (server.hasArg("speed")) {
    int speed = server.arg("speed").toInt();
    if (speed > 255) {
      setSpeed(255);
    }
    else if (speed <= 0) {
      setSpeed(0);
      stopMovement();
    }
  }

  server.send(200, "text/plain", "Ok");
}
