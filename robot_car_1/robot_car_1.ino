#include <Servo.h>
//servo motor
Servo servo = Servo();

int EnA = 5;
int In1 = 6;
int In2 = 7;

int EnB = 9;
int In3 = 10;
int In4 = 11;

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
  analogWrite(EnA, 150);
  analogWrite(EnB, 150);

  //for bluetooth signals
  Serial.begin(9600);
}

void loop() {
  /*
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
  */
}

void go_forward(){
  //go forward | In1 -> HIGH | In2 -> LOW || In3 -> LOW | In4 -> HIGH
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void go_backward(){
  //go backward | In1 -> HIGH | In2 -> LOW || In3 -> LOW | In4 -> HIG
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