#define STROBE(addr) __asm__ ("sta %w", addr)
#define COLS 40
#define ROWS 24
#include "Common.h"

void DrawHGRScreen(void);
void SetLookupTable(void);
void SetGraphicsMode(void);
void DrawChar(int index, byte xpos, byte ypos);
void SetChar(byte index, byte x, byte y);