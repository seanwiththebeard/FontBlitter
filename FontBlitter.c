#include "stdio.h"
#include "Common.h"
//#link "Platform.c"
#include "Platform.h"

void main (void)
{
  byte x, y;
  byte i = 0;
  SetGraphicsMode();
  DrawHGRScreen();
  
  while (1)
  {
    //printf("hello\n");
    for (y= 0; y < 16; ++y)
      for (x = 0; x < 16; ++x)
      {
        SetChar(i, x, y);
        //DrawChar(i, x, y);
        ++i;
        //DrawChar(x + y*16, x + (i % 24), y + (i % 8)); 
      }
    DrawHGRScreenArea(0, 0, 16, 16);
    i += 16;
    //DrawHGRScreen();
  }
}
