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
  straight.x0 = (GAME_WIDTH / 2) - (STRAIGHT_WIDTH / 2);
  straight.y0 = GAME_HEIGHT - 26;
  straight.width = STRAIGHT_WIDTH;
  straight.height = 25;
  straight.isActive = true;

  return straight;
}

Piece spawnSquare(void *buffer)
{
  drawSquare(buffer);

  Piece straight = {};
  straight.x0 = (GAME_WIDTH / 2) - (SQUARE_WIDTH / 2);
  straight.y0 = GAME_HEIGHT - 51;
  straight.width = SQUARE_WIDTH;
  straight.height = 50;
  straight.isActive = true;

  return straight;
}

// TODO: check the height is indeed 50 pixels
// looks different than square height but it should be the same
Piece spawnUp(void *buffer)
{
  drawUp(buffer);

  Piece up = {};
  up.x0 = (GAME_WIDTH / 2) - 25;
  up.y0 = GAME_HEIGHT - 51;
  up.width = UP_WIDTH;
  up.height = 50;
  up.isActive = true;

  return up;
}

Piece spawnLeftTurn(void *buffer)
{
  drawLeftTurn(buffer);

  Piece leftTurn = {};
  leftTurn.x0 = (GAME_WIDTH / 2) - 25;
  leftTurn.y0 = GAME_HEIGHT - 26;
  leftTurn.width = LEFT_TURN_WIDTH;
  leftTurn.height = 50;
  leftTurn.isActive = true;
  return leftTurn;
}

void spawnNewPiece(void *buffer)
{
  static uint64 nbOfCalls = 0;
  Piece newPiece = {};

  if(nbOfCalls++ % 5 == 0)
  {
    newPiece = spawnSquare(buffer);
  }
  else if(nbOfCalls % 4 == 0)
  {
    newPiece = spawnStraight(buffer);
  }
  else if(nbOfCalls % 3 == 0)
  {
    newPiece = spawnLeftTurn(buffer);
  }
  else if(nbOfCalls % 2 == 0)
  {
    newPiece = spawnUp(buffer);
  }

  *activePiece = newPiece;
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