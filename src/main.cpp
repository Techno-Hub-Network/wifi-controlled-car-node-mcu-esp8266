#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include "request.cpp"
// #include "motor.controller.cpp"

const char* ssid = "THN_CAR";
const char* password = "THN_CAR1";

void setup() {
  Serial.begin(115200);
  setupMotorController();

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS");
    return;
  }

  WiFi.softAP(ssid, password);
  delay(100);

  Serial.println("Hotspot IP address: " + WiFi.softAPIP().toString());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_POST, handleForward);
  server.on("/backward", HTTP_POST, handleBackward);
  server.on("/left", HTTP_POST, handleLeft);
  server.on("/right", HTTP_POST, handleRight);
  server.on("/stop", HTTP_POST, handleStop);
  server.on("/speed", HTTP_POST, handleSpeed);
  server.begin();
  stopMovement();
}

void loop() {
  server.handleClient();
  spinLeftMotor();
  spinRightMotor();
  delay(100);
}