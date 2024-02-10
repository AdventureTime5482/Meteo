#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS1302,6,8,7);  // для модуля DS1302 - RST, CLK, DAT

#include <DHT.h>
#include <DHT_U.h>
DHT dht(9,DHT11);
byte x;
int chet=1;

int level = 1;       // переменная для отсчета уровня
int pause = 100; // переменная для задержки
byte p = 0;          // переменная для времени прыжка

// создаем массивы дракончика, дерева, камня и птицы
byte dracon[8] = {
 0b01110, 0b11011, 0b11111, 0b11100, 0b11111, 0b01100, 0b10010, 0b11011
};
byte derevo[8] = {
 0b00000, 0b00000, 0b00000, 0b11011, 0b11011, 0b11011, 0b01100, 0b01100
};
byte kamen[8] = {
 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b11111
};
byte ptica[8] = {
 0b00100, 0b00101, 0b01111, 0b11111, 0b10100, 0b00100, 0b00000, 0b00000
};


void GAME(){
 // первоначальное положение дракончика и препятствия
  byte d = 1;
  byte x = 15;
  byte y = 1;
  // выбираем препятствие, которое появится, рандомно
  byte i = random (1, 4);
  if (i == 3){ 
    y = 0;
  }else y = 1;

  while (x > 0) {
    // очищаем экран и выводим номер уровня
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(level);

    // считываем данные с кнопки и учитываем количество циклов в прыжке
    // если дакончик находится в прыжке долго - возвращаем его вниз
    if (digitalRead(4) == !LOW) d = 1;
    if (digitalRead(4) == !HIGH) d = 0;
    if (p > 3) d = 1;

    // выводим дракончика в нужной строке
    LCD.setCursor(4, d);
    LCD.print(char(0));
    // выводим препятствие
    LCD.setCursor(x, y);
    tone(10, 50);
    LCD.print(char(i));
    noTone(10);

    // если дракончик наткнулся на препятствие выводим надпись GAME OVER!
    if (x == 4 && y == d) {
      delay(400);
      tone(10, 50);
      delay(100);
      noTone(10);
      delay(100);
      tone(10, 20);
      delay(300);
      noTone(10);
      LCD.clear();
      delay(200);
      LCD.setCursor(3, 0);
      LCD.print("GAME OVER!");
      delay(600);
      LCD.clear();
      delay(400);
      LCD.setCursor(3, 0);
      LCD.print("GAME OVER!");
      delay(600);
      LCD.clear();
      LCD.setCursor(3, 1);
      LCD.print("LEVEL: ");
      LCD.print(level);
      delay(400);
      LCD.setCursor(3, 0);
      LCD.print("GAME OVER!");
      delay(3000);
      LCD.clear();
      if (d == 0) { 
        chet=1;
        break;
        }
      // начинаем игру заново, обнулив уровень игры
      LCD.setCursor(7, 0);
      LCD.print("GO!");
      delay(400);
      tone(10, 600);
      delay(100);
      noTone(10);
      LCD.clear();

      level = 0;
      pause = 400;
      p = 0;
      y = 1;
      x = 0;
      break;
    }

    // если дракончик прыгнул, издаем звук
    if (d == 0) { tone(10, 200); delay(100); noTone(10); }
    else { delay(100); }

    // если дракончик не столкнулся, то меняем положение препятствия
    // начинаем считать сколько циклов дракончик находится в прыжке
    delay(pause);
    x = x - 1;
    p = p + 1;
    if (p > 4) p = 0; 
 }

  // переходим на следующий уровень и сокращаем время задержки
  tone(10, 800);
  delay(20);
  level = level + 1;
  pause = pause - 20;
  if (pause < 0) pause = 0;
}

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
  pinMode (10, OUTPUT); // подключаем пьезодинамик
 pinMode (4, INPUT_PULLUP);     // подключаем кнопку
 digitalWrite(4, !LOW);
 LCD.init();                        // инициализация LCD дисплея
 LCD.backlight();              // включение подсветки дисплея

 // создаем символы дракончика, дерева, камня и птицы
 LCD.createChar(0, dracon);
 LCD.createChar(1, derevo);
 LCD.createChar(2, kamen);
 LCD.createChar(3, ptica);
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
  GAME();
  break;
 }
}
