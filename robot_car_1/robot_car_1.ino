#include <SoftwareSerial.h>
#include <Servo.h> // Include Servo library
#include <Ultrasonic.h> // Include Ultrasonic library

Servo servo = Servo();
Ultrasonic u = Ultrasonic(A2, A1);
SoftwareSerial BTSerial(6, 7); // RX, TX pins on Arduino

// Motor A
int EnA = 3; // Enable Pin for motor A
int In1 = 4; // Input 1 Pin for motor A
int In2 = 5; // Input 2 Pin for motor A

// Motor B
int EnB = 11; // Enable Pin for motor B
int In3 = 12; // Input 3 Pin for motor B
int In4 = 13; // Input 4 Pin for motor B

char connection;

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
  Serial.begin(9600); // Set up serial communication
  BTSerial.begin(9600); // Set up Bluetooth communication
}

void loop() {
  if (BTSerial.available() > 0) { // Check if there is data available to read
    connection = BTSerial.read(); // Read the data
    Serial.write(connection); // Print the data to the serial monitor
    Serial.write("\n");
    delay(100); // Delay to avoid flooding the serial monitor
    if (connection == '1') { // Check if the received character is '1'
      servo_motor_forward();
      if (is_road_clear()){
        go_forward();
        delay(500);
        stop();
      }
    }
    if (connection == '2'){ // backwards
      if (is_road_clear()){
        go_backward();
        delay(500);
        stop();
      }
    }
    if (connection == '3'){// turn right
      servo_motor_right();
      if (is_road_clear()){
        turn_right();
        delay(500);
        stop();
      }
    }
    if (connection == '4'){
      servo_motor_left();
      if (is_road_clear()){
        turn_left();
        delay(500);
        stop();
      }
    }
    if (connection == '5'){
      stop();
    }
  }
}

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

bool is_road_clear(){
  delay(500);
  int distance = u.distanceRead();
  if (distance  != 0){
    if (distance > 10){
      return true;
    }
    else{
      return false;
    }
  }
}