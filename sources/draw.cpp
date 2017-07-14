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

// only drawn at the top with hardcoded values because it is only used in spawnLeftTurn (as of 14/07/17)
void drawLeftTurn(void *buffer)
{
  // draw borders (from top to bottom)
  {
    // top border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 175, GAME_HEIGHT - 2, 50);
    // top left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 175, GAME_HEIGHT - 2, -25);
    // top right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 225, GAME_HEIGHT - 2, -25);
    // middle left border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 175, GAME_HEIGHT - 27, 25);
    // middle right border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 225, GAME_HEIGHT - 27, 25);
    // bottom left border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 200, GAME_HEIGHT - 27, -25);
    // bottom right border
    drawVertLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 250, GAME_HEIGHT - 27, -25);
    // bottom border
    drawHorLine(buffer, ACTIVE_PIECE_BORDER_COLOR, 200, GAME_HEIGHT - 52, 50);
  }
  // draw interior (from top to bottom)
  {
    // upper part
    for(int i = 1; i < 25; i++)
    {
      drawHorLine(buffer, LEFT_TURN_COLOR, 176, GAME_HEIGHT - 2 - i, 49);
    }
    // middle line
    drawHorLine(buffer, LEFT_TURN_COLOR, 201, GAME_HEIGHT - 27, 24);
    // lower part
    for(int i = 1; i < 25; i++)
    {
      drawHorLine(buffer, LEFT_TURN_COLOR, 201, GAME_HEIGHT - 27 - i, 49);
    }
  }
}