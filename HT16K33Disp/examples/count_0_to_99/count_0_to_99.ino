//----------------------------------------
// Count form 00 to 99 on HT16K33 Display
// using HT16K33Disp library (Ver 1.0)
// by: Anas Kuzechie (May 03, 2022)
//----------------------------------------
#include <Wire.h>
#include <HT16K33Disp.h>
//-----------------------
HT16K33Disp disp(0x70);

//------------------------------------------------
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  //Wire.setClock(100000);
  disp.begin();
  disp.Clear();
  delay(1000);
  Serial.println("Started");
}
//------------------------------------------------
void loop()
{
  disp.Text("PLAY");
  delay(1000);
  disp.Clear();
  delay(1000);
  disp.Text( "C=");
  //------------------------------
  for(byte MSD=0; MSD<=9; MSD++)
  {
    disp.Num( 2, MSD);
    for(byte LSD=0; LSD<=9; LSD++)
    {
      disp.Num( 3, LSD);
      delay(200);
    }
  }
  //------------------------------
  delay(1000);
  disp.Clear();
  delay(1000);
}