// TODO: 
// - Force 60fps & improve controls
// - Add rotation
// - Add several pieces
// - Add losing
// - Add points

// if first piece (x0 + width) > second piece (x0)
// then we've got a block
// merge the two pieces?
// Should we treat it as a single block, or two pieces, or both?

// I think we should store it and treat it as a single block
// we only keep track of the active piece + an array of blocks


#include "game.h"

void gameUpdate(void *buffer, GameControls gameControls)
{
  static uint64 nbOfCalls = 0;

  if(gameControls.isLeftPressed && !gameControls.isRightPressed && (nbOfCalls % 75 == 0))
  {
    OutputDebugStringA("left pressed\n");
    if(canActivePieceGoLeft(buffer))
    {
      int counter = 0;
      while(counter < PIXELS_TO_MOVE && activePiece->x0 > 1)
      {
        moveLeft(buffer);
        counter++;
      }
    }
  }
  else if(gameControls.isRightPressed && !gameControls.isLeftPressed && (nbOfCalls % 75 == 0))
  {
    OutputDebugStringA("right pressed\n");
    for(int i = 0; i < PIXELS_TO_MOVE; i++)
    {
      moveRight(buffer);
    }
  }

  moveDown(buffer, gameControls.isDownPressed);

  if(!canActivePieceMoveDown(buffer))
  {
    setActivePieceToUnactive(buffer);
    clearFullLines(buffer);
    spawnNewPiece(buffer);
  }

  nbOfCalls++;
}

void clearFullLines(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(uint64 y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;
    bool isLineFull = true;

    for(uint64 x = 0; x < GAME_WIDTH; ++x)
    {
      if(*pixel != GAME_BORDER_COLOR)
      {
        if(*pixel == VOID_COLOR && isLineFull)
        {
          isLineFull = false;
        }
      }

      pixel++;
    }

    if(isLineFull && y != 0 && y != (GAME_HEIGHT - 1))
    {
      eraseLine((uint32 *)row, (uint32 *)row + (GAME_WIDTH * BYTE_PER_PIXEL));
    }

    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
}

void eraseLine(uint32 *begin, uint32 *end)
{
  uint32 *curr = begin;
  while(curr < end)
  {
    if(*curr != GAME_BORDER_COLOR)
    {
      *curr = VOID_COLOR;
    }
    curr++;
  }
}

void gameInit(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(int y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;
    for(int x = 0; x < GAME_WIDTH; ++x)
    {
      if(y == 0 || y == (GAME_HEIGHT - 1) || x == 0 || x == (GAME_WIDTH - 1))
      {
        *pixel++ = GAME_BORDER_COLOR;
      }
      else
      {
        *pixel++ = VOID_COLOR;
      }
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
  
  *activePiece = spawnUp(buffer);
}


uint32* goTo(void *buffer, uint32 x, uint32 y)
{
  uint32* pixel = (uint32 *) buffer;
  pixel += (y * GAME_WIDTH) + x;
  return pixel;
}





