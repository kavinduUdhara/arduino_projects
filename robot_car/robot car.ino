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

  Serial.begin(9600);
}

void loop() {
  connection = Serial.read();
  Serial.println(connection);

  if (connection == '1'){
    go_forward();
    delay(500);
    stop();
    delay(500);
  }
  if (connection == '2'){
    go_backward();
    delay(500);
    stop();
    delay(500);
  }
  if (connection == '3'){
    turn_right();
    delay(500);
    stop();
    delay(500);
  }
  if (connection == '4'){
    turn_left();
    delay(500);
    stop();
    delay(500);
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
