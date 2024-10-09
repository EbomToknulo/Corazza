int mesPrev = 0;
int signalPrev = 0;

#include <Arduino.h>
#include <Wire.h>
#include <AlarmsArray.h>
#include <SetTime.h>
#include <LCD.h>
#include <Logger.h>
#include <Menu.h>

#define but1 10
#define but2 11
#define but3 12
/*
D2-D9 входа на которые подключены оптроны
D10-D12 - входа для кнопок
A0-A1 это программный UART для OpenLog
A4-A5 стандартно SDA SCL
*/


int signal = 0;

void signaltest();
int ReadPLC();

void setup()
{
  // DDRB=_BV(PB4)
  //  DDRD&=~(111111<<2);
  //  DDRB&=~(1111100>>2);
  //  DDRD = DDRB | B00000000;
  //  DDRB = DDRB | B00000000;

  randomSeed(A2);

  //initRTC();
  initLCD();
  //initLog();
 // initMenu();

  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);

  Serial.begin(9600);
  // формируем предыдущее сообщение
  signalPrev = ReadPLC();
  // ReadPLC();
}

void loop()
{
  // ReadPLC();
  signal = 0;
 // signal = ReadPLC();
  if (signal != signalPrev)
  {
    // значит сообщение стало другим пишем сообщение в лог и на экран
   // loadScreen(signal);
   // writeLog(signal);
    signalPrev = signal;
  }

  signaltest();
}

void signaltest()
{
  String tmp;

  int r = random(37);
  tmp = getMes(r);
  //loadScreen(r);
  Serial.println(tmp);
  delay(5000);
}

/*Основной метод для чтения телеграммы от ПЛК
стоит учесть что все входы подтянуты резисторами к + питания
поэтому потом их надо инвертировать
*/
int ReadPLC()
{
  /*
  1 часть это порт D ( надо двинуть на 2 позиции вправо)
  2 часть это порт B (нужны только биты 0 и 1)
  */
  uint8_t portd;
  uint8_t portb;
  uint8_t res=0;
  int temp = 0;

  portd = PIND;
  portb = PINB;
  portd = portd >> 2;
  portb = portb << 6;
  res |= portd;
  res |= portb;
  // теперь нужна инверсия.
  res ^= B11111111;

  Serial.println(res);
  Serial.println("+++++++++++++++++");

  temp = (int)res;
  Serial.println(temp);
  Serial.println("================");
  return temp;
}