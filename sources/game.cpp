// TODO: 
// - Force 60fps & improve controls
// - Add rotation
// - Add several pieces
// - Add losing
// - Add points

// Create an array of pieces
// Every frame, go through the array of pieces
// Begin on the lowest left point of each piece
// go to the right, checking if the pixel below is free
// if it is not, break
// If you are on a right edge but you know you didn't finish (because we have the width of the piece)
// Then, try to go down, if you can't, go up
// Continue going to the right as soon as you can!

// The only special case is when the user wants the active piece to move left or right

// It would be good for the array of pieces to be sorted in such a way that when we iterate over it
// we go from the bottom left to the top right 

// The behavior above will break the blocks of pieces
// possible solution :
// if first piece (x0 + width) > second piece (x0)
// then we've got a block
// merge the two pieces?
// Should we treat it as a single block, or two pieces, or both?

// I think we should store it and treat it as a single block
// we only keep track of the active piece + an array of blocks


// CREATE DRAW.CPP
// fillPiece function
// probably only need to be done when ititializing the active piece

#include "game.h"

static Piece *activePiece = nullptr;


void gameUpdate(void *buffer, GameControls gameControls)
{
  static uint64 nbOfCalls = 0;

  if(gameControls.isLeftPressed && !gameControls.isRightPressed && (nbOfCalls % 75 == 0))
  {
    OutputDebugStringA("left pressed\n");
    for(int i = 0; i < PIXELS_TO_MOVE; i++)
    {
      moveLeft(buffer);
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

void spawnNewPiece(void *buffer)
{
  static uint64 nbOfCalls = 0;
  if(nbOfCalls++ % 2 == 0)
  {
    spawnNewCube(buffer);
  }
  else
  {
    spawnNewRect(buffer);
  }
}

void setActivePieceToUnactive(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(uint64 y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;

    for(uint64 x = 0; x < GAME_WIDTH; ++x)
    {
      if(*pixel == ACTIVE_PIECE_BORDER_COLOR)
      {
        *pixel = PIECE_BORDER_COLOR;
      }
      pixel++;
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
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
  spawnLeftTurn(buffer);
}

void spawnNewCube(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(int y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;
    for(int x = 0; x < GAME_WIDTH; ++x)
    {
      if(y > 0 && y < (GAME_HEIGHT - 1) && x > 0 && x < (GAME_WIDTH - 1))
      {
        if((y == (GAME_HEIGHT - 49) || y == (GAME_HEIGHT - 2)) && (x >= 176 && x < 226))
        {
          *pixel = ACTIVE_PIECE_BORDER_COLOR;
        }
        else if((x == 176 || x == 225) && y > (GAME_HEIGHT - 50))
        {
          *pixel = ACTIVE_PIECE_BORDER_COLOR;
        }
        else if((y > (GAME_HEIGHT - 50)) && (x >= 176) && (x < 226))
        {
          *pixel = 255;
        }
      }
      pixel++;
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
}

void spawnNewRect(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(int y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;
    for(int x = 0; x < GAME_WIDTH; ++x)
    {
      if(y > 0 && y < (GAME_HEIGHT - 1) && x > 0 && x < (GAME_WIDTH - 1))
      {
        if((y == (GAME_HEIGHT - 49) || y == (GAME_HEIGHT - 2)) && (x >= 151 && x < 251))
        {
          *pixel = ACTIVE_PIECE_BORDER_COLOR;
        }
        else if((x == 151 || x == 250) && y > (GAME_HEIGHT - 50))
        {
          *pixel = ACTIVE_PIECE_BORDER_COLOR;
        }
        else if((y > (GAME_HEIGHT - 50)) && (x >= 151) && (x < 251))
        {
          *pixel = 255;
        }
      }
      pixel++;
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
}

Piece spawnLeftTurn(void *buffer)
{
  drawLeftTurn(buffer);

  Piece leftTurn = {};
  leftTurn.x0 = 175;
  leftTurn.y0 = GAME_HEIGHT - 27;
  leftTurn.width = 75;
  leftTurn.height = 50;
  leftTurn.isActive = true;
  return leftTurn;
}

uint32* goTo(void *buffer, uint32 x, uint32 y)
{
  uint32* pixel = (uint32 *) buffer;
  pixel += (y * GAME_WIDTH) + x;
  return pixel;
}





