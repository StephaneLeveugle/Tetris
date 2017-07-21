// TODO: 
// - Add rotation
// - Add several pieces
// - Add losing
// - Add points
// - Improve controls (track taps)

// if first piece (x0 + width) > second piece (x0)
// then we've got a block
// merge the two pieces?
// Should we treat it as a single block, or two pieces, or both?

// I think we should store it and treat it as a single block
// we only keep track of the active piece + an array of blocks

// Improve Left Turn, they don't pile up correctly
// the bottom is 1px off

#include "game.h"

void gameUpdate(void *buffer, GameControls gameControls)
{
  static uint64 nbOfCalls = 0;

  if(gameControls.isLeftPressed && !gameControls.isRightPressed)
  {
    OutputDebugStringA("left pressed\n");
    if(canActivePieceGoLeft(buffer))
    {
      int counter = 0;
      while(counter < PIXELS_TO_MOVE && (activePiece->x0 > 1))
      {
        moveLeft(buffer);
        counter++;
      }
    }
  }
  else if(gameControls.isRightPressed && !gameControls.isLeftPressed)
  {
    OutputDebugStringA("right pressed\n");
    if(canActivePieceGoRight(buffer))
    {
      int counter = 0;
      while(counter < PIXELS_TO_MOVE && (activePiece->x0 < (GAME_WIDTH - 1)))
      {
        moveRight(buffer);
        counter++;
      }
    }
  }

  if(gameControls.isDownPressed)
  {
    for(int i = 0; i < (PIXELS_TO_MOVE * 2); i++)
    {
      moveDown(buffer);
    }
  }
  else
  {
    // make it slower to move down so that it feels smoother
    if(nbOfCalls % 8 == 0)
    {
      for(int i = 0; i < PIXELS_TO_MOVE; i++)
      {
        moveDown(buffer);
      }
    }
  }

  if(!canActivePieceMoveDown(buffer))
  {
    uint32 *pixel = (uint32 *) buffer;
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
  
  *activePiece = spawnSquare(buffer);
}


uint32 * goTo(void *buffer, uint32 x, uint32 y)
{
  uint32 *pixel = (uint32 *) buffer;
  pixel += (y * GAME_WIDTH) + x;
  return pixel;
}

uint32 * goToXMax(void *buffer)
{
  uint32 *pixel = goTo(buffer, activePiece->x0 + activePiece->width, activePiece->y0);

  // if we are on the border, just go as far as possible down
  if(*pixel == ACTIVE_PIECE_BORDER_COLOR)
  {
    while(*(pixel - GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR) pixel -= GAME_WIDTH;
  }
  else
  {
    uint32 *originalPosition = pixel;
    bool isBorderFound = false;
    int nbOfPixelsGoneThrough = 0;
    
    // look for the border downwards
    while(!isBorderFound && nbOfPixelsGoneThrough < activePiece->height)
    {
      if(*pixel == ACTIVE_PIECE_BORDER_COLOR) isBorderFound = true;
      else
      {
        pixel -= GAME_WIDTH;
        nbOfPixelsGoneThrough++;
      }
    }

    pixel = originalPosition;
    nbOfPixelsGoneThrough = 0;
    // look for the border upwards (if not already found)
    while(!isBorderFound && nbOfPixelsGoneThrough < activePiece->height)
    {
      if(*pixel == ACTIVE_PIECE_BORDER_COLOR) isBorderFound = true;
      else
      {
        pixel += GAME_WIDTH;
        nbOfPixelsGoneThrough++;
      }
    }

    // now go as far as possible down
    while(*(pixel - GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR) pixel -= GAME_WIDTH;  
  }

  return pixel;
}





