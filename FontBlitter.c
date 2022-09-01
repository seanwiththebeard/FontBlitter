#include <string.h>
#include "Common.h"
#include "Charset.h"
//#link "Charset.c"

#define STROBE(addr)       __asm__ ("sta %w", addr)
#define COLS 40
#define ROWS 24
byte* HGR = (byte*)0x2000;

void SetGraphicsMode()
{
  STROBE(0xc052); // turn off mixed-mode
  STROBE(0xc054); // page 1
  STROBE(0xc057); // hi-res
  STROBE(0xc050); // set graphics mode
  memset((byte*)0x2000, 0, 0x2000); // clear page 1
}

int GetRow(byte y)
{
  return ((y/64)*0x28 + (y%8)*0x400 + ((y/8)&7)*0x80);
}

void DrawChar(byte index, byte xpos, byte ypos)
{
  byte y;
  for (y = 0; y < 8; ++y)
  {
    HGR[GetRow(ypos*8 + y) + xpos] = charset[index * 8 + y];
  }
}

void main (void)
{
  byte x, y;
  byte i = 0;
  SetGraphicsMode();
  
  while (1)
  {
  for (y= 0; y < 16; ++y)
    for (x = 0; x < 16; ++x)
      DrawChar(x + y*16, x + (i % 24), y + (i % 8));    
    //++i;
  }
}
