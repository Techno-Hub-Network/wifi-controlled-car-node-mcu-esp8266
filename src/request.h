#ifndef REQUEST_H
#define REQUEST_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include "motor_controller.h"

void handleRoot();
void handleForward();
void handlePostRequests(void (*callbackFunction)(int));
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleSpeed();
void initializeServer();
void handleClient();

#endif // REQUEST_H
