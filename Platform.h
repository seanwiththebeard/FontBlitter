#define STROBE(addr) __asm__ ("sta %w", addr)
#define COLS 40
#define ROWS 24
#include "Common.h"

void InitGraphics(void);

void CopyBuffer(void);
void CopyBufferArea(byte origin_x, byte origin_y, byte width, byte height);
void SetChar(byte index, byte x, byte y);
void SetCharBuffer(byte index, byte x, byte y);