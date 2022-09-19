#include "stdio.h"
#include "Common.h"
//#link "System_Graphics_A2CHR.c"
#include "Platform.h"

void main (void)
{
  byte x, y;
  byte i = 0;
  SetGraphicsMode();
  printf("hello");
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
    i += 16;
    //DrawHGRScreen();
  }
}
