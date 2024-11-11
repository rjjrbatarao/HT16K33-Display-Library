//------------------------------------------
// DHT22 Temp & Humidity on HT16K33 Display
// using HT16K33Disp library (Ver 1.0)
// by: Anas Kuzechie (May 03, 2022)
//------------------------------------------
#include <Wire.h>
#include <DHT.h>
#include <HT16K33Disp.h>
//-----------------------
HT16K33Disp disp(0x70);
DHT dht(8, DHT22);
//-----------------------
byte add = 0x70;
float temp; int humidity;
int temp_LSD, temp_MSD, temp_fraction, hum_LSD, hum_MSD;
unsigned long millisCapture = millis(), myDelay = 30000;
//------------------------------------------------------
void setup()
{
  Wire.begin();
  dht.begin();
  disp.begin();
  disp.Clear();
}
//------------------------------------------------------
void loop()
{
  delay(2000);
  disp_temp();
  if(millis() - millisCapture > myDelay)
  {
    disp.Clear(); delay(1000);
    disp_hum(); delay(3000);
    disp.Clear();
  }
}
//------------------------------------------------------
void disp_temp()
{
  temp = dht.readTemperature();
  temp_MSD = int(temp)/10;
  temp_LSD = int(temp)%10;
  temp_fraction = (temp - int(temp))*10;
  //----------------------------------------------------
  disp.Num( 0, temp_MSD);
  disp.Numdp( 1, temp_LSD);
  disp.Num( 2, temp_fraction);
  disp.Char( 3, 'C');
}
//------------------------------------------------------
void disp_hum()
{
  humidity = dht.readHumidity();
  hum_MSD = humidity/10;
  hum_LSD = humidity%10;
  //----------------------------------------------------
  disp.Char( 0, 'H');
  disp.Num( 1, hum_MSD);
  disp.Num( 2, hum_LSD);
  disp.Char( 3, 'P');
  //----------------------------------------------------
  millisCapture = millis();
}