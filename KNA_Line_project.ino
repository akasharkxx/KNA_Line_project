#include <Wire.h>
int led = 2, out = 10;
char a[8];
void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(out, OUTPUT);
}

void loop() {
    digitalWrite(out, LOW);
    String inp;
    Serial.println("Enter message to send");
    while(!Serial.available()){}
    while(Serial.available()){
      inp = Serial.readString();
    }
    Serial.println(inp);
    int len = inp.length(), i, j;
  // Serial.println(len);
    char input[len];
    for(i = 0; i<len; i++){
        input[i] = inp[i];
    }
    int b[len];
    for(i=0;i<len-1;i++){
        dec2Bin(input[i]);
        delay(3000);
        clearled();
    }Serial.println(" ");
    delay(8000);
}
void dec2Bin(int x)
{
    int i,j;
    for(i=0;i<8;i++){
      int p = 7-i;
      if((x%2) == 1){
        a[p] = '1';
      }else{
        a[p] = '0';
      }
        x /= 2;
    }
    led = 2;
    for(j=0;j<8;j++){
      if(a[j] == '1'){
        digitalWrite(led, HIGH);
      }else{
        digitalWrite(led, LOW);
      }led++;
      Serial.println(a[j]);
      delay(1000);
    }Wire.beginTransmission(8); // transmit to device #8
     Wire.write(a,9);              // sends one byte
     Wire.endTransmission();
     delay(500);
    Serial.println(" ");
}
void clearled(){
  led = 2;
  int i;
  for(i = 0;i < 8; i++){
    digitalWrite(led, LOW);
    led++;
    }
  }
