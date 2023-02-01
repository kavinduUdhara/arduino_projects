#include <Servo.h>

Servo s = Servo();

void setup() {
  pinMode(13, OUTPUT);
  s.attach(3);
}

void loop() {
  while (true) {
    for (int x = 0; x <= 180; x++) {
      s.write(x);
      delay(50);
    }
    for (int x = 180; x >= 0; x--) {
      s.write(x);
      delay(50);
    }
  }
}