#include <string.h>
#include "Common.h"
#include "Charset.h"
//#link "Charset.c"

#define STROBE(addr)       __asm__ ("sta %w", addr)
#define COLS 40
#define ROWS 24
byte* HGR = (byte*)0x2000;
byte* HGRBuffer = (byte*)0x4000;
int RowsHGR[192];

byte BufferFlip = 0;

void FlipBuffer()
{
  if (BufferFlip)
  {
    HGR = (byte*)0x2000;
    --BufferFlip;
    STROBE(0xc054); // page 1
  }
  else
  {
    HGR = (byte*)0x4000;
    ++BufferFlip;
    STROBE(0xc055); // page 1
  }
  
}

void SetLookupTable()
{
  byte y;
  for (y = 0; y < 192; ++y)
    RowsHGR[y] = (y/64)*0x28 + (y%8)*0x400 + ((y/8)&7)*0x80;
}

void SetGraphicsMode()
{
  STROBE(0xc052); // turn off mixed-mode
  STROBE(0xc054); // page 1
  STROBE(0xc057); // hi-res
  STROBE(0xc050); // set graphics mode
  //memset((byte*)0x2000, 0, 0x2000); // clear page 1
  SetLookupTable();
}

byte y;
int offset, i;
void DrawChar(int index, byte xpos, byte ypos)
{
  i = index <<3;
  ypos = ypos << 3;
  offset= RowsHGR[ypos] + xpos;
  for (y = 0; y < 8; ++y)
  {
    HGR[offset] = charset[i];
    offset += 0x400;
    ++i;
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
      {
        DrawChar(i, x, y);
        ++i;
        //DrawChar(x + y*16, x + (i % 24), y + (i % 8)); 
      }
    //FlipBuffer();
    i += 16;
  }
}
