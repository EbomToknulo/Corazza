#include <DS3231.h>

DS3231 myRTC;
bool century = false;
bool h12Flag;
bool pmFlag;

void getTimeSerial();

void initRTC()
{
    if (debug) getTimeSerial();
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
    uint8_t h = 0;
    uint8_t m = 0;
    uint8_t s = 0;
    h = myRTC.getHour(h12Flag, pmFlag);
    m = myRTC.getMinute();

    if (h < 10)
    {
        tmp += "0";
        tmp += h;
    }
    else
        tmp += h;
    tmp += ":";
    if (m < 10)
    {
        tmp += "0";
        tmp += m;
    }
    else
        tmp += m;
    if (longtime)
    {
        tmp += ":";
        s = myRTC.getSecond();
        if (s < 10)
        {
            tmp += "0";
            tmp += s;
        }
        else
            tmp += s;
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

void setDate(int val)
{
    if ((val >= 0) & (val < 24))
        myRTC.setDate(val);
}

void setMonth(int val)
{
    if ((val > 0) & (val < 13))
        myRTC.setMonth(val);
}

void setYear(int val)
{
    if ((val >= 0) & (val < 51))
    {
        // val += 2000;
        Serial.println(val);
        myRTC.setYear(val);
    }
}
void setH(int val)
{
    if ((val >= 0) & (val < 24))
        myRTC.setHour(val);
}
void setM(int val)
{
    if ((val >= 0) & (val < 60))
        myRTC.setMinute(val);
}
void setS(int val)
{
    if ((val >= 0) & (val < 60))
        myRTC.setSecond(val);
}