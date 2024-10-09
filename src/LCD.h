#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 40, 2);

void getUpScreen();
String dateTime(bool datetime);

void initLCD()
{
    lcd.init();
    lcd.backlight();
    getUpScreen();
}

void getUpScreen()
{
    lcd.setCursor(10, 0);
    lcd.print("Corazza Panel");
    lcd.setCursor(30, 1);
    lcd.print("by ET");
    delay(4000);
    lcd.clear();
}

void loadScreen(int str)
{
    String mes = getMes(str);
    int len = mes.length();
    // пишем текущее сообщение
    lcd.clear();
    lcd.setCursor(0, 0);
    if (len >= 28)
        mes += dateTime(false);
    else
        mes += dateTime(true);
    lcd.print(mes);
    // пишем предыдущее сообщение
    mes = getMes(mesPrev);
    len = mes.length();
    lcd.setCursor(0, 1);
    if (len >= 28)
        mes += dateTime(false);
    else
        mes += dateTime(true);
    lcd.print(mes);
    mesPrev = str;
}

String dateTime(bool datetime)
{
    String dt;
    if (datetime)
    {
        dt += " ";
        dt += getTimeStr(true);
        dt += " ";
        dt += getDateStr(true);
    }
    else
    {
        dt += " ";
        dt += getTimeStr(true);
    }
    return dt;
}