#include "servo_arm.h"
#include "robot.h"

int angle1 = 0;
int angle2 = 110;
int angle3 = 145;
int stepAngle = 5;

Servo servo1;
Servo servo2;
Servo servo3;

void updateArm(int angleUpdate, int id){
    if (angleUpdate < 0 ) angleUpdate = 0;
    if (angleUpdate > 180) angleUpdate = 180;
    switch(id){
        case 1 : 
            angle1 = angleUpdate;
            servo1.write(angle1);
            break;
        case 2 : 
            angle2 = angleUpdate;
            servo2.write(angle2);
            break;
        case 3 : 
            angle3 = angleUpdate;
            servo3.write(angle3);
            break;
    }
}

void setupToTakeAndThrowTheBall(int id, int target){
    int *anglePtr;
    Servo *servoPtr;
    switch(id){
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

void takeTheBall(){
    setupToTakeAndThrowTheBall(3, 80);
    delay(200);
    setupToTakeAndThrowTheBall(2, 85);
    delay(200);
    setupToTakeAndThrowTheBall(3, 125);
    delay(200);
}

void throwTheBall(){
    setupToTakeAndThrowTheBall(2,145);
    delay(200);
    setupToTakeAndThrowTheBall(1, 180);
    delay(200);
    setupToTakeAndThrowTheBall(3, 180);
    delay(200);
}

void setDefaultArm(){
    updateArm(angle1, 1);
    delay(500);
    updateArm(angle2, 2);
    delay(500);
    updateArm(angle3, 3);
    delay(500);
}

void servoUp(int id){
    if(id==1) updateArm(angle1 + stepAngle, 1);
    if(id==2) updateArm(angle2 + stepAngle, 2);
    if(id==3) updateArm(angle3 + stepAngle, 3);
    Serial.println(String(angle1) + " - " + String(angle2) + " - " + String(angle3));
}

void servoDown(int id){
    if(id==1) updateArm(angle1 - stepAngle, 1);
    if(id==2) updateArm(angle2 - stepAngle, 2);
    if(id==3) updateArm(angle3 - stepAngle, 3);
    Serial.println(String(angle1) + " - " + String(angle2) + " - " + String(angle3));
}

void handleCommandServo(char cmd){
    switch(cmd){
    case 'Q': servoUp(1); break;
    case 'A': servoDown(1); break;
    case 'W': servoUp(2); break;
    case 'X': servoDown(2); break;
    case 'E': servoUp(3); break;
    case 'D': servoDown(3); break;
    case 'Z': takeTheBall(); break;
    case 'N': throwTheBall(); break;
    default : break;
  }
} 

void initServo(){
    servo1.attach(19);
    servo2.attach(20);  
    servo3.attach(21);
}
