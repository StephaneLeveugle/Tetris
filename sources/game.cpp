#include "game.h"

#define VOID_COLOR 0
#define ACTIVE_PIECE_BORDER_COLOR (255 << 16 | 255 << 8 | 255)
#define PIECE_BORDER_COLOR (127 << 16 | 127 << 8 | 127)
#define GAME_BORDER_COLOR (255 << 8)
#define BYTE_PER_PIXEL 4
#define PIXELS_TO_MOVE 25

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
        else if((x == 176 || x == 225) && y >(GAME_HEIGHT - 50))
        {
          *pixel = ACTIVE_PIECE_BORDER_COLOR;
        }
        else if((y >(GAME_HEIGHT - 50)) && (x >= 176) && (x < 226))
        {
          *pixel = 255;
        }
      }
      pixel++;
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
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

bool canActivePieceMoveDown(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(uint64 y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;

    for(uint64 x = 0; x < GAME_WIDTH; ++x)
    {
      if(*pixel == ACTIVE_PIECE_BORDER_COLOR)
      {
        return canPieceGoDown(pixel);
      }
      pixel++;
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }

  return false;
}

void moveDown(void *buffer, bool isDownPressed)
{
  static uint64 nbOfCalls = 0;

  if(nbOfCalls % 16 == 0 || ((nbOfCalls % 2 == 0) && isDownPressed))
  {
    uint8 *row = (uint8 *)buffer;

    for(uint64 y = 0; y < GAME_HEIGHT; ++y)
    {
      uint32 *pixel = (uint32 *)row;

      for(uint64 x = 0; x < GAME_WIDTH; ++x)
      {
        if(*pixel != GAME_BORDER_COLOR)
        {
          if(y > 1 && *pixel != VOID_COLOR)
          {
            if(*(pixel - GAME_WIDTH) == VOID_COLOR)
            {
              uint32 *start = pixel;

              if(canPieceGoDown(&pixel, &x))
              {
                moveHorLineDown(start, pixel);
              }
            }
          }
        }

        pixel++;
      }

      row += GAME_WIDTH * BYTE_PER_PIXEL;
    }
  }

  nbOfCalls++;
}

void moveLeft(void *buffer)
{
  static uint64 nbOfCalls = 0;

  if(nbOfCalls % 2048 == 0)
  {
    uint8 *row = (uint8 *)buffer;

    for(uint64 y = 0; y < GAME_HEIGHT; ++y)
    {
      uint32 *pixel = (uint32 *)row;

      for(uint64 x = 0; x < GAME_WIDTH; ++x)
      {
        if(*pixel == ACTIVE_PIECE_BORDER_COLOR && canPieceGoDown(pixel))
        {

          // perform the move while going to the right
          while(*pixel == ACTIVE_PIECE_BORDER_COLOR && canPieceGoLeft(pixel))
          {
            moveVertLineLeft(pixel);
            pixel++;
          }

          return;
        }
        pixel++;
      }

      row += GAME_WIDTH * BYTE_PER_PIXEL;
    }
  }

  nbOfCalls++;
}

void moveVertLineLeft(uint32 *pixel)
{
  do
  {
    *(pixel - 1) = *pixel;
    *pixel = VOID_COLOR;
    pixel = pixel + GAME_WIDTH;
  } while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR);
}

bool canPieceGoLeft(uint32 *pixel)
{
  bool canPieceGoLeft = true;
  do
  {
    if(*(pixel - 1) != VOID_COLOR)
    {
      canPieceGoLeft = false;
    }
    pixel = pixel + GAME_WIDTH;
  } while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR);

  return canPieceGoLeft;
}


void moveRight(void *buffer)
{
  static uint64 nbOfCalls = 0;

  if(nbOfCalls % 2048 == 0)
  {
    uint8 *row = (uint8 *)buffer;

    for(uint64 y = 0; y < GAME_HEIGHT; ++y)
    {
      uint32 *pixel = (uint32 *)row;

      for(uint64 x = 0; x < GAME_WIDTH; ++x)
      {
        if(*pixel == ACTIVE_PIECE_BORDER_COLOR && canPieceGoDown(pixel))
        {
          // go to right side of active piece
          do
          {
            pixel++;
          } while(*(pixel + 1) == ACTIVE_PIECE_BORDER_COLOR);

          // we now are on the right side of active piece
          // perform the move while going back to the left
          while(*pixel == ACTIVE_PIECE_BORDER_COLOR && canPieceGoRight(pixel))
          {
            moveVertLineRight(pixel);
            pixel--;
          }

          return;
        }
        pixel++;
      }

      row += GAME_WIDTH * BYTE_PER_PIXEL;
    }
  }

  nbOfCalls++;
}

void moveVertLineRight(uint32 *pixel)
{
  do
  {
    *(pixel + 1) = *pixel;
    *pixel = VOID_COLOR;
    pixel = pixel + GAME_WIDTH;
  } while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR);
}

bool canPieceGoRight(uint32 *pixel)
{
  bool canPieceGoRight = true;
  do
  {
    if(*(pixel + 1) != VOID_COLOR)
    {
      canPieceGoRight = false;
    }
    pixel = pixel + GAME_WIDTH;
  } while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR);

  return canPieceGoRight;
}


bool canPieceGoDown(uint32 **pixel, uint64 * const x)
{
  bool canPieceGoDown = true;

  //do
  while(**pixel != GAME_BORDER_COLOR && **pixel != VOID_COLOR && **pixel != PIECE_BORDER_COLOR)
  {
    if(*(*pixel - GAME_WIDTH) != VOID_COLOR)
    {
      canPieceGoDown = false;
    }
    (*pixel)++;
    (*x)++;
  }
  //} while(**pixel != GAME_BORDER_COLOR && **pixel != VOID_COLOR && **pixel != PIECE_BORDER_COLOR);

  return canPieceGoDown;
}

bool canPieceGoDown(uint32 *pixel)
{
  bool canPieceGoDown = true;
  //do
  while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR && *pixel != PIECE_BORDER_COLOR)
  {
    if(*(pixel - GAME_WIDTH) != VOID_COLOR)
    {
      canPieceGoDown = false;
    }
    *pixel++;
  }
  //} while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR && *pixel != PIECE_BORDER_COLOR);

  return canPieceGoDown;
}

void moveHorLineDown(uint32 *start, uint32 *end)
{
  uint32 *curr = start;
  while(curr < end)
  {
    *(curr - GAME_WIDTH) = *curr;
    *curr++ = VOID_COLOR;
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
      else if((y == (GAME_HEIGHT - 49) || y == (GAME_HEIGHT - 2)) && (x >= 175 && x < 225))
      {
        *pixel++ = ACTIVE_PIECE_BORDER_COLOR;
      }
      else if((x == 175 || x == 224) && y > (GAME_HEIGHT - 50))
      {
        *pixel++ = ACTIVE_PIECE_BORDER_COLOR;
      }
      else if((y > (GAME_HEIGHT - 50)) && (x >= 175) && (x < 225))
      {
        *pixel++ = 255;
      }
      else
      {
        *pixel++ = VOID_COLOR;
      }
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
}