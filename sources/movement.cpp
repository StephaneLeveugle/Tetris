bool canActivePieceMoveDown(void *buffer)
{
  uint32 *pixel = goTo(buffer, activePiece->x0, activePiece->y0);

  int nbOfPixelsGoneThrough = 0;

  while(*pixel == ACTIVE_PIECE_BORDER_COLOR)
  {
    if(*(pixel - GAME_WIDTH) != VOID_COLOR && *(pixel - GAME_WIDTH) != ACTIVE_PIECE_BORDER_COLOR)
    {
      return false;
    }
    pixel++;
    nbOfPixelsGoneThrough++;
  }

  // if we didn't finish (because of the piece shape)
  if(nbOfPixelsGoneThrough < activePiece->width)
  {
    // go back once to the left
    pixel--;
    // decrement to make sure it isn't counted twice
    nbOfPixelsGoneThrough--;

    // try to go down
    if(*(pixel - GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR)
    {
      while(*(pixel - GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR) pixel -= GAME_WIDTH;
    }
    // try to go up
    else if(*(pixel + GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR)
    {
      while(*(pixel + GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR) pixel += GAME_WIDTH;
    }
    // wtf?
    else
    {
      return false;
    }

    // now check again
    while(*pixel == ACTIVE_PIECE_BORDER_COLOR)
    {
      if(*(pixel - GAME_WIDTH) != VOID_COLOR && *(pixel - GAME_WIDTH) != ACTIVE_PIECE_BORDER_COLOR)
      {
        return false;
      }
      pixel++;
      nbOfPixelsGoneThrough++;
    }
  }

  return nbOfPixelsGoneThrough == activePiece->width;
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

    activePiece->y0--;
  }

  nbOfCalls++;
}


void moveLeft(void *buffer)
{
  uint32 *pixel = goTo(buffer, activePiece->x0, activePiece->y0);

  for(int i = 0; i < activePiece->width; i++)
  {
    // go as far as possible down
    while(*(pixel - GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR) pixel -= GAME_WIDTH;
    // move the vertical line to the left
    moveVertLineLeft(pixel);
    
    // prepare the next iteration 
    if(i < (activePiece->width - 1))
    {
      // go up while next pixel to the right isn't ACTIVE_PIECE_BORDER_COLOR
      while(*(pixel + 1) != ACTIVE_PIECE_BORDER_COLOR) pixel += GAME_WIDTH;
    }
    pixel++; 
  }

  activePiece->x0--;
}

bool canActivePieceGoLeft(void *buffer)
{
  uint32 *pixel = goTo(buffer, activePiece->x0, activePiece->y0);
  int nbOfPixelsGoneThrough = 0;

  // go up, checking on the left for every pixel
  while(*pixel == ACTIVE_PIECE_BORDER_COLOR)
  {
    if(*(pixel - 1) != VOID_COLOR)
    {
      return false;
    }
    pixel += GAME_WIDTH;
    nbOfPixelsGoneThrough++;
  }

  // if we didn't finish (because of the piece shape)
  if(nbOfPixelsGoneThrough < activePiece->height)
  {
    pixel -= GAME_WIDTH;
    nbOfPixelsGoneThrough--;

    // move as far as possible to the right
    while(*(pixel + 1) == ACTIVE_PIECE_BORDER_COLOR) pixel++;
    // try going up again
    while(*(pixel + GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR)
    {
      pixel += GAME_WIDTH;
      nbOfPixelsGoneThrough++;

      if(*(pixel - 1) != VOID_COLOR)
      {
        return false;
      }
    }

    // if it is still not finished
    if(nbOfPixelsGoneThrough < activePiece->height)
    {
      // go back to (x0, y0) and move as far as possible to the right
      pixel = goTo(buffer, activePiece->x0, activePiece->y0);
      while(*(pixel + 1) == ACTIVE_PIECE_BORDER_COLOR) pixel++;

      // check on the left while going down
      while(*(pixel - GAME_WIDTH) == ACTIVE_PIECE_BORDER_COLOR)
      {
        pixel -= GAME_WIDTH;
        nbOfPixelsGoneThrough++;

        if(*(pixel - 1) != VOID_COLOR)
        {
          return false;
        }
      }
    }
  }

  // nbOfPixelsGoneThrough is 25 with a left turn
  // line 183 is never hit
  return nbOfPixelsGoneThrough == activePiece->height;
}

void moveVertLineLeft(uint32 *pixel)
{
  do
  {
    *(pixel - 1) = *pixel;
    *pixel = VOID_COLOR;
    pixel = pixel + GAME_WIDTH;
  } while(*pixel != GAME_BORDER_COLOR && *pixel != VOID_COLOR && *pixel != PIECE_BORDER_COLOR);
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