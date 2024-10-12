#include <avr/pgmspace.h>

const char alarm1[] PROGMEM = "1.FR77 Emergency";
const char alarm2[] PROGMEM = "2.FR77 Protection guards";
const char alarm3[] PROGMEM = "3.IC76 Emergency";
const char alarm4[] PROGMEM = "4.IC76 Protection guards";
const char alarm5[] PROGMEM = "5.Torque sensor";
const char alarm6[] PROGMEM = "6.Pressure plate sensor";
const char alarm7[] PROGMEM = "7.Air missing";
const char alarm8[] PROGMEM = "8.Tray missing";
const char alarm9[] PROGMEM = "9.Advertising insert missing";
const char alarm10[] PROGMEM = "10.Foil Roll Finished";
const char alarm11[] PROGMEM = "11.Tear tape roll finished";
const char alarm12[] PROGMEM = "12.Flag rell safety";
const char alarm13[] PROGMEM = "13.FR77 Out range temperature";
const char alarm14[] PROGMEM = "14.IC76 Out range temperature";
const char alarm15[] PROGMEM = "15.FR77 motor thermal relay";
const char alarm16[] PROGMEM = "16.FR77 inverter alarm";
const char alarm17[] PROGMEM = "17.FR77 brake thermal relay";
const char alarm18[] PROGMEM = "18.IC76 motor thermal relay";
const char alarm19[] PROGMEM = "19.IC76 inverter alarms";
const char alarm20[] PROGMEM = "20.IC76 brake thermal relay";
const char alarm21[] PROGMEM = "21.Pump thermal relay";
const char alarm22[] PROGMEM = "22.FR77 infeed belt thermal";
const char alarm23[] PROGMEM = "23.IC76 infeed belt thermal";
const char alarm24[] PROGMEM = "24.Carton low level";
const char alarm25[] PROGMEM = "25.AD insert low level";
const char alarm26[] PROGMEM = "26.Wrong size grup";
const char alarm27[] PROGMEM = "27.Glue not ready";
const char alarm28[] PROGMEM = "28.Encoder FR77 alarm";
const char alarm29[] PROGMEM = "29.Encoder IC76 alarm";
const char alarm30[] PROGMEM = "30.Infeed product alarm";
const char alarm31[] PROGMEM = "31.Feed pusher alarm";
const char alarm32[] PROGMEM = "32.Groupe pusher arm alarm";
const char alarm33[] PROGMEM = "33.Cellofan control alarm";
const char alarm34[] PROGMEM = "34.Forward pusher alarm";
const char alarm35[] PROGMEM = "35.Lable control";
const char alarm36[] PROGMEM = "36.IC76 outfeed motor in failure";
const char alarm37[] PROGMEM = "37.Quality control - fault in box";
// 37
static const int length = 37;
char buffer[35];
// самое длинное сообщение это 34 знака
const char *const Message[] PROGMEM = {
    alarm1,
    alarm2,
    alarm3,
    alarm4,
    alarm5,
    alarm6,
    alarm7,
    alarm8,
    alarm9,
    alarm10,
    alarm11,
    alarm12,
    alarm13,
    alarm14,
    alarm15,
    alarm16,
    alarm17,
    alarm18,
    alarm19,
    alarm20,
    alarm21,
    alarm22,
    alarm23,
    alarm24,
    alarm25,
    alarm26,
    alarm27,
    alarm28,
    alarm29,
    alarm30,
    alarm31,
    alarm32,
    alarm33,
    alarm34,
    alarm35,
    alarm36,
    alarm37};

/*
    {1, "1.FR77 Emergency"},
    {2, "2.FR77 Protection guards"},
    {3, "3.IC76 Emergency"},
    {4, "2.IC76 Protection guards"},
    {5, "5.Torque sensor"},
    {6, "6.Pressure plate sensor"},
    {7, "7.Air missing"},
    {8, "8.Tray missing"},
    {9, "9.Advertising insert missing"},
    {10, "10.Foil Roll Finished"},
    {11, "11.Tear tape roll finished"},
    {12, "12.Flag rell safety"},
    {13, "13.FR77 Out range temperature"},
    {14, "14.IC76 Out range temperature"},
    {15, "15.FR77 motor thermal relay"},
    {16, "16.FR77 inverter alarm"},
    {17, "17.FR77 brake thermal relay"},
    {18, "18.IC76 motor thermal relay"},
    {19, "19.IC76 inverter alarms"},
    {20, "20.IC76 brake thermal relay"},
    {21, "21.Pump thermal relay"},
    {22, "22.FR77 infeed belt thermal"},
    {23, "23.IC76 infeed belt thermal"},
    {24, "24.Carton low level"},
    {25, "25.AD insert low level"},
    {26, "26.Wrong size grup"},
    {27, "27.Glue not ready"},
    {28, "28.Encoder FR77 alarm"},
    {29, "29.Encoder IC76 alarm"},
    {30, "30.Infeed product alarm"},
    {31, "31.Feed pusher alarm"},
    {32, "32.Groupe pusher arm alarm"},
    {33, "33.Cellofan control alarm"},
    {34, "34.Forward pusher alarm"},
    {35, "35.Lable control"},
    {36, "36.IC76 outfeed motor in failure"},
    {37, "37.Quality control - fault in box"}};
*/
String getMes(int id)
{
  if (id <= length)
    // String res = "";
    strcpy_P(buffer, (char *)pgm_read_ptr(&(Message[id-1])));

  return buffer;
}