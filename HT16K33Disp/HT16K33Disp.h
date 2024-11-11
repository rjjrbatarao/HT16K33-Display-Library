//---------------------------------
// Header File
// by: Anas Kuzechie (May 03, 2022)
//---------------------------------
#include <Wire.h>
//--------------------
//header guards
//prevents header files from multiple inclusion
#ifndef HT16K33Disp_h
#define HT16K33Disp_h

//class definition, which has public and/or private sections
class HT16K33Disp
{
    public:
        //constructor
        HT16K33Disp(const uint8_t address, TwoWire *wire = &Wire);
        //methods
        bool begin(byte brightLevel = 8);
        void Clear();
        void Char(byte digit, char c1);
        void Text(String text1);
        void Num(byte digit, int n);
        void Numdp(byte digit, int n);
	private:
		bool isConnected();
		uint8_t _address;

		TwoWire*  _wire;
};

#endif