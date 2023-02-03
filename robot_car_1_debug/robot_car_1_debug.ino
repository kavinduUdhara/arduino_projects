#include <Servo.h>
//servo motor
Servo servo = Servo();

int EnA = 3; // Enable Pin for motor A
int In1 = 4; // Input 1 Pin for motor A
int In2 = 5; // Input 2 Pin for motor A

// Motor B
int EnB = 11; // Enable Pin for motor B
int In3 = 12; // Input 3 Pin for motor B
int In4 = 13; // Input 4 Pin for motor B

char connection;

void setup() {
  //servo.attach(A0); //servo motor pin

  //L298N-2A Motor Driver Module | motorA - pins
  pinMode(EnA, OUTPUT); 
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);

  //L298N-2A Motor Driver Module | motorB - pins
  pinMode(EnB, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  //define the speed of the motors | lowest - 100 | highest - 200
  analogWrite(EnA, 100);
  analogWrite(EnB, 100);

  //for bluetooth signals
  Serial.begin(9600);
}

void loop() {
  go_forward();
}

void go_forward(){
  //go forward | In1 -> HIGH | In2 -> LOW || In3 -> LOW | In4 -> HIGH
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void go_backward(){
  //go backward | In1 -> HIGH | In2 -> LOW || In3 -> LOW | In4 -> HIGH
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void stop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void turn_left(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void turn_right(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void after_action(){
    delay(500);
    stop();
    delay(500);
}

void servo_motor_forward(){
  servo.write(30);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(150);
  delay(500);
  servo.write(90);
  delay(500);
}

void servo_motor_left(){
  servo.write(150);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(150);
  delay(500);
}

void servo_motor_right(){
  servo.write(30);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(30);
  delay(500);
}