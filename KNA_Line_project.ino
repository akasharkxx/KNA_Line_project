#include <Wire.h>
int led = 2, count = 0;
String a[8];char z[12];int b[12];
void clearled(){
  led = 2;
  int i;
  for(i = 0;i < 12; i++){
    digitalWrite(led, LOW);
    led++;
    }
  }
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Wire.begin();
}

void loop() {
    count = 0;
    //digitalWrite(out, LOW);
    String inp;
    Serial.println("Enter message to send");
    while(!Serial.available()){}
    while(Serial.available()){
      inp = Serial.readString();
    }
    Serial.println(inp);
    int len = inp.length(), i, j;
    Serial.println(len);
    char input[len];
    for(i = 0; i<len-1; i++){
        input[i] = inp[i];
    }
    for(i=0;i<len-1;i++){
        dec2Bin(input[i]);
        delay(700);
        clearled();
    }
    Serial.println(" ");
    delay(2000);
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
    b[0] = a[7].toInt()^a[6].toInt()^a[4].toInt()^a[3].toInt()^a[1].toInt();
    b[1] = a[7].toInt()^a[5].toInt()^a[4].toInt()^a[2].toInt()^a[1].toInt();
    b[3] = a[6].toInt()^a[5].toInt()^a[4].toInt()^a[0].toInt();
    b[7] = a[3].toInt()^a[2].toInt()^a[1].toInt()^a[0].toInt();
    count = 0;
    for(i = 11; i >= 0;i--){
      if(i == 0 || i == 1 || i == 3 || i == 7){
        continue;
      }else{
        b[i] = a[count++].toInt();  
      }
    }
    int d;int tem[12];
    for (i = 11, d = 0; i >= 0; i--, d++)
      tem[d] = b[i];
    for (i = 0; i < 12; i++)
      b[i] = tem[i];
    for(i = 11; i >= 0;i--)
      z[i] = b[i]+'0';  
    Serial.println("Sent");
    Serial.println(z);
    led = 2;
    for(j=0;j<12;j++){
      if(z[j] == '1'){
        digitalWrite(led++, HIGH);
      }else{
        digitalWrite(led++, LOW);
      }
      delay(800);
    }
    delay(3000);
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(z,13);              // sends one byte
    Wire.endTransmission();
    delay(300);
    Serial.println(" ");
 }
