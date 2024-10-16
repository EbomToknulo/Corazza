void goBacktoLoop(uint8_t id);
void journalCtrl();
void journalLoop();
void callbackInt(int value);
void callDay(int value);
void callMonth(int value);
void callYear(int value);
void callH(int value);
void callM(int value);
void callS(int value);
void callExit();
void callJournal();

uint8_t date;
uint8_t month;
uint8_t year;

extern MenuScreen *settingsScreenTime;
// extern MenuScreen *settingsScreenDate;

/*Изначально писал только функцию под отображение журнала,
потом прикрутил меню с редактированием времени, название оставил прежнее.
чтобы не делать рефакторинг.
По факту функция включает меню
*/
void journalCtrl()
{
    if (digitalRead(but3))
    {
        // инициализация при нажатии на кнопку
        if (!longPress)
        {
            journalTime = millis();
            longPress = true;
            if (debug)
                Serial.println("longpress");
        }
        else
        {
            if (millis() >= (journalTime + journalTimer))
            {
                // время вышло, запускаем журнал
                longPress = false;
                // journalFlag = !journalFlag;
                menuFlag = !menuFlag;
                if (debug)
                    Serial.println("menu act");
                if (menuFlag)
                {
                    getMenuScreen();
                    menu.reset();
                    menu.show();
                    menu.refresh();
                    /*
                    journalLenght = arrayLength();
                    if (journalLenght == 0)
                    {

                            journalFlag = false;
                    }
                    else
                        getJournalScreen(false);
                        */
                }
                else
                {
                    if (debug)
                        Serial.println("goback");
                    goBacktoLoop(0);
                    delay(3000);
                }
            }
        }
    }
    else
    {
        if (longPress)
        {
            longPress = false;
            if (debug)
                Serial.println("butunpress");
        }
    }
}

void journalLoop()
{
    if (journalFlag)
    {
        if (digitalRead(but1))
        {
            jid++;
            delay(500);
            if (jid > (journalLenght - 1))
            {
                jid = (journalLenght - 1);
            }
            goBacktoLoop(jid);
            if (debug)
                Serial.println("++");
        }
        if (digitalRead(but2))
        {
            if (jid <= (0))
            {
                jid = 0;
            }
            else
                jid--;
            delay(500);
            goBacktoLoop(jid);
            if (debug)
                Serial.println("---");
        }
    }
}

void goBacktoLoop(uint8_t id)
{
    lcd.clear();
    loadScreen(messageLog[id], 0);
    if (id < (journallen - 1))
        loadScreen(messageLog[id + 1], 1);
}

// Declare the call back function
void toggleBacklight(bool isOn);

// clang-format off
MENU_SCREEN(mainScreen, mainItems,
    ITEM_COMMAND("Journal", callJournal),
    ITEM_TOGGLE("Backlight", toggleBacklight),
    ITEM_SUBMENU("SetTime", settingsScreenTime),
    ITEM_COMMAND("Exit", callExit)
    );

// Create submenu and precise its parent
MENU_SCREEN(settingsScreenTime, settingsItems,
            ITEM_INT_RANGE("Hour", 0, 23, 15, callH, (const char *)"hh"),
            ITEM_INT_RANGE("Minute>", 0, 59, 15, callM, (const char *)"mm"),
            ITEM_INT_RANGE("Seconds>", 0, 59, 15, callS, (const char *)"ss"),
            ITEM_INT_RANGE("Day", 1, 31, 1, callDay, (const char *)"dd"),
            ITEM_INT_RANGE("Month>", 1, 12, 1, callMonth, (const char *)"mm"),
            ITEM_INT_RANGE("Year>", 0, 50, 24, callYear, (const char *)"yy"),
            ITEM_BACK());

void initMenu()
{
    upBtn.begin();
    downBtn.begin();
    enterBtn.begin();
    backButton.begin();
    renderer.begin();
    menu.setScreen(mainScreen);
    menu.hide();
}

void loopMenu()
{
    upBtnA.observe();
    downBtnA.observe();
    enterBtnA.observe();
    backButtonA.observe();
    if(debug) Serial.print("l");
}

void toggleBacklight(bool isOn)
{
    lcdAdapter.setBacklight(isOn);
}

void callDay(int value)
{
    setDate(value);
}

void callMonth(int value)
{
    setMonth(value);
}

void callYear(int value)
{
    setYear(value);
}

void callH(int value)
{
    setH(value);
}

void callM(int value)
{
    setM(value);
}

void callS(int value)
{
    setS(value);
}

void callExit()
{
//menu.reset();
 menu.hide();
 menuFlag=false;
 if (debug) Serial.println("exit");
}

void callJournal()
{
   journalLenght = arrayLength();
//menu.reset();
    menu.hide();
    menuFlag=false;
    journalFlag=true;
    journalLenght = arrayLength();

      if (journalLenght == 0)
        {
          journalFlag = false;
          getJournalScreen(true);
         }
          else
           getJournalScreen(false);
 if (debug) Serial.println("journal");
}