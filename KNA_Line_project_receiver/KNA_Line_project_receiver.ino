#include <Wire.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int power(int x, int y){
   int res = 1;
  while(y>0){
      res = res * x;
      y = y - 1;
    }
    return res;
  }
char a[12],b[8];int p[4];
int j = 0;
void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Waiting");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  Wire.requestFrom(8,13);
  delay(700);
}

void receiveEvent(int howMany) {
  int i = 0;
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    a[i] = c;
    i++;
  }
  Serial.println("Received data");
  Serial.println(a);
  lcd.print(a);
  p[0] = (a[11]-'0')^(a[9]-'0')^(a[7]-'0')^(a[5]-'0')^(a[3]-'0')^(a[1]-'0');
  p[1] = (a[10]-'0')^(a[9]-'0')^(a[6]-'0')^(a[5]-'0')^(a[2]-'0')^(a[1]-'0');
  p[2] = (a[8]-'0')^(a[7]-'0')^(a[6]-'0')^(a[5]-'0')^(a[0]-'0');
  p[3] = (a[4]-'0')^(a[3]-'0')^(a[2]-'0')^(a[1]-'0');
  int dec = 0, rem;
  for(i = 0; i < 4; i++){
     dec += power(2,i)*p[i];
     Serial.println(p[i]);
  }dec--;
  if(dec < 0){
    a[dec] = ~(a[dec]-'0') + '0';
    }
  Serial.println(dec);
  int j = 0;
  b[7] = a[9];
  b[6] = a[7];
  b[5] = a[6];
  b[4] = a[5];
  b[3] = a[3];
  b[2] = a[2];
  b[1] = a[1];
  b[0] = a[0];
  Serial.println(b);
  dec = 0;
  for(i = 0; i<8; i++){
    int j = 0;
    if(b[7-i] == '1'){
      rem = 1;
      j = power(2,i);
      dec += rem * j;
      }else{
        rem = 0;
        j = power(2,i);
        dec += rem * j;
      }
  }
    Serial.println(dec);
    delay(600);lcd.clear();
    Serial.println(char(dec));
    lcd.print(char(dec));
}
