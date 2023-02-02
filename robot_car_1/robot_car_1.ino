/*
  Project: Arduino Controlled Car with Servo Motor, Ultrasonic Sensor and bluetooth moduler
  Purpose: This code provides to control an arduino-powered car with a servo motor and ultrasonic sensor. The car can receive commands through Bluetooth to move forward, backward, turn left, turn right and stop.
  Function: The servo motor acts as the steering mechanism, while the ultrasonic sensor is used for obstacle detection.
*/

#include <Servo.h> // Include Servo library
#include <Ultrasonic.h> // Include Ultrasonic library
/*The Servo.h library is used to control a servo motor in the project. It provides functions for setting the servo motor's position, speed, and other properties.

The Ultrasonic.h library is used to measure the distance between the ultrasonic sensor and an object in front of it. It provides functions to trigger the ultrasonic sensor and receive the time required for the echo signal to return. This time can then be used to calculate the distance to the object.

Both of these libraries simplify the implementation of these components in the project, making it easier to control the servo motor and measure distance with the ultrasonic sensor.*/

// Servo Motor
Servo servo = Servo(); // Create an object for the servo motor
// Ultrasonic Sensor
Ultrasonic u = Ultrasonic(A2, A1);  // ultrasonic sensor is connected to pins A2 (Trig Pin) and A1 (Echo Pin)

// L298N Motor Driver
// Motor A
int EnA = 3; // Enable Pin for motor A
int In1 = 4; // Input 1 Pin for motor A
int In2 = 5; // Input 2 Pin for motor A

// Motor B
int EnB = 11; // Enable Pin for motor B
int In3 = 12; // Input 3 Pin for motor B
int In4 = 13; // Input 4 Pin for motor B
/*...use of the library disables analogWrite() (PWM) functionality on pins 9 and 10,... 
ref: https://stackoverflow.com/questions/75318922/motor-driver-isnt-working-properly-while-servo-attacha0-line-present-in-the*/

char connection;

void setup() {
  servo.attach(A0); // servo motor is connected to pin A0 

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

void loop() {
  //read bluetooth connection signels
  connection = Serial.read();
  Serial.println(connection);

  if (connection == '1'){
    servo_motor_forward();
    go_forward();
    after_action();
  }
  if (connection == '2'){
    go_backward();
    after_action();
  }
  if (connection == '3'){
    servo_motor_right();
    turn_right();
    after_action();
  }
  if (connection == '4'){
    servo_motor_left();
    turn_left();
    after_action();
  }
  if (connection == '5'){
    stop();
    delay(500);
  }
}

void go_forward(){
  //go forward | In1 -> HIGH | In2 -> LOW || In3 -> LOW | In4 -> HIGH
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void go_backward(){
  //go backward | In1 -> LOW | In2 -> HIGH  || In3 -> HIGH | In4 -> LOW
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void stop(){
  //stop | * -> LOW
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