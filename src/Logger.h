#include <SoftwareSerial.h>

static const int RXPin = 14U, TXPin = 15U;

SoftwareSerial ss(RXPin, TXPin);

void initLog(){
    ss.begin(9600);
}

void writeLog(int str){

}
