#ifndef MOVEMENT_HEADER
#define MOVEMENT_HEADER

void moveLeft(void *buffer);
void moveVertLineLeft(uint32 *pixel);
bool canActivePieceGoLeft(void *buffer);

void moveRight(void *buffer);
void moveVertLineRight(uint32 *pixel);
bool canPieceGoRight(uint32 *pixel);

bool canActivePieceMoveDown(void *buffer);
bool canPieceGoDown(uint32 **pixel, uint64 * const x);
bool canPieceGoDown(uint32 *pixel);
void moveDown(void *buffer);
void moveHorLineDown(uint32 *start, uint32* end);

#endif