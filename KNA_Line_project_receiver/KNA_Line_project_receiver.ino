#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

char a[10],b[100];
int j = 0;
void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  //Wire.onReceive(receiveEvent);
  Wire.requestFrom(8,9);
  delay(700);
  //Wire.requestFrom(0x27);
}

void receiveEvent(int howMany) {
  int i = 0;
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    a[i] = c;
    Serial.print(c);
    i++;// print the character
  }
  Serial.println("");
  Serial.println(a);
  int dec = 0, rem;
  for(i = 0; i<8; i++){
    int j = 0;
    if(a[7-i] == '1'){
      rem = 1;
      j = power(2,i);
      dec += rem * j;
      }else{
        rem = 0;
        j = power(2,i);
        dec += rem * j;
      }
  }
    //Serial.println(dec);
    //Serial.println(char(dec));
    //b[j++] = char(dec);
    lcd.setCursor(0,0);
    lcd.print(char(dec));
}
int power(int x, int y){
   int res = 1;
  while(y>0){
      res = res * x;
      y = y - 1;
    }
    return res;
  }
