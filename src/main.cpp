#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include "request.h"
#include "motor_controller.h"

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

  initializeServer();
  stopMovement();
}

void loop() {
  handleClient();
  spinLeftMotor();
  spinRightMotor();
  delay(100);
}