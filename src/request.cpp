#include "request.h"

ESP8266WebServer server(80);

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

void initializeServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_POST, handleForward);
  server.on("/backward", HTTP_POST, handleBackward);
  server.on("/left", HTTP_POST, handleLeft);
  server.on("/right", HTTP_POST, handleRight);
  server.on("/stop", HTTP_POST, handleStop);
  server.on("/speed", HTTP_POST, handleSpeed);
  server.begin();
}

void handleClient() {
  server.handleClient();
}