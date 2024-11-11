//--------------------------------------------
// DHT22 Temp & Humidity on 2 HT16K33 Displays
// using HT16K33Disp library (Ver 1.0)
// by: Anas Kuzechie (May 03, 2022)
//--------------------------------------------
#include <Wire.h>
#include <DHT.h>
#include <HT16K33Disp.h>
//-----------------------
HT16K33Disp disp1(0x70);
HT16K33Disp disp2(0x71);
DHT dht(8, DHT22);
//-----------------------

float temp; int humidity;
int temp_LSD, temp_MSD, temp_fraction, hum_LSD, hum_MSD;
unsigned long millisCapture = millis(), myDelay = 30000;
//------------------------------------------------------
void setup()
{
  Wire.begin();
  dht.begin();
  disp1.begin();
  disp2.begin();
  //-------------------------------------------
  disp1.Clear(); disp2.Clear();
  delay(1000);
  disp1.Text("DHT1"); disp2.Text( "1/22");
  delay(2000);
  disp1.Clear(); disp2.Clear();
}
//------------------------------------------------------
void loop()
{
  delay(2000);
  disp_temp(); disp_hum();
  //----------------------------------------------------
  if(millis() - millisCapture > myDelay) disp_message();
}
//------------------------------------------------------
void disp_temp()
{
  temp = dht.readTemperature();
  temp_MSD = int(temp)/10;
  temp_LSD = int(temp)%10;
  temp_fraction = (temp - int(temp))*10;
  //------------------------------------
  disp1.Num(0, temp_MSD);
  disp1.Numdp( 1, temp_LSD);
  disp1.Num( 2, temp_fraction);
  disp1.Char( 3, 'C');
}
//------------------------------------------------------
void disp_hum()
{
  humidity = dht.readHumidity();
  hum_MSD = humidity/10;
  hum_LSD = humidity%10;
  //----------------------------
  disp2.Char( 0, 'H');
  disp2.Num( 1, hum_MSD);
  disp2.Num( 2, hum_LSD);
  disp2.Char( 3, 'P');
}
//------------------------------------------------------
void disp_message()
{
  disp1.Clear(); disp2.Clear();
  delay(1000);
  disp1.Text( "TEMP"); disp2.Text( " AND");
  delay(2000);
  disp1.Clear(); disp2.Clear();
  delay(1000);
  disp1.Text( "HUMI"); disp2.Text( "DITY");
  delay(2000);
  disp1.Clear(); disp2.Clear();
  //-------------------------------------------
  millisCapture = millis();
}