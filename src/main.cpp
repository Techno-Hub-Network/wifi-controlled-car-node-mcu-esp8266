#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <LittleFS.h>

const char* ssid = "THN_CAR";
const char* password = "THN_CAR1";

int IN1 = D1;
int IN2 = D0;
int ENA = D2;

int IN3 = D6;
int IN4 = D4;
int ENB = D3;

int speed = 255;

ESP8266WebServer server(80);

void spinForwardLeftMotor(int speed);
void spinBackwardLeftMotor(int speed);
void spinForwardRightMotor(int speed);
void spinBackwardRightMotor(int speed);
void stopLeftMotor();
void stopRightMotor();
void stopMovement();
void moveForward(int speed);
void moveBackward(int speed);
void handleRoot();
void handleForward();
void handlePostRequests(void (*callbackFunction)(int));
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleSpeed();

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

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
  // speed = 180;
  // moveForward(speed);
  // delay(2000);
  // stopMovement();
  // delay(2000);
  // moveBackward(speed);
  // delay(2000);
  // stopMovement();
  // delay(2000);


  //   stopLeftMotor();
  //   stopRightMotor();
  //   delay(2000);
  //   spinBackwardLeftMotor(speed);
  //   spinBackwardRightMotor(speed);
  //   delay(2000);
  //   stopLeftMotor();
  //   stopRightMotor();
  //   delay(2000);
  // server.handleClient();
  server.handleClient();
}


void spinForwardLeftMotor(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
}

void spinBackwardLeftMotor(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

void spinForwardRightMotor(int speed) {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void spinBackwardRightMotor(int speed) {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void stopLeftMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void stopRightMotor() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopMovement() {
  stopLeftMotor();
  stopRightMotor();
}

void moveForward(int speed) {
  spinForwardLeftMotor(speed);
  spinForwardRightMotor(speed);
  delay(500);
}

void moveBackward(int speed) {
  spinBackwardLeftMotor(speed);
  spinBackwardRightMotor(speed);
  delay(500);
}

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
  handlePostRequests(moveForward);
  stopMovement();
}

void handleBackward() {
  handlePostRequests(moveBackward);
  stopMovement();
}

void handleLeft() {
  handlePostRequests(spinForwardLeftMotor);
  stopMovement();
}

void handleRight() {
  handlePostRequests(spinForwardRightMotor);
  stopMovement();
}

void handleStop() {
  stopMovement();
  server.send(200, "text/plain", "Ok");
}

void handleSpeed() {
  if (server.hasArg("speed")) {
    speed = server.arg("speed").toInt();
    if (speed > 255) {
      speed = 255;
    }
    else if (speed <= 0) {
      speed = 0;
      stopMovement();
    }
  }

  server.send(200, "text/plain", "Ok");
}
