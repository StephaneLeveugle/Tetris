bool canActivePieceMoveDown(void *buffer)
{
  uint8 *row = (uint8 *)buffer;

  for(uint64 y = 0; y < GAME_HEIGHT; ++y)
  {
    uint32 *pixel = (uint32 *)row;

    for(uint64 x = 0; x < GAME_WIDTH; ++x)
    {
      if(*pixel > MIN_ACTIVE_PIECE_BORDER_COLOR)
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
        if(*pixel > MIN_ACTIVE_PIECE_BORDER_COLOR && canPieceGoDown(pixel))
        {

          // perform the move while going to the right
          while(*pixel > MIN_ACTIVE_PIECE_BORDER_COLOR && canPieceGoLeft(pixel))
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
        if(*pixel > MIN_ACTIVE_PIECE_BORDER_COLOR && canPieceGoDown(pixel))
        {
          // go to right side of active piece
          do
          {
            pixel++;
          } while(*(pixel + 1) > MIN_ACTIVE_PIECE_BORDER_COLOR);

          // we now are on the right side of active piece
          // perform the move while going back to the left
          while(*pixel > MIN_ACTIVE_PIECE_BORDER_COLOR && canPieceGoRight(pixel))
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
  while(**pixel != GAME_BORDER_COLOR && **pixel != VOID_COLOR && (**pixel < MIN_PIECE_BORDER_COLOR || **pixel > MAX_PIECE_BORDER_COLOR))
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
  while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR && (*pixel < MIN_PIECE_BORDER_COLOR || *pixel > MAX_PIECE_BORDER_COLOR))
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