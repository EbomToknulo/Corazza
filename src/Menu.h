
void goBacktoLoop(uint8_t id);
void journalCtrl();
void journalLoop();

void journalCtrl()
{
    if (digitalRead(but3))
    {
        // инициализация при нажатии на кнопку
        if (!longPress)
        {
            journalTime = millis();
            longPress = true;
            Serial.println("longpress");
        }
        else
        {
            if (millis() >= (journalTime + journalTimer))
            {
                // время вышло, запускаем журнал
                longPress = false;
                journalFlag = !journalFlag;
                Serial.println("journal");
                if (journalFlag)
                {
                    journalLenght = arrayLength();
                    if (journalLenght == 0)
                    {
                        getJournalScreen(true);
                        journalFlag = false;
                    }
                    else
                        getJournalScreen(false);
                }
                else
                {
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

void initMenu()
{
    
}