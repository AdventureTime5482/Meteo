#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);




#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS1302,6,8,7);  // для модуля DS1302 - RST, CLK, DAT


void setup() {
   time.begin();
   time.settime(0, 30, 18, 12, 6, 20, 5); // 0  сек, 30 мин, 18 часов, 12, июня, 2020, четверг
}

void loop() {
   // если прошла 1 секунда выводим время
   if (millis() % 1000 == 0) {
      lcd.setCursor(0,0);
      lcd.print(time.gettime("d-m-Y, H:i:s, D"));
      delay(1);
   }
}
