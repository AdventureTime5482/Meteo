#include <LiquidCrystal_I2C.h>


#include <DHT.h>
#include <DHT_U.h>
DHT dht(9,DHT11);

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  
dht.begin();

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(dht.readTemperature());
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(dht.readHumidity());
}
