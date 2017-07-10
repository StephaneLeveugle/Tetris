#ifndef GAME_HEADER
#define GAME_HEADER

struct GameControls
{
  bool isLeftPressed = false;
  bool isRightPressed = false;
  bool isDownPressed = false;
};

void moveLeft(void *buffer);
void moveVertLineLeft(uint32 *pixel);
bool canPieceGoLeft(uint32 *pixel);

void moveRight(void *buffer);
void moveVertLineRight(uint32 *pixel);
bool canPieceGoRight(uint32 *pixel);

bool canActivePieceMoveDown(void *buffer);
bool canPieceGoDown(uint32 **pixel, uint64 * const x);
bool canPieceGoDown(uint32 *pixel);
void moveDown(void *buffer, bool isDownPressed);
void moveHorLineDown(uint32 *start, uint32* end);

void setActivePieceToUnactive(void *buffer);
void spawnNewPiece(void *buffer);
void gameUpdate(void *buffer, GameControls gameControls);
void clearFullLines(void *buffer);
void eraseLine(uint32 *begin, uint32 *end);
void gameInit(void *buffer);

#endif
