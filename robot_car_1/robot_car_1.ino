/*
  Project: Arduino Controlled Car with Servo Motor, Ultrasonic Sensor and bluetooth moduler
  Purpose: This code provides to control an arduino-powered car with a servo motor and ultrasonic sensor. The car can receive commands through Bluetooth to move forward, backward, turn left, turn right and stop.
  Function: The servo motor acts as the steering mechanism, while the ultrasonic sensor is used for obstacle detection.
  Auther: (cc) Kavindu Udhara
*/

#include <Servo.h> // Include Servo library
#include <Ultrasonic.h> // Include Ultrasonic library
/*The Servo.h library is used to control a servo motor in the project. It provides functions for setting the servo motor's position, speed, and other properties.
The Ultrasonic.h library is used to measure the distance between the ultrasonic sensor and an object in front of it. It provides functions to trigger the ultrasonic sensor and receive the time required for the echo signal to return. This time can then be used to calculate the distance to the object.
Both of these libraries simplify the implementation of these components in the project, making it easier to control the servo motor and measure distance with the ultrasonic sensor.*/

// Servo Motor
Servo servo = Servo(); // Create an object for the servo motor
// Ultrasonic Sensor
Ultrasonic ultrasonicSensor = Ultrasonic(A2, A1);  // ultrasonic sensor is connected to pins A2 (Trig Pin) and A1 (Echo Pin)

// L298N Motor Driver
// Motor A
int EnA = 3; // Enable Pin for motor A
int In1 = 4; // Input 1 Pin for motor A
int In2 = 5; // Input 2 Pin for motor A

// Motor B
int EnB = 11; // Enable Pin for motor B
int In3 = 12; // Input 3 Pin for motor B
int In4 = 13; // Input 4 Pin for motor B
/*Ref. to the error #1 on GitHub: ...use of the library disables analogWrite() (PWM) functionality on pins 9 and 10,... 
ref: https://stackoverflow.com/questions/75318922/motor-driver-isnt-working-properly-while-servo-attacha0-line-present-in-the*/

char connection; //for read bluetooth module connection signels

void setup() {
  servo.attach(10); // servo motor is connected to pin 10

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
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
}

// This is the main loop function where the program listens to the bluetooth connection signals 
void loop() {

  if (connection == 1){
    servo.write(30);
    delay(500);
    servo.write(90);
    delay(500);
    servo.write(150);
    delay(500);
    servo.write(90);
    delay(500);
    int d = u.distanceRead();
    if (d != 0) {
      if (d > 10) {
        // Forward Code
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);
        delay(500);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        delay(500);
      }
    }
    servo.write(90);
  }
  if (connection == 2){
    // Backward Code
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    delay(500);
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    delay(500);
  }
  if(connection == 3){
    servo.write(150);
    delay(500);
    servo.write(90);
    delay(500);
    servo.write(150);
    delay(500);
    int d = u.distanceRead();
    if (d != 0) {
      if (d > 10) {
        // Left Code
        digitalWrite(In1, LOW);
        digitalWrite(In2, HIGH);
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);
        delay(500);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        delay(500);
      }
    }
    servo.write(90);
  }
  if (connection == 4){
    s.write(30);
    delay(500);
    s.write(90);
    delay(500);
    s.write(30);
    delay(500);
    int d = u.distanceRead();
    if (d != 0) {
      if (d > 10) {
        // Right Code
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW);
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        delay(500);
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        delay(500);
      }
    }
    s.write(90);
  }
  if (connection == 5){
    //stop code
            digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
  }    
}
  /*
    // Check if the received signal is '1'
  if (connection == '1'){
    servo_motor_forward();
    int distance = ultrasonicSensor.distanceRead(); // Measure the distance using the ultrasonic sensor
    // Check if the distance measured is not 0 and greater than 30
    if (distance != 0 and distance > 30){
      go_forward();
      after_action();
    }
  }
  // Check if the received signal is '2'
  if (connection == '2'){
    go_backward();
    after_action();
  }
  // Check if the received signal is '3'
  if (connection == '3'){
    servo_motor_right();
    int distance = ultrasonicSensor.distanceRead();
    Serial.println(distance);
    if (distance != 0 and distance > 30){
      turn_right();
      after_action();
    }
  }
  // Check if the received signal is '4'
  if (connection == '4'){
    servo_motor_left();
    int distance = ultrasonicSensor.distanceRead();
    Serial.println(distance);
    if (distance != 0 and distance > 30){
      turn_left();
      after_action();
    }
  }
  // Check if the received signal is '5'
  if (connection == '5'){
    stop();
    delay(500); // Wait for 500ms
  }*/

// This function moves the robot forward
void go_forward(){
  //go forward | In1 -> HIGH | In2 -> LOW || In3 -> LOW | In4 -> HIGH
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

// This function moves the robot backward
void go_backward(){
  //go backward | In1 -> LOW | In2 -> HIGH  || In3 -> HIGH | In4 -> LOW
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

// This function stops the robot
void stop(){
  //stop | * -> LOW
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

// Function to turn the robot to the left
void turn_left(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

// Function to turn the robot to the right
void turn_right(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

// Function to perform actions after turning the robot
void after_action(){
    delay(500); // Wait for 500ms
    stop(); // Stop the robot
    delay(500); // Wait for 500ms
}

// Function to rotate the servo motor to the forward direction
void servo_motor_forward(){
  servo.write(30); // Rotate the servo motor to 30 degrees
  delay(500);
  servo.write(90); // Rotate the servo motor to 90 degrees
  delay(500);
  servo.write(150); // Rotate the servo motor to 150 degrees
  delay(500);
  servo.write(90); // Rotate the servo motor back to 90 degrees
  delay(500);
}

// Function to rotate the servo motor to the left direction
void servo_motor_left(){
  servo.write(150); // Rotate the servo motor to 150 degrees
  delay(500);
  servo.write(90);  // Rotate the servo motor back to 90 degrees
  delay(500);
  servo.write(150); // Rotate the servo motor to 150 degrees again
  delay(500);
}

// Function to rotate the servo motor to the right direction
void servo_motor_right(){
  servo.write(30); // Rotate the servo motor to 30 degrees
  delay(500);
  servo.write(90); // Rotate the servo motor back to 90 degrees
  delay(500);
  servo.write(30); // Rotate the servo motor to 30 degrees again
  delay(500);
}