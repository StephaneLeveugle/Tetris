#ifndef GAME_HEADER
#define GAME_HEADER

#define VOID_COLOR 0
#define ACTIVE_PIECE_BORDER_COLOR (255 << 16 | 255 << 8 | 255)
#define ACTIVE_CUBE_BORDER_COLOR (254 << 16 | 254 << 8 | 254)
#define ACTIVE_RECT_BORDER_COLOR (253 << 16 | 253 << 8 | 253)
#define MIN_ACTIVE_PIECE_BORDER_COLOR (245 << 16 | 245 << 8 | 245)
#define PIECE_BORDER_COLOR (127 << 16 | 127 << 8 | 127)
#define CUBE_BORDER_COLOR (126 << 16 | 126 << 8 | 126)
#define RECT_BORDER_COLOR (125 << 16 | 125 << 8 | 125)
#define MAX_PIECE_BORDER_COLOR (127 << 16 | 127 << 8 | 127)
#define MIN_PIECE_BORDER_COLOR (117 << 16 | 117 << 8 | 117)
#define GAME_BORDER_COLOR (255 << 8)
#define BYTE_PER_PIXEL 4
#define PIXELS_TO_MOVE 25

struct GameControls
{
  bool isLeftPressed = false;
  bool isRightPressed = false;
  bool isDownPressed = false;
};

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
void gameUpdate(void *buffer, GameControls gameControls);
void clearFullLines(void *buffer);
void eraseLine(uint32 *begin, uint32 *end);
void gameInit(void *buffer);

#endif
