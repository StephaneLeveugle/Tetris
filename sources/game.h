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

enum PieceType
{
    PIECE_TYPE_CUBE,
    PIECE_TYPE_RECT,

    PIECE_TYPE_COUNT,
};

struct Piece
{
  int x0;
  int y0;
  int width;
  int height;
  bool isActive;
  PieceType type;
};

void setActivePieceToUnactive(void *buffer);
void spawnNewPiece(void *buffer);
void spawnNewCube(void *buffer);
void spawnNewRect(void *buffer);
Piece spawnLeftTurn(void *buffer);
void gameUpdate(void *buffer, GameControls gameControls);
void clearFullLines(void *buffer);
void eraseLine(uint32 *begin, uint32 *end);
void gameInit(void *buffer);

uint32* goTo(void *buffer, uint32 x, uint32 y);

#include "movement.h"
#include "draw.h"
#include "movement.cpp"
#include "draw.cpp"

#endif
