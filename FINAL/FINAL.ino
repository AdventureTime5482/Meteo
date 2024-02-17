//МУЗЫКА-TETRIS//
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

// change this to make the song slower or faster
int tempo=144; 

// change this to whichever pin you want to use
int buzzer = 11;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
  

  NOTE_E5,2,  NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,2,   NOTE_A4,2,
  NOTE_GS4,2,  NOTE_B4,4,  REST,8, 
  NOTE_E5,2,   NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,4,   NOTE_E5,4,  NOTE_A5,2,
  NOTE_GS5,2,

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes=sizeof(melody)/sizeof(melody[0])/2; 

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


//МУЗЫКА//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2);

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


void Music(){
   // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
    chet = 4;
  }
}

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
  LCD.setCursor(0,0);
  LCD.print("Temperature:");
  LCD.print(dht.readTemperature());
  LCD.setCursor(0,1);
  LCD.print("Humidity:");
  LCD.print(dht.readHumidity());
}

void RTC(){
   if (millis() % 1000 == 0) {
      LCD.setCursor(0,0);
      LCD.print(time.gettime("d-m-Y, H:i:s, D"));
      delay(1);
   }
}

void setup() { 
  pinMode (11, OUTPUT); // подключаем пьезодинамик
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
LCD.init();
LCD.backlight();
LCD.clear();
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
//  LCD.setCursor(5,0);
//  LCD.print("REZ1");
  Meteo();
  break;
  case 2:
//  LCD.setCursor(5,0);
//  LCD.print("REZ2");
  LCD.clear();
  RTC();
  break;
  case 3:
  Music();
  break;
  case 4:
  GAME();
  break;
 }
}
