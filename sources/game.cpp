#define NB_OF_PIXELS GAME_HEIGHT * GAME_WIDTH
#define BSIZE 50

struct Pixel {
    u32 color;
    bool isActive = false;
    bool isEmpty = true;
};

struct Block {
    u16 x, y;
};

#define pxl pixels[i][j]

Pixel pixels[GAME_HEIGHT][GAME_WIDTH] = {};
Block activeBlocks[4] = {};
Block blocks[200] = {};
u16 blockIndexCounter = 0;

#include "spawn.cpp"
#include "movement.cpp"

void gameInit(u32 *buffer) {
    srand(time(NULL));
    spawnAny();
}

void gameUpdate(u32 *buffer, GameControls gameControls) {

    if (gameControls.isLeftPressed) {
        if (canMoveLeft()) moveLeft();
        else if (canMoveDown()) moveDown();
    } else if (gameControls.isRightPressed) {
        if (canMoveRight()) moveRight();
        else if (canMoveDown()) moveDown();
    } else if (canMoveDown()) moveDown();

    if (!canMoveDown()) {
        for (int i = 0; i < 4; i++) {
            blocks[blockIndexCounter++] = activeBlocks[i];
        }
        // set all active pixels back to non active
        {
            for (u16 i = 0; i < GAME_HEIGHT; i++) {
                for (u16 j = 0; j < GAME_WIDTH; j++) {
                    pxl.isActive = false;
                }
            }
        }
        spawnAny();        
    }

    for (u16 i = 0; i < GAME_HEIGHT; i++) {
        for (u16 j = 0; j < GAME_WIDTH; j++) {
            buffer[(i*GAME_WIDTH)+j] = pxl.color;
        }
    }    
}