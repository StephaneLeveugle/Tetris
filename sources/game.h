#ifndef GAME_HEADER
#define GAME_HEADER

#define BYTE_PER_PIXEL 4
#define PIXELS_TO_MOVE 25

struct GameControls
{
  bool isLeftPressed = false;
  bool isRightPressed = false;
  bool isDownPressed = false;
};

void gameUpdate(void *buffer, GameControls gameControls);
void clearFullLines(void *buffer);
void eraseLine(uint32 *begin, uint32 *end);
void gameInit(void *buffer);

uint32* goTo(void *buffer, uint32 x, uint32 y);

#include "movement.h"
#include "draw.h"
#include "piece.h"
#include "movement.cpp"
#include "draw.cpp"
#include "piece.cpp"

#endif
