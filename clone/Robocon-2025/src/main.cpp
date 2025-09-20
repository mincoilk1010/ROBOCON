#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "servo_arm.h"
#include "robot.h"
#include "config.h"
                                   
void setup(){

  Serial.begin(115200); 
  Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2);
  // WiFi connect
  // WiFi.begin(ssid, password);
  // Serial.print("Connecting to Wifi...");
  // int retry = 0;
  // while (WiFi.status() != WL_CONNECTED && retry < 20)
  // {
  //   delay(500);
  //   Serial.print(".");
  //   retry++;
  // }
  
  // if (WiFi.status() != WL_CONNECTED){
  //   Serial.println("\nFailed to connect to WiFi, restarting...");
  //   ESP.restart();
  // }
  
  // Serial.print("\nWiFi connected, IP: ");
  // Serial.print(WiFi.localIP());
  // Initializating robot
  initRobot();
  setDefaultArm();
  Serial.println("Robot is ready");
}

void loop(){
  // Try to connect to wifi if esp32 lost connection
  // if(WiFi.status() != WL_CONNECTED){
  //   Serial.println("WiFi disconnected!");
  //   WiFi.reconnect();
  //   delay(5000);
  // }
  // Receive data from UART
  if (Serial1.available()){
    char cmd = Serial1.read();
    handleCommandMotor(cmd);
    handleCommandServo(cmd);
  }
}



