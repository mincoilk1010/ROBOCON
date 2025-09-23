#pragma once
#include<ESP32Servo.h>

extern int angle1;
extern int angle2;
extern int angle3;
extern int stepAngle;
    
extern Servo servo1;
extern Servo servo2;
extern Servo servo3;

void initServo();
void setDefaultArm();
void updateArm(int a, int id);
void servoUp(int id);
void servoDown(int id);
void handleCommandServo(char cmd);
void takeTheBall();
void throwTheBall();
void setupToTakeAndThrowTheBall(int id, int target);