#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

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


void setup() {
  Serial.begin(9600);
 pinMode(3,INPUT_PULLUP);
 pinMode(13,OUTPUT);
lcd.init();
lcd.backlight();
lcd.clear();
dht.begin();
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
  lcd.setCursor(5,0);
  lcd.print("REZ2");
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
