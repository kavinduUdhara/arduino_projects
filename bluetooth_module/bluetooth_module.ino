/*

*/

void setup() {
  Serial.begin(9600); 
}

void loop() {
  char c = Serial.read();
  Serial.println(c);
}
