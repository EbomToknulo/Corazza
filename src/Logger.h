#include <SoftwareSerial.h>

static int messageLog[journallen];

static const int RXPin = 14U, TXPin = 15U;

SoftwareSerial ss(RXPin, TXPin);

String logDate();
void shiftArray();

void initLog()
{
    ss.begin(9600);
}

void writeLog(int str)
{
    String buf;
    buf = getMes(str);
    buf += logDate();
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
    for (uint8_t i = 19; i > 0; i--)
    {
        buf = messageLog[i - 1];
        messageLog[i] = buf;
    }
}
