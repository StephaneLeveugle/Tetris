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
        else if((x == 151 || x == 250) && y >(GAME_HEIGHT - 50))
        {
          *pixel = ACTIVE_PIECE_BORDER_COLOR;
        }
        else if((y >(GAME_HEIGHT - 50)) && (x >= 151) && (x < 251))
        {
          *pixel = 255;
        }
      }
      pixel++;
    }
    row += GAME_WIDTH * BYTE_PER_PIXEL;
  }
}

Piece spawnStraight(void *buffer)
{
  drawStraight(buffer);

  Piece straight = {};
  straight.x0 = 150;
  straight.y0 = GAME_HEIGHT - 27;
  straight.width = 100;
  straight.height = 25;
  straight.isActive = true;

  return straight;
}

Piece spawnSquare(void *buffer)
{
  drawSquare(buffer);

  Piece straight = {};
  straight.x0 = 175;
  straight.y0 = GAME_HEIGHT - 52;
  straight.width = 50;
  straight.height = 50;
  straight.isActive = true;

  return straight;
}

Piece spawnUp(void *buffer)
{
  drawUp(buffer);

  Piece up = {};
  up.x0 = 175;
  up.y0 = GAME_HEIGHT - 52;
  up.width = 75;
  up.height = 50;
  up.isActive = true;

  return up;
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