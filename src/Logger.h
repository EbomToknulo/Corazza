#include <SoftwareSerial.h>

static int messageLog[journallen];

static const int RXPin = A1, TXPin = A0;

SoftwareSerial ss(RXPin, TXPin);

String logDate();
void shiftArray();
void messageArrayTest();

void initLog()
{
    ss.begin(9600);
    String buf;
    buf += getTimeStr(true);
    buf += " ";
    buf += getDateStr(true);
    ss.println(buf);
}

void writeLog(int str)
{
    String buf;
   // buf += (String)str;
    buf += logDate();
    buf = getMes(str);
    ss.println(buf);
}

void writeShortLog(int str)
{
    shiftArray();
    messageLog[0] = str;
}

String logDate()
{
    String dt;
    dt += " ";
    dt += getTimeStr(true);
    dt += " ";
    dt += getDateStr(true);
    return dt;
}

void shiftArray()
{
    int buf = 0;
    for (uint8_t i = (journallen - 1); i > 0; i--)
    {
        buf = messageLog[i - 1];
        messageLog[i] = buf;
    }
}

uint8_t arrayLength()
{
    int tmp = 0;
    for (uint8_t i = 0; i < journallen - 1; i++)
    {
        if (messageLog[i] != 0)
            tmp++;
    }

    if (debug)
    {
        Serial.print("lenght array= ");
        Serial.println(tmp);
        messageArrayTest();
    }
    return tmp;
}

void messageArrayTest()
{
    for (uint8_t i = 0; i < journallen - 1; i++)
    {
        Serial.print("messageLog= ");
        Serial.println(messageLog[i]);
    }
}