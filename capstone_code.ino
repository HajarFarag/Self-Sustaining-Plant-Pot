#include <Servo.h> 

const int AirValue = 600;
const int WaterValue = 350; 
int soilmoisturepercent=0;

const int IN1=3; //Input 2 on HBridge
const int IN2=4; //Input 1 on HBridge
const int IN3=5; //Input 3 on HBridge
const int IN4=6; //Input 4 on HBridge

const int IN5=7; //Signal on Servo Motor
Servo waterGate;

const int IR_sensor_front=10; //Output of IR 1
const int IR_sensor_back=12; //Output of IR 3


#define LDR_sensor_front A0
#define LDR_sensor_left A1
#define LDR_sensor_back A2
#define LDR_sensor_right A3

#define soilMoistureValue A4

//#define IR_sensor_front A4
//#define IR_sensor_left A5
//#define IR_sensor_back A6
//#define IR_sensor_right A7

void setup(){

 Serial.begin(9600);
 waterGate.attach(IN5);
 //pinMode
  
}

void loop(){
  
  int moisture_value = analogRead(soilMoistureValue);
  
  int LDR_front = analogRead(LDR_sensor_front);
  int LDR_back = analogRead(LDR_sensor_back);
  int LDR_left = analogRead(LDR_sensor_left);
  int LDR_right = analogRead(LDR_sensor_right);
  
  int IR_front = digitalRead(IR_sensor_front);
  int IR_back = digitalRead(IR_sensor_back);
  
  soilmoisturepercent = map(moisture_value, AirValue, WaterValue, 0, 100);
  
  if(soilmoisturepercent <= 50){
    
    waterGate.write(90);
    delay(1000);
    waterGate.write(0);
  
  }
  
  if (LDR_front > LDR_back && LDR_front > LDR_left && LDR_front > LDR_right){
    
    check_IR(255); // add function
    delay(50);
    forward(255);
    delay(500);
    Serial.print("FRONT");
  
  }
  
  else if (LDR_back > LDR_front && LDR_back > LDR_left && LDR_back > LDR_right){
  
    check_IR(255); // add function
    delay(50);
    backward(255);
    delay(500);
    Serial.print("BACK");
  
  }
  
  else if (LDR_right > LDR_front && LDR_right > LDR_left && LDR_right > LDR_back){
  
    check_IR(255); // add function
    delay(50);
    rotate_r(255);
    delay(500);
    Serial.print("RIGHT");
  
  }
  
  else if (LDR_left > LDR_right && LDR_left > LDR_back && LDR_left > LDR_front){
  
    check_IR(255); // add function
    delay(50);
    rotate_l(255);
    delay(500);
    Serial.print("LEFT");
  
  }
  
  // testing code
  Serial.print("LDR front: ");
  Serial.println(LDR_front);
  Serial.print("LDR_back: ");
  Serial.println(LDR_back);
  Serial.print("LDR_left: ");
  Serial.println(LDR_left);
  Serial.print("LDR_right: ");
  Serial.println(LDR_right);
  Serial.print("IR_front: ");
  Serial.println(IR_front);
  Serial.print("IR_back: ");
  Serial.println(IR_back);
  Serial.print("moisture percentage:  ");
  Serial.println(soilmoisturepercent);
}


void Stop(){
  Serial.begin(9600);//When we want to  Motor To stop ,
  // just void this part on the loop section .
  analogWrite(IN1,0);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,0);
}

void rotate_r (int Speed)
{
  //When we want to let Motor To Rotate ,
  // just void this part on the loop section .
  analogWrite(IN1,0);
  analogWrite(IN2,Speed);
  analogWrite(IN3,Speed);
  analogWrite(IN4,0);
}

void rotate_l (int Speed)
{
  //When we want to let Motor To Rotate ,
  // just void this part on the loop section .
  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,Speed);
}

void backward (int Speed){
  //When we want to let Motor To move forward,
  // just void this part on the loop section .
  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,Speed);
  analogWrite(IN4,0);
}

void forward (int Speed){
  //When we want to let Motor To move forward,
  // just void this part on the loop section .
  analogWrite(IN1,0);
  analogWrite(IN2,Speed);
  analogWrite(IN3,0);
  analogWrite(IN4,Speed);
}

void check_IR(int speed){
  
  int IR_front = digitalRead(IR_sensor_front);
  int IR_back = digitalRead(IR_sensor_back);
  
  if (IR_front == 1){
    
    backward(speed);
    
  }
  
  else if(IR_back == 1){
  
    forward(speed);
    
  }
  
 

}
