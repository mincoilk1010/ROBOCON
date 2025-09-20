#pragma once
#include<ESP32Servo.h>

int angle1 = 0;
int angle2 = 110;  
int angle3 = 145;       
const int stepAngle = 5; 

Servo servo1;
Servo servo2;
Servo servo3;

void initServo();
void setDefaultArm();
void updateArm(int a, int id);
void takeTheBall(int id, int target);
void servoUp(int id);
void servoDown(int id);
void handleCommandServo(char cmd);
void takeTheBall();
void throwTheBall();
void setupToTakeAndThrowTheBall(int id, int target);