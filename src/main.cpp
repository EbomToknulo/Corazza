#include <Arduino.h>

int mesPrev = 0;
int signalPrev = 0;
bool menuFlag = false;
bool journalFlag = false;
bool longPress = false;
uint8_t jid = 0;
uint8_t journalLenght = 0;
uint64_t journalTime = 0;

#define journallen 20
// left button
#define but1 10
// right button
#define but2 11
// menu button
#define but3 12
#define journalTimer 2000
#define menuTimer 2000

#include <Wire.h>
#include <AlarmsArray.h>
#include <SetTime.h>
#include <Logger.h>
#include <LCD.h>
#include <Menu.h>

/*
D2-D9 входа на которые подключены оптроны
D10-D12 - входа для кнопок
A0-A1 это программный UART для OpenLog
A4-A5 стандартно SDA SCL
*/
int signal = 0;
// uint64_t currentTime = 0;
void signaltest();
int ReadPLC();
void journalCtrl();
void journalLoop();
void goBacktoLoop(uint8_t id);

void setup()
{
  // DDRB=_BV(PB4)
  //  DDRD&=~(111111<<2);
  //  DDRB&=~(1111100>>2);
  //  DDRD = DDRB | B00000000;
  //  DDRB = DDRB | B00000000;

  randomSeed(A2);

  initRTC();
  initLCD();
  initLog();
  initMenu();

  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);

  Serial.begin(9600);
  // формируем предыдущее сообщение
  signalPrev = ReadPLC();
  // ReadPLC();
  // currentTime = millis();
  getReadyScreen();
}

void loop()
{
  // ReadPLC();
  // signal = 0;
  signal = ReadPLC();
  if ((signal != 0) & (signal != signalPrev))
  {
    /*
    Serial.println("+++signal++++++++++++++");
    Serial.println(signal);
    Serial.println("+++++prev++++++++++++");
    Serial.println(signalPrev);
*/
    // значит сообщение стало другим пишем сообщение в лог и на экран
    if (!journalFlag)
      loadScreen(signal);
    writeLog(signal);
    writeShortLog(signal);
    signalPrev = signal;
  }


  journalCtrl();
  journalLoop();

  if (!journalFlag)
    signaltest();
}

/*
Тестовый метод, для тестирования работы.
Формирует журнал передавая случайные числа
*/
void signaltest()
{
  String tmp;

  int r = random(37);
  tmp = getMes(r);
  loadScreen(r);
  writeShortLog(r);
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
  uint8_t res = 0;
  int temp = 0;

  portd = PIND;
  portb = PINB;
  portd = portd >> 2;
  portb = portb << 6;
  res |= portd;
  res |= portb;
  // теперь нужна инверсия. потому что физически сигналы инвертированы из-за оптронов
  res ^= B11111111;

  temp = (int)res;

  if (temp > length)
    temp = 0;
  return temp;
}