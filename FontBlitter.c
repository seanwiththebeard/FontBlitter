#include "stdio.h"
#include "Common.h"
//#link "Platform.c"
#include "Platform.h"

void main (void)
{
  byte x, y;
  byte i = 0;
  InitGraphics();
  CopyBuffer();
  
  while (1)
  {
    for (y= 0; y < 16; ++y)
      for (x = 0; x < 16; ++x)
      {
        SetCharBuffer(i, x, y);
        ++i; 
      }
    CopyBufferArea(0, 0, 16, 16);
    i += 16;
    //DrawHGRScreen();
  }
}
