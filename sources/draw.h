#ifndef DRAW_HEADER
#define DRAW_HEADER

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

#define LEFT_TURN_COLOR (255 << 16)

void drawVertLine(void *buffer, uint32 content, uint32 x0, uint32 y0, int32 height);
void drawHorLine(void *buffer, uint32 content, uint32 x0, uint32 y0, int32 width);
void drawLeftTurn(void *buffer);

#endif