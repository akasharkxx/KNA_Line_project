#include <Wire.h>
char a[8];
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  int i = 0;
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    a[i++] = c;
    Serial.print(c);         // print the character
  }
  Serial.println(a);
  for(i = 0; i<8; i++){
    
    }
}
