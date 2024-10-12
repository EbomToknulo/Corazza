#include <DS3231.h>

DS3231 myRTC;
bool century = false;
bool h12Flag;
bool pmFlag;

void getTimeSerial();

void initRTC()
{
    getTimeSerial();
}

String getDateStr(bool longtime)
{
    String tmp = "";
    tmp += myRTC.getDate();
    tmp += ".";
    tmp += myRTC.getMonth(century);
    if (longtime)
    {
        tmp += ".";
        tmp += myRTC.getYear();
    }
    return tmp;
}

String getTimeStr(bool longtime)
{
    String tmp = "";
    tmp += myRTC.getHour(h12Flag, pmFlag);
    tmp += ":";
    tmp += myRTC.getMinute();
    if (longtime)
    {
        tmp += ":";
        tmp += myRTC.getSecond();
    }
    return tmp;
}

void getTimeSerial()
{
    delay(1000);
    Serial.print(myRTC.getYear(), DEC);
    Serial.print("-");
    Serial.print(myRTC.getMonth(century), DEC);
    Serial.print("-");
    Serial.print(myRTC.getDate(), DEC);
    Serial.print("  ");
    Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC); // 24-hr
    Serial.print(":");
    Serial.print(myRTC.getMinute(), DEC);
    Serial.print(":");
    Serial.println(myRTC.getSecond(), DEC);
}

/*
myRTC.setClockMode(false);  // set to 24h
        //setClockMode(true); // set to 12h

        myRTC.setYear(year);
        myRTC.setMonth(month);
        myRTC.setDate(date);
        myRTC.setDoW(dOW);
        myRTC.setHour(hour);
        myRTC.setMinute(minute);
        myRTC.setSecond(second);
        */