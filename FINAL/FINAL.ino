#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS1302,6,8,7);  // для модуля DS1302 - RST, CLK, DAT

#include <DHT.h>
#include <DHT_U.h>
DHT dht(9,DHT11);
byte x;
int chet=1;



void Meteo(){
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(dht.readTemperature());
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(dht.readHumidity());
}

void RTC(){
   if (millis() % 1000 == 0) {
      lcd.setCursor(0,0);
      lcd.print(time.gettime("d-m-Y, H:i:s, D"));
      delay(1);
   }
}

void setup() {
  Serial.begin(9600);
 pinMode(3,INPUT_PULLUP);
 pinMode(13,OUTPUT);
lcd.init();
lcd.backlight();
lcd.clear();
dht.begin();
time.begin();
time.settime(0, 30, 18, 12, 6, 20, 5); // 0  сек, 30 мин, 18 часов, 12, июня, 2020, четверг
}

void loop() {
 x = !digitalRead(3);
 Serial.println(x);
 if(x==1){
  chet++;//chet=chet+1;
  Serial.println("Hi");
  Serial.println(chet);
  delay(200);
 }
 if(chet>3){
  chet = 1;
 }
 switch(chet){
  case 1:
//  lcd.setCursor(5,0);
//  lcd.print("REZ1");
  Meteo();
  break;
  case 2:
//  lcd.setCursor(5,0);
//  lcd.print("REZ2");
  lcd.clear();
  RTC();
  break;
  case 3:
  lcd.setCursor(5,0);
  lcd.print("REZ3");
  break;
  case 4:
  lcd.setCursor(5,0);
  lcd.print("REZ4");
  break;
 }
}
