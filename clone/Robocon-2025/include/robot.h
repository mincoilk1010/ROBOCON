#pragma once

#define ENA1 12 // trước trái
#define IN1_1 13
#define IN2_1 14

#define ENB1 9 // trước phải
#define IN3_1 10
#define IN4_1 11

#define ENA2  8 // sau trái
#define IN1_2  3
#define IN2_2 46 

#define ENB2 16 // sau phải
#define IN3_2 17
#define IN4_2 18 

const int freq = 1000;     
const int resolution = 8;  
const int MOTOR_SPEED = 150; 


void initRobot();
void wheelSpin(int v1, int v2, int v3, int v4);
void handleCommandMotor(char cmd);
void moveForward(int speed);
void moveBackward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void rotateRight(int speed);
void rotateLeft(int speed);
