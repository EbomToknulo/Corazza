#include <Arduino.h>
#include <Button.h>
#include <ItemToggle.h>
#include <ItemInput.h>
#include <LcdMenu.h>
#include <ItemSubMenu.h>
#include <ItemBack.h>
#include <ItemCommand.h>
#include <ItemIntRange.h>
#include <MenuScreen.h>
#include <LiquidCrystal_I2C.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <input/ButtonAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>

int mesPrev = 0;
int signalPrev = 0;
bool menuFlag = false;
bool journalFlag = false;
bool longPress = false;
bool debug = false;
int signal = 0;
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
// back button
#define but4 A2

#define journalTimer 2000
#define menuTimer 2000

LiquidCrystal_I2C lcd(0x27, 40, 2);
LiquidCrystal_I2CAdapter lcdAdapter(&lcd);
CharacterDisplayRenderer renderer(&lcdAdapter, 40, 2);
LcdMenu menu(renderer);

Button upBtn(but1);
ButtonAdapter upBtnA(&menu, &upBtn, UP);
Button downBtn(but2);
ButtonAdapter downBtnA(&menu, &downBtn, DOWN);
Button enterBtn(but3);
ButtonAdapter enterBtnA(&menu, &enterBtn, ENTER);
Button backButton(but4);
ButtonAdapter backButtonA(&menu, &backButton, BACK);

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

  if (debug)
    randomSeed(A2);

  initRTC();
  initLCD();
  initLog();
  initMenu();

  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);
  pinMode(but4, INPUT);

  Serial.begin(9600);
  if (debug)
  {
    signaltest();
    signaltest();
    signaltest();
    signaltest();
    signaltest();
    signaltest();
    signaltest();
    signaltest();
    signaltest();
    signaltest();
  }
  // формируем предыдущее сообщение
  signalPrev = ReadPLC();
  getReadyScreen();
}

void loop()
{
  if (!menuFlag)
  {
    // ReadPLC();
    // signal = 0;
    signal = ReadPLC();
    if ((signal != 0) & (signal != signalPrev))
    {
      // значит сообщение стало другим пишем сообщение в лог и на экран
      if (!journalFlag)
        loadScreen(signal);
      writeLog(signal);
      writeShortLog(signal);
      signalPrev = signal;
    }

    journalCtrl();
    journalLoop();
  }
  else
    loopMenu();
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
  // loadScreen(r);
  writeShortLog(r);
  Serial.println(tmp);
  // delay(5000);
}

/*Основной метод для чтения телеграммы от ПЛК
стоит учесть что все входы подтянуты резисторами к + питания
поэтому потом их надо инвертировать
UPD на сапал 1 почему то постоянно мигает выход 0.6. Видимо пытались сделать строб для панели.
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
  res &= B10111111;

  temp = (int)res;

  if (temp > length)
    temp = 0;
  return temp;
}