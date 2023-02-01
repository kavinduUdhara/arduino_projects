#include <Servo.h>

Servo servo = Servo();

int EnA = 5;
int In1 = 6;
int In2 = 7;

int EnB = 9;
int In3 = 10;
int In4 = 11;

char connection;

void setup() {
  //turn moter A
  pinMode(EnA, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);

  //turn moter B
  pinMode(EnB, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  //lowest - 100 highest - 200
  analogWrite(EnA, 150);
  analogWrite(EnB, 150);

  servo.attach(A0);

  Serial.begin(9600);
}

void loop() {
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
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void go_backward(){
  // In1 -> HIGH & In2 -> LOW ---- backward
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