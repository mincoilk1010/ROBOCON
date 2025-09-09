#include <ESP32Servo.h>

// =================== Define Servo ===================
Servo servo1;
Servo servo2;
Servo servo3;

int angle1 = 0;
int angle2 = 110;  
int angle3 = 145;       // Góc ban đầu
int stepAngle = 5;       // Bước tăng/giảm góc

// =================== Trạng thái servo ===================
bool servo1Running = false;
bool servo1DirectionUp = true;
bool servo2Running = false;
bool servo2DirectionUp = true;
bool servo3Running = false;
bool servo3DirectionUp = true;

// =================== Hàm điều khiển ===================
void setServoAngle(int a, int id) {
  if (a < 0) a = 0;
  if (a > 180) a = 180;
  switch (id) {
    case 1: angle1 = a; servo1.write(angle1); break;  
    case 2: angle2 = a; servo2.write(angle2); break;
    case 3: angle3 = a; servo3.write(angle3); break;
  }
}

void servoUp(int id) {
  if (id == 1) setServoAngle(angle1 + stepAngle, 1);
  if (id == 2) setServoAngle(angle2 + stepAngle, 2);
  if (id == 3) setServoAngle(angle3 + stepAngle, 3);
  Serial.println(String(angle1) + " " + String(angle2) + " " + String(angle3));
}

void servoDown(int id) {
  if (id == 1) setServoAngle(angle1 - stepAngle, 1);
  if (id == 2) setServoAngle(angle2 - stepAngle, 2);
  if (id == 3) setServoAngle(angle3 - stepAngle, 3);
  Serial.println(String(angle1) + " " + String(angle2) + " " + String(angle3));
}

void handleCommand_Arm(char cmd){
  switch(cmd){
    case 'Q': servoUp(1); break;
    case 'A': servoDown(1); break;
    case 'W': servoUp(2); break;
    case 'S': servoDown(2); break;
    case 'E': servoUp(3); break;
    case 'D': servoDown(3); break;
    case 'L': take_the_ball(); break;
    case 'K': set_default_arm(); break;
    case 'T': through_the_ball(); break;
  }
}

// =================== Hàm cao cấp ===================
void control_arm (int a1,int a2, int a3){
    setServoAngle(a1,1);
    delay(300);
    setServoAngle(a2,2);
    delay(300);
    setServoAngle(a3,3);
    delay(300);
}

void updateServo(Servo &servo, bool &running, bool &directionUp, int &angle) {
  if (running) {
    if (directionUp) angle += stepAngle; 
    else angle -= stepAngle;
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;
    servo.write(angle);
    delay(50); // tốc độ quay
  }
}

void set_default_arm (){
  control_arm(0,110,145);
}

void control_angle_servo(int servoID, int target){
  int *anglePtr;
  Servo *servoPtr;
  switch(servoID){
    case 1: anglePtr = &angle1; servoPtr = &servo1; break;
    case 2: anglePtr = &angle2; servoPtr = &servo2; break;
    case 3: anglePtr = &angle3; servoPtr = &servo3; break;
    default: return;
  }

  while (*anglePtr != target){
    if (*anglePtr < target) (*anglePtr)++;
    else if (*anglePtr > target) (*anglePtr)--;
    servoPtr->write(*anglePtr);
    delay(20);
  }
}

void take_the_ball(){
  control_angle_servo(3, 80);
  delay(200);
  control_angle_servo(2, 85);
  delay(200);
  control_angle_servo(3, 125);
  delay(200);
}

void through_the_ball(){
  control_angle_servo(2, 145);
  delay(200);
  control_angle_servo(1, 180);
  delay(200);
  control_angle_servo(3,180);
  delay(200);
}

// =================== SETUP ===================
void setup(){
  Serial.begin(115200);
  servo1.attach(35);
  servo2.attach(36);
  servo3.attach(37);
  set_default_arm();
}

// =================== LOOP ===================
void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();    
    handleCommand_Arm(cmd);
  }
  updateServo(servo1, servo1Running, servo1DirectionUp, angle1);
  updateServo(servo2, servo2Running, servo2DirectionUp, angle2);
  updateServo(servo3, servo3Running, servo3DirectionUp, angle3);
}
