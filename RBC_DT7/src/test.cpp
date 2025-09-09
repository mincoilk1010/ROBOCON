
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// =================== WiFi & MQTT ===================
const char* ssid = "Trung Tam TT-TV";
const char* password = "12345679";
const char* mqtt_server = "192.168.22.44"; // IP broker (Node-RED/Mosquitto)

WiFiClient espClient;
PubSubClient client(espClient);

// =================== Servo ===================
Servo servo1;
Servo servo2;
Servo servo3;

#define RXD2 44
#define TXD2 43

int angle1 = 0;
int angle2 = 0;  
int angle3 = 0;  
int angle4 = 0;          // Góc ban đầu
int stepAngle = 5;       // Bước tăng/giảm góc

// =================== Motor ===================
#define ENA1 12 // truoc trái
#define IN1_1 13
#define IN2_1 14

#define ENB1 9  // truoc phai
#define IN3_1 10
#define IN4_1 11

#define ENA2  8 // sau trai
#define IN1_2  3
#define IN2_2 46 

#define ENB2 16 // sau phai
#define IN3_2 17
#define IN4_2 18 

#define SPEED_THUAN 150
#define SPEED_DAO -150

// =================== Hàm điều khiển servo ===================
bool servo1Running = false;
bool servo1DirectionUp = true;
bool servo2Running = false;
bool servo2DirectionUp = true;
bool servo3Running = false;
bool servo3DirectionUp = true;


void setServoAngle1(int a, int b) {
  if (a < 0) a = 0;
  if (a > 180) a = 180;
  switch(b){
    case 1:
        angle1 = a;
      servo1.write(angle1);
      break;  
    case 2:
      angle2 = a;
      servo2.write(angle2);
      break;
    case 3:
      angle3 = a;
      servo3.write(angle3);
      break;
    case 4:
      angle4 = a;
      servo1.write(angle4); // nếu bạn định dùng servo4 thì cần khai báo thêm
      break;
  }
}

void servoUp(int a) {
  switch(a){
    case 1: setServoAngle1(angle1 + stepAngle, 1); break;
    case 2: setServoAngle1(angle2 + stepAngle, 2); break;
    case 3: setServoAngle1(angle3 + stepAngle, 3); break;
    case 4: setServoAngle1(angle4 + stepAngle, 4); break;
  }
}

void servoDown(int a) {
  switch(a){
    case 1: setServoAngle1(angle1 - stepAngle, 1); break;
    case 2: setServoAngle1(angle2 - stepAngle, 2); break;
    case 3: setServoAngle1(angle3 - stepAngle, 3); break;
    case 4: setServoAngle1(angle4 - stepAngle, 4); break;
  }
}

// =================== Motor control ===================
void setMotor(int kenhpwm, int in1, int in2, int speed) {
  speed = constrain(speed, -255, 255);
  if(speed > 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if(speed < 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  ledcWrite(kenhpwm, abs(speed));
}

void banhMecanum(int sp_truoc_phai, int sp_truoc_trai, int sp_sau_phai, int sp_sau_trai){
  setMotor(ENA1, IN1_1, IN2_1, sp_truoc_trai);
  setMotor(ENB1, IN3_1, IN4_1, sp_truoc_phai);
  setMotor(ENA2, IN1_2, IN2_2, sp_sau_trai);
  setMotor(ENB2, IN3_2, IN4_2, sp_sau_phai);
}

void controlServo01(char cmd){
  switch(cmd){
    // Servo1 control
    case 'T': // Bắt đầu quay lên
      servo1Running = true;
      servo1DirectionUp = true;
      break;
    case 'J': // Bắt đầu quay xuống
      servo1Running = true;
      servo1DirectionUp = false;
      break;
    case 'S': // Dừng servo
      servo1Running = false;
      break;
    default: break;
}
}
void controlServo02(char cmd){
  switch(cmd){
    // Servo1 control
    case 'Z': // Bắt đầu quay lên
      servo1Running = true;
      servo1DirectionUp = true;
      break;
    case 'X': // Bắt đầu quay xuống
      servo1Running = true;
      servo1DirectionUp = false;
      break;
    case 'C': // Dừng servo
      servo1Running = false;
      break;
    default: break;
}
}
void controlServo03(char cmd){
  switch(cmd){
    // Servo1 control
    case 'V': // Bắt đầu quay lên
      servo1Running = true;
      servo1DirectionUp = true;
      break;
    case 'N': // Bắt đầu quay xuống
      servo1Running = true;
      servo1DirectionUp = false;
      break;
    case 'M': // Dừng servo
      servo1Running = false;
      break;
    default: break;
}
}
void handleCommand_Arm(char cmd){
  controlServo01(cmd);
  controlServo02(cmd);
  controlServo03(cmd);
}
void set_arm_servo(char cmd){
  if ()
}
void control_arm (int angle1,int angle2, int angle3){
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500);
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500);
    servo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500);
}

void set_default_arm (){
  control_arm(45,45,45);
}
// =================== Command handler ===================
void handleCommand_Motor(char cmd) {

    // Các lệnh khác giữ nguyên
    case 'F': banhMecanum(SPEED_THUAN, SPEED_THUAN, SPEED_THUAN, SPEED_THUAN); break;
    case 'B': banhMecanum(SPEED_DAO, SPEED_DAO, SPEED_DAO, SPEED_DAO); break;
    case 'L': banhMecanum(SPEED_THUAN, SPEED_DAO, SPEED_THUAN, SPEED_DAO); break;
    case 'R': banhMecanum(SPEED_DAO, SPEED_THUAN, SPEED_DAO, SPEED_THUAN); break;
    case 'G': banhMecanum(SPEED_DAO, SPEED_DAO, SPEED_THUAN, SPEED_THUAN); break;
    case 'H': banhMecanum(SPEED_THUAN, SPEED_THUAN, SPEED_DAO, SPEED_DAO); break;
    default:
      Serial.println("Unknown command");
      break;
  }



// =================== MQTT callback ===================
void mqttCallback(char* topic, byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)message[i];
  }
  Serial.print("MQTT ["); Serial.print(topic); Serial.print("]: "); Serial.println(msg);

  if (String(topic) == "robot/cmd") {
    if (msg.length() > 0) {
      handleCommand_Motor(msg[0]);  // nhận ký tự đầu tiên như 'T','J','P','F',...
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Đang kết nối MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Đã kết nối!");
      client.subscribe("robot/cmd");
    } else {
      Serial.print("Lỗi, 2=");
      Serial.print(client.state());
      Serial.println(" thử lại sau 5 giây");
      delay(5000);
    }
  }
}

// =================== SETUP ===================
void setup(){
  Serial.begin(115200);
  //Serial2.begin(115200);
  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi connected, IP: ");
  Serial.println(WiFi.localIP());

  // MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqttCallback);

  // Servo attach
  servo1.attach(35);
  servo2.attach(36);
  servo3.attach(37);
  setServoAngle1(angle1, 1);

  // Motor pins
  pinMode(IN1_1, OUTPUT); pinMode(IN2_1, OUTPUT);
  pinMode(IN3_1, OUTPUT); pinMode(IN4_1, OUTPUT);
  pinMode(IN1_2, OUTPUT); pinMode(IN2_2, OUTPUT);
  pinMode(IN3_2, OUTPUT); pinMode(IN4_2, OUTPUT);

  // PWM setup
  ledcAttachPin(ENA1, 1000);
  ledcAttachPin(ENB1, 1000);
  ledcAttachPin(ENA2, 1000);
  ledcAttachPin(ENB2, 1000);

  banhMecanum(0, 0, 0, 0);
}

// =================== LOOP ===================
void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lệnh từ UART
  if (Serial2.available()) {      
    char cmd = Serial2.read();
    handleCommand_Motor(cmd);    
    handleCommand_Servo(cmd);     
  }
  if (servo1Running) {

  if (servo1DirectionUp) {
    angle1 += stepAngle;
    if (angle1 > 180) angle1 = 180;
  } else {
    angle1 -= stepAngle;
    if (angle1 < 0) angle1 = 0;
  }
  servo1.write(angle1);
  delay(50); // tốc độ quay
}

}