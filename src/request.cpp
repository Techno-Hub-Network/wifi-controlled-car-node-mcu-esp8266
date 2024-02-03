#include "request.h"

ESP8266WebServer server(80);

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");

  if (file) {
    server.streamFile(file, "text/html");
    file.close();
  } else {
    server.send(404, "text/plain", "File Not Found");
  }
}

void handlePostRequests(void (*callbackFunction)(int)) {
  if (server.hasArg("speed")) {
    const int newSpeed = server.arg("speed").toInt();
    setSpeed(newSpeed);
    callbackFunction(newSpeed);
  }

  server.send(200, "text/plain", "Ok");
}

void handleForward() { handlePostRequests(setMoveForward); }

void handleBackward() { handlePostRequests(setMoveBackward); }

void handleLeft() { handlePostRequests(setTurnLeft); }

void handleRight() { handlePostRequests(setTurnRight); }

void handleStop() {
  stopMovement();
  server.send(200, "text/plain", "Ok");
}

void handleSpeed() {
  if (server.hasArg("speed")) {
    int newSpeed = server.arg("speed").toInt();
    setSpeed(newSpeed);
    if (SPEED == MIN_SPEED) {
      stopMovement();
    }
    if (SPEED > MIN_SPEED && LEFT_MOTOR_STATE == MOTOR_STOP && RIGHT_MOTOR_STATE == MOTOR_STOP) {
      setMoveForward(SPEED);
    }
  }

  server.send(200, "text/plain", "Ok");
}

void initializeServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_POST, handleForward);
  server.on("/backward", HTTP_POST, handleBackward);
  server.on("/left", HTTP_POST, handleLeft);
  server.on("/right", HTTP_POST, handleRight);
  server.on("/stop", HTTP_POST, handleStop);
  server.on("/speed", HTTP_POST, handleSpeed);
  server.on("/status", HTTP_GET, handleGetStatus);
  server.begin();
}

void handleClient() { server.handleClient(); }

void handleGetStatus() {
  String status = "{";
  status += "\"currentStatus\":{";
  status += "\"leftMotor\":\"" + String(LEFT_MOTOR_STATE) + "\",\"rightMotor\":\"" + String(RIGHT_MOTOR_STATE) +
            "\",\"speed\":\"" + String(SPEED);
  status += "\"},";
  status += "\"motorStates\":{";
  status += "\"forward\":\"" + String(MOTOR_FORWARD) + "\",\"backward\":\"" + String(MOTOR_BACKWARD) +
            "\",\"stop\":\"" + String(MOTOR_STOP);
  status += "\"},";
  status += "\"motorSpeeds\":{";
  status += "\"minSpeed\":\"" + String(MIN_SPEED) + "\",\"maxSpeed\":\"" + String(MAX_SPEED);
  status += "\"}";
  status += "}";

  server.send(200, "application/json", status);
}
