#include <Arduino.h>
#include "robot.h"
 
void motorSpin(int v1, int v2, int v3, int v4) {
  // Động cơ 1 - Bánh trước trái
  digitalWrite(IN1_1, v1 >= 0 ? LOW : HIGH);
  digitalWrite(IN2_1, v1 >= 0 ? HIGH  : LOW);
  ledcWrite(0, abs(v1));

  // Động cơ 2 - Bánh trước phải
  digitalWrite(IN3_1, v2 >= 0 ? HIGH : LOW);
  digitalWrite(IN4_1, v2 >= 0 ? LOW  : HIGH);
  ledcWrite(1, abs(v2));
  
  // Động cơ 3 - Bánh sau trái
  digitalWrite(IN1_2, v3 >= 0 ? HIGH : LOW);
  digitalWrite(IN2_2, v3 >= 0 ? LOW  : HIGH);
  ledcWrite(2, abs(v3));

  // Động cơ 4 - Bánh sau phải
  digitalWrite(IN3_2, v4 >= 0 ? LOW : HIGH);
  digitalWrite(IN4_2, v4 >= 0 ? HIGH  : LOW);
  ledcWrite(3, abs(v4));
}

void initRobot() {

  pinMode(IN1_1, OUTPUT);
  pinMode(IN2_1, OUTPUT);
  pinMode(IN3_1, OUTPUT);
  pinMode(IN4_1, OUTPUT);

  pinMode(IN1_2, OUTPUT);
  pinMode(IN2_2, OUTPUT);
  pinMode(IN3_2, OUTPUT);
  pinMode(IN4_2, OUTPUT);

  // Cấu hình PWM cho 4 kênh
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcSetup(3, freq, resolution);

  // Gán PWM cho các chân ENA/ENB
  ledcAttachPin(ENA1, 0);
  ledcAttachPin(ENB1, 1);
  ledcAttachPin(ENA2, 2);
  ledcAttachPin(ENB2, 3);

  // Stop when robot start up
  motorSpin(0, 0, 0, 0);
}

void moveForward(int speed) {
  motorSpin(speed+90, speed+90, speed, speed);
}

void moveBackward(int speed) {
  motorSpin(-speed -90, -speed-90, -speed, -speed);
}

void turnRight(int speed) {
  motorSpin(-speed-90, speed+90, -speed, speed);
}

void turnLeft(int speed) {
  motorSpin(speed+90, -speed-90, speed, -speed);
}

void rotateRight(int speed) {
  motorSpin(speed+90, speed+90, -speed, -speed);
}

void rotateLeft(int speed) {
  motorSpin(-speed-90, -speed-90, speed, speed);
}

void handleCommandMotor(char cmd){
    switch (cmd){
        case 'F' :
            moveForward(MOTOR_SPEED);
            Serial.println("Go Straight");
            break;
        case 'B' :
            moveBackward(MOTOR_SPEED);
            Serial.println("Go Back");
            break;
        case 'R':
            turnRight(MOTOR_SPEED);
            Serial.println("Turn Right");
            break;
        case 'L':
            turnLeft(MOTOR_SPEED);
            Serial.println("Turn Left");
            break;
        case 'G':
            rotateRight(MOTOR_SPEED);
            Serial.println("Rorate Right");
            break;
        case 'H':
            rotateLeft(MOTOR_SPEED);
            Serial.println("Rorate Left");
            break;
        case 'S':
            motorSpin(0, 0, 0, 0);
            Serial.println("Stop");
            break;
        default : 
          motorSpin(0, 0, 0, 0);
            break;
    }
}

