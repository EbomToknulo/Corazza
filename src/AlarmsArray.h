#include <avr/pgmspace.h>
/*
struct mes
{
  int id;
  const char myStr[];
};
*/
// 37
const int length = 37;
// самое длинное сообщение это 34 знака
const char Message[][] PROGMEM= {
    "1.FR77 Emergency",
    "2.FR77 Protection guards",
    "3.IC76 Emergency",
    "2.IC76 Protection guards",
    "5.Torque sensor",
    "6.Pressure plate sensor",
    "7.Air missing",
    "8.Tray missing",
    "9.Advertising insert missing",
    "10.Foil Roll Finished",
    "11.Tear tape roll finished",
    "12.Flag rell safety",
    "13.FR77 Out range temperature",
    "14.IC76 Out range temperature",
    "15.FR77 motor thermal relay",
    "16.FR77 inverter alarm",
    "17.FR77 brake thermal relay",
    "18.IC76 motor thermal relay",
    "19.IC76 inverter alarms",
    "20.IC76 brake thermal relay",
    "21.Pump thermal relay",
    "22.FR77 infeed belt thermal",
    "23.IC76 infeed belt thermal",
    "24.Carton low level",
    "25.AD insert low level",
    "26.Wrong size grup",
    "27.Glue not ready",
    "28.Encoder FR77 alarm",
    "29.Encoder IC76 alarm",
    "30.Infeed product alarm",
    "31.Feed pusher alarm",
    "32.Groupe pusher arm alarm",
    "33.Cellofan control alarm",
    "34.Forward pusher alarm",
    "35.Lable control",
    "36.IC76 outfeed motor in failure",
    "37.Quality control - fault in box"};

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
  String res = "";
  char buffer[40];
  Serial.println("=======================================");
  for (int i = 0; i < length; i++)
  {
   // strcpy_P(buffer, (char *)pgm_read_ptr(&(Message[i])));
    Serial.print("buf= ");
    //Serial.println(buffer);
Serial.println(Message[i]);

    /*if (Message[i].id == id)
    {
      Serial.println(i + 1);
     // res = Message[i].myStr;
     // Serial.println(Message[i].myStr);
      //Serial.println(Message[i].id);
    }
    */
  }
  return res;
}