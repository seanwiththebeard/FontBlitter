#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "Charset.h"
#include "Common.h"
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

void GenerateCharset()
{
  int i = 0;
  for (i = 1; i < 2048; ++i)
  {
    charset[i] = charset[i - 1] + 1;
  }
}

int GetRow(byte y)
{
  return ((y/64)*0x28 + (y%8)*0x400 + ((y/8)&7)*0x80);

}

void DrawChar(byte index, byte xpos, byte ypos)
{
  byte y;
  if (xpos >= COLS)
    xpos = COLS - 1;
  if (ypos >= ROWS)
    ypos = ROWS-1;
    for (y = 0; y < 8; ++y)
    {
      HGR[GetRow(ypos*8 + y) + xpos] = charset[index * 8 + y];
    }
}

int main (void)
{
  byte x, y;
  byte i = 0;
  SetGraphicsMode();
  //GenerateCharset();
  
  while (1)
  {
  for (y= 0; y < 16; ++y)
    for (x = 0; x < 16; ++x)
      DrawChar(x + y*16, x + (i % 24), y + (i % 8));
    
    ++i;
  }
      //DrawChar(0, 0, 0);
      //DrawChar(0, 39, 23);
  
  //printf("\nHello! Press a key to reboot...\n");
  cgetc();
  return EXIT_SUCCESS;
}

