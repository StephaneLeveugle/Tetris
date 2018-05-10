#define NB_OF_PIXELS GAME_HEIGHT * GAME_WIDTH
const int BSIZE = 50;

struct GameControls {
    bool isRightPressed, wasRightPressed,
         isLeftPressed, wasLeftPressed,
         isDownPressed, wasDownPressed,
         isUpPressed, wasUpPressed,
         isEnterPressed, wasEnterPressed,
         isBackspacePressed, wasBackspacePressed;
};

struct Pixel {
    u32 color;
    bool isActive = false;
    bool isEmpty = true;
};

struct Block {
    u16 x, y;
    u32 color;
};

enum TetrominoType {
    I, O, T, L, J, Z, S
};

struct Tetromino {
    Block blocks[4] = {};
    TetrominoType type;
    u32 color = 0;
    u16 rotation = 0;
};

struct ClearLinesResult {
    u16 lineIndex, nbOfLinesCleared;
};

#define pxl pixels[i][j]

Pixel pixels[GAME_HEIGHT][GAME_WIDTH] = {};
// this is the active tetromino, controlled by the player
Tetromino tetromino = {};
Tetromino nextTetromino = {};

ClearLinesResult clearLines(u32 *buffer);
void copyPixelsToBuffer(u32 *buffer);

#include "spawn.cpp"
#include "movement.cpp"

void gameInit(u32 *buffer) {
    srand(time(NULL));
    spawnAny();
}

// returns false if game over
// returns true otherwise
bool gameUpdate(u32 *buffer, GameControls *gameControls, double *timeIdle) {

    if (gameControls->isEnterPressed) {
        if (!gameControls->wasEnterPressed) {
            gameControls->wasEnterPressed = true;
            FILE *pixelsFile = fopen("pixels.debug", "wb");
            if (pixelsFile) {
                fwrite(pixels, sizeof(Pixel), NB_OF_PIXELS, pixelsFile);
            }
            fclose(pixelsFile);
            FILE *tetrominoFile = fopen("tetromino.debug", "wb");
            if (tetrominoFile) {
                fwrite(&tetromino, sizeof(Tetromino), 1, tetrominoFile);
            }
            fclose(tetrominoFile);
        }
    } else if (gameControls->isBackspacePressed) {
        if (!gameControls->wasBackspacePressed) {
            gameControls->wasBackspacePressed = true;
            FILE *pixelsFile = fopen("pixels.debug", "rb");
            if (pixelsFile) {
                fread(pixels, sizeof(Pixel), NB_OF_PIXELS, pixelsFile);
            }
            fclose(pixelsFile);
            FILE *tetrominoFile = fopen("tetromino.debug", "rb");
            if (tetrominoFile) {
                fread(&tetromino, sizeof(Tetromino), 1, tetrominoFile);
            }
            fclose(tetrominoFile);
        }
    } else if (gameControls->isLeftPressed) {
        if ((!gameControls->wasLeftPressed || *timeIdle > 100) && canMoveLeft()) {
            moveLeft();
            *timeIdle = 0;
            gameControls->wasLeftPressed = true;
        } else if (*timeIdle > 1000 && canMoveDown()) {
            moveDown();
            *timeIdle = 0;
        }
    } else if (gameControls->isRightPressed) {
        if ((!gameControls->wasRightPressed || *timeIdle > 100) && canMoveRight()) {
            moveRight();
            *timeIdle = 0;
            gameControls->wasRightPressed = true;
        } else if (*timeIdle > 1000 && canMoveDown()) {
            moveDown();
            *timeIdle = 0;
        }
    } else if (gameControls->isDownPressed) {
        if (!gameControls->wasDownPressed || *timeIdle > 50) {
            if (canMoveDown()) {
                moveDown();
                *timeIdle = 0;
                gameControls->wasDownPressed = true;
            }
        }
    } else if (gameControls->isUpPressed) {
        if (!gameControls->wasUpPressed || *timeIdle > 200) {
            if (rotate()) {
                *timeIdle = 0;
                gameControls->wasUpPressed = true;
            } else if (*timeIdle > 1000 && canMoveDown()) {
                moveDown();
                *timeIdle = 0;
            }
        }
    } else {
        if (*timeIdle > 1000 && canMoveDown()) {
            moveDown();
            *timeIdle = 0;
        }
    }

    if (!canMoveDown()) {
        // set all active pixels back to non active
        {
            for (u16 i = 0; i < GAME_HEIGHT; i++) {
                for (u16 j = 0; j < GAME_WIDTH; j++) {
                    pxl.isActive = false;
                }
            }
        }

        ClearLinesResult clRes = clearLines(buffer);
        if (clRes.nbOfLinesCleared != 0) {
            // lower all pixels that were above the cleared line(s) by nbOfLinesCleared * BSIZE
            {
                for (u16 i = clRes.lineIndex; i < GAME_HEIGHT; i++) {
                    for (u16 j = 0; j < GAME_WIDTH; j++) {
                        pixels[i-(clRes.nbOfLinesCleared*BSIZE)][j] = {pxl.color, pxl.isActive, pxl.isEmpty};
                        pxl = {};
                    }
                }
            }
        }  

        spawnAny();
        if (!canMoveDown()) {
            copyPixelsToBuffer(buffer);
            return false;
        }
        gameControls->isDownPressed = false;
        gameControls->wasDownPressed = false;
    }

    copyPixelsToBuffer(buffer);

    return true;
}

void copyPixelsToBuffer(u32 *buffer) {
    for (u16 i = 0; i < GAME_HEIGHT; i++) {
        for (u16 j = 0; j < GAME_WIDTH; j++) {
            buffer[(i*GAME_WIDTH)+j] = pxl.color;
        }
    }
}

ClearLinesResult clearLines(u32 *buffer) {
    ClearLinesResult result = {};
    bool isLineComplete;
    for (u16 i = 0; i < GAME_HEIGHT; i += BSIZE) {
        isLineComplete = true;
        for (u16 j = 0; j < GAME_WIDTH; j+= BSIZE) {
            if (pxl.isEmpty) {
                isLineComplete = false;
                break;
            }
        }
        if (isLineComplete) {
            result.lineIndex = i + BSIZE;
            result.nbOfLinesCleared++;
            // sets all pixels of the entire blocks on the line to 0
            {
                for (u16 k = i, kmax = i + BSIZE; k < kmax; k++) {
                    for (u16 l = 0; l < GAME_WIDTH; l++) {
                        pixels[k][l] = {};
                    }
                }
            }
        } else {
            if (result.lineIndex != 0) break;
        }
    }
    return result;
}