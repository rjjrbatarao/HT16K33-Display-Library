//---------------------------------
// Source File
// by: Anas Kuzechie (May 03, 2022)
//---------------------------------
#include <Arduino.h>
#include <HT16K33Disp.h>
//------------------------------------------------------------
// Constructor
//------------------------------------------------------------
HT16K33Disp::HT16K33Disp(const uint8_t address, TwoWire *wire) {
  _address = address;
  _wire = wire;
}
//------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------
uint16_t convert(char);
uint16_t convertdp(int);
//------------------------------------------------------------
// Methods
//------------------------------------------------------------
bool HT16K33Disp::begin(byte brightLevel)
{
	if (! isConnected()) return false;
    _wire->beginTransmission(_address);
    _wire->write(0x21);               //normal operation mode
    _wire->endTransmission();
    //--------------------------------------------------------
    _wire->beginTransmission(_address);
    _wire->write(0x81);               //display ON, blinking OFF
    _wire->endTransmission();	
    //--------------------------------------------------------
    _wire->beginTransmission(_address);
    _wire->write(0xE0 | brightLevel);   //brightness level
    _wire->endTransmission();

	return true;
}
bool HT16K33Disp::isConnected()
{
  _wire->beginTransmission(_address);
  return (0 == _wire->endTransmission());
}

//------------------------------------------------------------
void HT16K33Disp::Char(byte digit, char c1)
{
    uint16_t c2; 
    c2 = convert(c1);
    //------------------------------
    _wire->beginTransmission(_address);
    _wire->write(digit*2);
    _wire->write(c2 & 0x00FF);
    _wire->write((c2 & 0xFF00) >> 8);
    _wire->endTransmission();
}
//------------------------------------------------------------
void HT16K33Disp::Text(String text1)
{
    char text2[5]; uint16_t c2;
    text1.toCharArray(text2, 5);
    
    for(byte i=0; i<text1.length(); i++)
    {
        c2 = convert(text2[i]);
        //------------------------------
        _wire->beginTransmission(_address);
        _wire->write(i*2);
        _wire->write(c2 & 0x00FF);
        _wire->write((c2 & 0xFF00) >> 8);
        _wire->endTransmission();
        delay(100);
    } 
}
//------------------------------------------------------------
void HT16K33Disp::Num(byte digit, int n)
{
    switch(n)
    {
      case 0: Char( digit, '0'); break;
      case 1: Char( digit, '1'); break;
      case 2: Char( digit, '2'); break;
      case 3: Char( digit, '3'); break;
      case 4: Char( digit, '4'); break;
      case 5: Char( digit, '5'); break;
      case 6: Char( digit, '6'); break;
      case 7: Char( digit, '7'); break;
      case 8: Char( digit, '8'); break;
      case 9: Char( digit, '9');
    }
}
//------------------------------------------------------------
void HT16K33Disp::Numdp(byte digit, int n)
{
    uint16_t c2;   
    c2 = convertdp(n);
    //------------------------------
    _wire->beginTransmission(_address);
    _wire->write(digit*2);
    _wire->write(c2 & 0x00FF);
    _wire->write((c2 & 0xFF00) >> 8);
    _wire->endTransmission();
}
//------------------------------------------------------------
void HT16K33Disp::Clear()
{
    for(byte i=0; i<=3; i++) Char( i, ' ');
}
//------------------------------------------------------------
// Functions
//------------------------------------------------------------
uint16_t convert(char c)
{
    uint16_t c2;
    switch(c)
    {
        case ' ': c2 = 0x0000; break;
        case '.': c2 = 0x4000; break;
        case '+': c2 = 0x12C0; break;
        case '-': c2 = 0x00C0; break;
        case '*': c2 = 0x3FC0; break;
        case '/': c2 = 0x0C00; break;
        case '=': c2 = 0x00C8; break;
        case '>': c2 = 0x0900; break;
        case '<': c2 = 0x2400; break;
        case '[': c2 = 0x0039; break;
        case ']': c2 = 0x000F; break;
        //---------------------------
        case '0': c2 = 0x0C3F; break;
        case '1': c2 = 0x0406; break;
        case '2': c2 = 0x00DB; break;
        case '3': c2 = 0x008F; break;
        case '4': c2 = 0x00E6; break;
        case '5': c2 = 0x00ED; break;
        case '6': c2 = 0x00FD; break;
        case '7': c2 = 0x0007; break;
        case '8': c2 = 0x00FF; break;
        case '9': c2 = 0x00EF; break;
        //---------------------------
        case 'A': c2 = 0x00F7; break;
        case 'B': c2 = 0x128F; break;
        case 'C': c2 = 0x0039; break;
        case 'D': c2 = 0x120F; break;
        case 'E': c2 = 0x00F9; break;
        case 'F': c2 = 0x00F1; break;
        case 'G': c2 = 0x00BD; break;
        case 'H': c2 = 0x00F6; break;
        case 'I': c2 = 0x1209; break;
        case 'J': c2 = 0x001E; break;
        case 'K': c2 = 0x2470; break;
        case 'L': c2 = 0x0038; break;
        case 'M': c2 = 0x0536; break;
        case 'N': c2 = 0x2136; break;
        case 'O': c2 = 0x003F; break;
        case 'P': c2 = 0x00F3; break;
        case 'Q': c2 = 0x203F; break;
        case 'R': c2 = 0x20F3; break;
        case 'S': c2 = 0x018D; break;
        case 'T': c2 = 0x1201; break;
        case 'U': c2 = 0x003E; break;
        case 'V': c2 = 0x0C30; break;
        case 'W': c2 = 0x2836; break;
        case 'X': c2 = 0x2D00; break;
        case 'Y': c2 = 0x1500; break;
        case 'Z': c2 = 0x0C09;
    }
    return c2;
}
//------------------------------------------------------------
uint16_t convertdp(int n)
{
    uint16_t c2;
    switch(n)
    {
        case 0: c2 = 0x0C3F|0x4000; break;
        case 1: c2 = 0x0406|0x4000; break;
        case 2: c2 = 0x00DB|0x4000; break;
        case 3: c2 = 0x008F|0x4000; break;
        case 4: c2 = 0x00E6|0x4000; break;
        case 5: c2 = 0x00ED|0x4000; break;
        case 6: c2 = 0x00FD|0x4000; break;
        case 7: c2 = 0x0007|0x4000; break;
        case 8: c2 = 0x00FF|0x4000; break;
        case 9: c2 = 0x00EF|0x4000;
    }
    return c2;
}