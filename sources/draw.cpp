// content is the color of what we want to draw
// positive height : from bottom to top
// negative height : from top to bottom
void drawVertLine(void *buffer, uint32 content, uint32 x0, uint32 y0, int32 height)
{
  bool isPos = (height > 0);
  height = abs(height);
  uint32 *pixel = goTo(buffer, x0, y0);
  for(uint32 i = 0; i < height; i++)
  {
    *pixel = content;
    if(isPos) pixel += GAME_WIDTH;
    else pixel -= GAME_WIDTH;
  }
}

// content is the color of what we want to draw
// positive width : from left to right
// negative width : from right to left
void drawHorLine(void *buffer, uint32 content, uint32 x0, uint32 y0, int32 width)
{
  bool isPos = (width > 0);
  width = abs(width);
  uint32 *pixel = goTo(buffer, x0, y0);
  for(uint32 i = 0; i < width; i++)
  {
    *pixel = content;
    if(isPos) pixel++;
    else pixel--;
  }
}

// only drawn at the top with hardcoded values because it is only used in spawn (as of 14/07/17)
void drawStraight(void *buffer)
{
  // 151 if GAME_WIDTH = 402
  int straightX0 = (GAME_WIDTH / 2) - (STRAIGHT_WIDTH / 2);

  // draw borders (frop top to bottom)
  {
    // top border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, straightX0, GAME_HEIGHT - 2, 100);
    // left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, straightX0, GAME_HEIGHT - 2, -25);
    // right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, straightX0 + 99, GAME_HEIGHT - 2, -25);
    // bottom border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, straightX0, GAME_HEIGHT - 26, 100);
  }
  // draw interior (from top to bottom)
  {
    for(int i = 1; i < 24; i++)
    {
      drawHorLine(buffer, STRAIGHT_COLOR, straightX0 + 1, GAME_HEIGHT - 2 - i, 98);
    }
  }
}

// only drawn at the top with hardcoded values because it is only used in spawn (as of 14/07/17)
void drawSquare(void *buffer)
{
  // 176 if GAME_WIDTH = 402
  int squareX0 = (GAME_WIDTH / 2) - (SQUARE_WIDTH / 2);

  // draw borders (frop top to bottom)
  {
    // top border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, squareX0, GAME_HEIGHT - 2, 50);
    // left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, squareX0, GAME_HEIGHT - 2, -50);
    // right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, squareX0 + 49, GAME_HEIGHT - 2, -50);
    // bottom border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, squareX0, GAME_HEIGHT - 51, 50);
  }
  // draw interior (from top to bottom)
  {
    for(int i = 1; i < 49; i++)
    {
      drawHorLine(buffer, SQUARE_COLOR, squareX0 + 1, GAME_HEIGHT - 2 - i, 48);
    }
  }
}

// only drawn at the top with hardcoded values because it is only used in spawnLeftTurn (as of 14/07/17)
void drawUp(void *buffer)
{
  // 176 with GAME_WIDTH = 402
  int upX0 = (GAME_WIDTH / 2) - 25;

  // draw borders (from top to bottom)
  {
    // top border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0 + 24, GAME_HEIGHT - 2, 25);
    // top left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0 + 24, GAME_HEIGHT - 2, -25);
    // top right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0 + 49, GAME_HEIGHT - 2, -25);
    // middle borders
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0, GAME_HEIGHT - 27, 25);
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0 + 49, GAME_HEIGHT - 27, 25);
    // left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0, GAME_HEIGHT - 27, -25);
    // right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0 + 74, GAME_HEIGHT - 27, -25);
    // bottom border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, upX0, GAME_HEIGHT - 51, 75);
  }
  // draw interior (from top to bottom)
  {
    // upper part
    for(int i = 1; i < 25; i++)
    {
      drawHorLine(buffer, UP_COLOR, upX0 + 25, GAME_HEIGHT - 2 - i, 24);
    }
    // middle line
    drawHorLine(buffer, UP_COLOR, upX0 + 25, GAME_HEIGHT - 27, 24);
    // lower part 
    for(int i = 1; i < 24; i++)
    {
      drawHorLine(buffer, UP_COLOR, upX0 + 1, GAME_HEIGHT - 27 - i, 73);
    }
  }
}

// only drawn at the top with hardcoded values because it is only used in spawnLeftTurn (as of 14/07/17)
void drawLeftTurn(void *buffer)
{
  int leftTurnX0 = (GAME_WIDTH / 2) - 25;

  // draw borders (from top to bottom)
  {
    // top border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0, GAME_HEIGHT - 2, 50);
    // top left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0, GAME_HEIGHT - 2, -25);
    // top right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0 + 49, GAME_HEIGHT - 2, -25);
    // middle left border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0, GAME_HEIGHT - 26, 25);
    // middle right border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0 + 48, GAME_HEIGHT - 27, 26);
    // bottom left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0 + 25, GAME_HEIGHT - 26, -25);
    // bottom right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0 + 74, GAME_HEIGHT - 27, -25);
    // bottom border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, leftTurnX0 + 25, GAME_HEIGHT - 51, 50);
  }
  // draw interior (from top to bottom)
  {
    // upper part
    for(int i = 1; i < 24; i++)
    {
      drawHorLine(buffer, LEFT_TURN_COLOR, leftTurnX0 + 1, GAME_HEIGHT - 2 - i, 48);
    }
    // middle line
    drawHorLine(buffer, LEFT_TURN_COLOR, leftTurnX0 + 26, GAME_HEIGHT - 26, 23);
    drawHorLine(buffer, LEFT_TURN_COLOR, leftTurnX0 + 26, GAME_HEIGHT - 27, 23);
    // lower part
    for(int i = 1; i < 24; i++)
    {
      drawHorLine(buffer, LEFT_TURN_COLOR, leftTurnX0 + 26, GAME_HEIGHT - 27 - i, 48);
    }
  }
}