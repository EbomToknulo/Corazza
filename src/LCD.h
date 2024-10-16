void getUpScreen();
String dateTime(bool datetime);
void loadScreen(int str, byte row);
void getReadyScreen();

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

void getReadyScreen()
{
    lcd.clear();
    lcd.setCursor(17, 0);
    lcd.print("READY");
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

void loadScreen(int str, byte row)
{
    String mes = getMes(str);
    int len = mes.length();
    // lcd.clear();
    lcd.setCursor(0, row);
    if (len >= 28)
        mes += dateTime(false);
    else
        mes += dateTime(true);
    lcd.print(mes);
}

String dateTime(bool longtime)
{
    String dt;
    if (longtime)
    {
        dt += " ";
        dt += getTimeStr(false);
        dt += " ";
        dt += getDateStr(false);
    }
    else
    {
        dt += " ";
        dt += getTimeStr(false);
    }
    return dt;
}

void getJournalScreen(bool empty)
{
    lcd.clear();
    lcd.setCursor(15, 0);
    lcd.print("Journal");
    delay(4000);
    lcd.clear();

    if (!empty)
    {
        loadScreen(messageLog[0], 0);
        loadScreen(messageLog[1], 1);
    }
    else
    {
        lcd.setCursor(10, 0);
        lcd.print("Journal is Empty");
        delay(5000);
        lcd.clear();
    }
}

void getMenuScreen()
{
    lcd.clear();
    lcd.setCursor(18, 0);
    lcd.print("MENU");
    delay(4000);
}