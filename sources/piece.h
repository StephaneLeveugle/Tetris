#ifndef PIECE_HEADER
#define PIECE_HEADER

// colors
#define LEFT_TURN_COLOR (255 << 16)
#define STRAIGHT_COLOR (255 << 8 | 255)
#define SQUARE_COLOR (255 << 16 | 255 << 8)
#define UP_COLOR (191 << 16 | 255)

// dimensions
#define SQUARE_WIDTH 50
#define STRAIGHT_WIDTH 100

enum PieceType
{
  PIECE_TYPE_CUBE,
  PIECE_TYPE_RECT,

  PIECE_TYPE_COUNT,
};

struct Piece
{
  int x0;
  int y0;
  int width;
  int height;
  bool isActive;
  PieceType type;
};

void setActivePieceToUnactive(void *buffer);
void spawnNewPiece(void *buffer);

void spawnNewCube(void *buffer);
void spawnNewRect(void *buffer);

Piece spawnSquare(void *buffer);
Piece spawnStraight(void *buffer);
Piece spawnUp(void *buffer);
Piece spawnLeftTurn(void *buffer);








#endif