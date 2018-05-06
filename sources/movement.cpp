// checks for each activeBlock if 
// - it has reached the bottom OR
// - the pixel directly below the (x,y) coordinate is taken by a non active block
bool canMoveDown() {
    u16 x, y;
    for (int i = 0; i < 4; i++) {
        x = tetromino.blocks[i].x;
        y = tetromino.blocks[i].y;
        if (y == 0) return false;
        if (!pixels[y-1][x].isEmpty && !pixels[y-1][x].isActive) return false; 
    }
    return true;
}

void moveDown() {
    OutputDebugStringA("Move down\n");
    for (u16 i = 0; i < GAME_HEIGHT; i++) {
        for (u16 j = 0; j < GAME_WIDTH; j++) {
            if (pxl.isActive) {
                pixels[i-BSIZE][j] = {pxl.color, pxl.isActive, pxl.isEmpty};
                pxl = {};
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        tetromino.blocks[i].y -= BSIZE;
    }
}

// checks for each activeBlock if 
// - it has reached the left border OR
// - the pixel directly to the left of the (x,y) pixel is taken by a non active block
bool canMoveLeft() {
    u16 x, y;
    for (int i = 0; i < 4; i++) {
        x = tetromino.blocks[i].x;
        y = tetromino.blocks[i].y;
        if (x == 0) return false;
        if (!pixels[y][x-1].isEmpty && !pixels[y][x-1].isActive) return false; 
    }
    return true;
}

void moveLeft() {
    for (u16 i = 0; i < GAME_HEIGHT; i++) {
        for (u16 j = 0; j < GAME_WIDTH; j++) {
            if (pxl.isActive) {
                pixels[i][j-BSIZE] = {pxl.color, pxl.isActive, pxl.isEmpty};
                pxl = {};
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        tetromino.blocks[i].x -= BSIZE;
    }
}

// checks for each activeBlock if 
// - it has reached the right border OR
// - the pixel directly to the right of the (x,y) pixel is taken by a non active block
bool canMoveRight() {
    u16 x, y;
    for (int i = 0; i < 4; i++) {
        x = tetromino.blocks[i].x;
        y = tetromino.blocks[i].y;
        if (x == GAME_WIDTH-BSIZE) return false;
        if (!pixels[y][x+1+BSIZE].isEmpty && !pixels[y][x+1+BSIZE].isActive) return false; 
    }
    return true;
}

void moveRight() {
    for (u16 i = GAME_HEIGHT - 1; i != UINT16_MAX; i--) {
        for (u16 j = GAME_WIDTH - 1; j != UINT16_MAX; j--) {
            if (pxl.isActive) {
                pixels[i][j+BSIZE] = {pxl.color, pxl.isActive, pxl.isEmpty};
                pxl = {};
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        tetromino.blocks[i].x += BSIZE;
    }
}

// see http://tetris.wikia.com/wiki/SRS to know more about the "algorithm"
// Wall kicks aren't implemented
// https://vignette.wikia.nocookie.net/tetrisconcept/images/3/3d/SRS-pieces.png/revision/latest?cb=20060626173148
bool rotate() {
    u16 oldRotation = tetromino.rotation,
        x           = tetromino.blocks[0].x,
        y           = tetromino.blocks[0].y;
     
    switch (tetromino.type) {
        case I: {
            switch (tetromino.rotation % 4) {
                case 0: {
                    if (y >= (2*BSIZE) && y <= (GAME_HEIGHT-(2*BSIZE))
                        && (pixels[x+2*BSIZE][y+BSIZE].isActive || pixels[x+2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y].isActive || pixels[x+2*BSIZE][y].isEmpty)
                        && (pixels[x+2*BSIZE][y-BSIZE].isActive || pixels[x+2*BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y-2*BSIZE].isActive || pixels[x+2*BSIZE][y-2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+2*BSIZE, y-2*BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+2*BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+2*BSIZE, y, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 1: {
                    if (x >= (2*BSIZE) && x <= (GAME_WIDTH-(2*BSIZE))
                        && (pixels[x-2*BSIZE][y+BSIZE].isActive || pixels[x-2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x][y+BSIZE].isActive || pixels[x][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 2: {
                    if (y >= BSIZE && y <= (GAME_HEIGHT-(3*BSIZE))
                        && (pixels[x+BSIZE][y-BSIZE].isActive || pixels[x+BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y].isActive || pixels[x+BSIZE][y].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 3: {
                    if (x >= BSIZE && x <= (GAME_WIDTH-(3*BSIZE))
                        && (pixels[x-BSIZE][y+2*BSIZE].isActive || pixels[x-BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x][y+2*BSIZE].isActive || pixels[x][y+2*BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y+2*BSIZE].isActive || pixels[x+2*BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
            }
        } break;

        case O: break;

        case T: {
            switch (tetromino.rotation % 4) {
                case 0: {
                    if (y >= BSIZE
                        && (pixels[x+BSIZE][y-BSIZE].isActive || pixels[x+BSIZE][y-BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+2*BSIZE, y, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 1: {
                    if (x >= BSIZE
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x, y, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 2: {
                    if (y <= (GAME_HEIGHT-BSIZE)
                        && (pixels[x][y+2*BSIZE].isActive || pixels[x][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x, y, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 3: {
                    if (x <= (GAME_WIDTH-2*BSIZE)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
            }            
        } break;

        case L: {
            switch (tetromino.rotation % 4) {
                case 0: {
                    if (y >= BSIZE
                        && (pixels[x+BSIZE][y-BSIZE].isActive || pixels[x+BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y-BSIZE].isActive || pixels[x+2*BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+2*BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 1: {
                    if (x >= BSIZE
                        && (pixels[x-BSIZE][y].isActive || pixels[x-BSIZE][y].isEmpty)
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-BSIZE, y, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 2: {
                    if (y <= (GAME_HEIGHT - 3*BSIZE)
                        && (pixels[x+BSIZE][y].isActive || pixels[x+BSIZE][y].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x][y+2*BSIZE].isActive || pixels[x][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 3: {
                    if (x <= (GAME_WIDTH-2*BSIZE)
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
            }            
        } break;

        case J: {
            switch (tetromino.rotation % 4) {
                case 0: {
                    if (y >= BSIZE
                        && (pixels[x+BSIZE][y-BSIZE].isActive || pixels[x+BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y+BSIZE].isActive || pixels[x+2*BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 1: {
                    if (x >= BSIZE
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y].isActive || pixels[x+BSIZE][y].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 2: {
                    if (y <= (GAME_HEIGHT - 3*BSIZE)
                        && (pixels[x-2*BSIZE][y].isActive || pixels[x-2*BSIZE][y].isEmpty)
                        && (pixels[x-BSIZE][y].isActive || pixels[x-BSIZE][y].isEmpty)
                        && (pixels[x-BSIZE][y+2*BSIZE].isActive || pixels[x-BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-2*BSIZE, y, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x-BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 3: {
                    if (x <= (GAME_WIDTH-3*BSIZE)
                        && (pixels[x][y+BSIZE].isActive || pixels[x][y+BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y+BSIZE].isActive || pixels[x+2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x][y+2*BSIZE].isActive || pixels[x][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
            }            
        } break;

        // TODO
        case Z: {
            switch (tetromino.rotation % 4) {
                case 0: {
                    if (y >= (2*BSIZE) && y <= (GAME_HEIGHT-(2*BSIZE))
                        && (pixels[x+2*BSIZE][y+BSIZE].isActive || pixels[x+2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y].isActive || pixels[x+2*BSIZE][y].isEmpty)
                        && (pixels[x+2*BSIZE][y-BSIZE].isActive || pixels[x+2*BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y-2*BSIZE].isActive || pixels[x+2*BSIZE][y-2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+2*BSIZE, y-2*BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+2*BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+2*BSIZE, y, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 1: {
                    if (x >= (2*BSIZE) && x <= (GAME_WIDTH-(2*BSIZE))
                        && (pixels[x-2*BSIZE][y+BSIZE].isActive || pixels[x-2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x][y+BSIZE].isActive || pixels[x][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 2: {
                    if (y >= BSIZE && y <= (GAME_HEIGHT-(3*BSIZE))
                        && (pixels[x+BSIZE][y-BSIZE].isActive || pixels[x+BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y].isActive || pixels[x+BSIZE][y].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 3: {
                    if (x >= BSIZE && x <= (GAME_WIDTH-(2*BSIZE))
                        && (pixels[x-BSIZE][y+2*BSIZE].isActive || pixels[x-BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x][y+2*BSIZE].isActive || pixels[x][y+2*BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y+2*BSIZE].isActive || pixels[x+2*BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
            }            
        } break;

        // TODO
        case S: {
            switch (tetromino.rotation % 4) {
                case 0: {
                    if (y >= (2*BSIZE) && y <= (GAME_HEIGHT-(2*BSIZE))
                        && (pixels[x+2*BSIZE][y+BSIZE].isActive || pixels[x+2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y].isActive || pixels[x+2*BSIZE][y].isEmpty)
                        && (pixels[x+2*BSIZE][y-BSIZE].isActive || pixels[x+2*BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y-2*BSIZE].isActive || pixels[x+2*BSIZE][y-2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+2*BSIZE, y-2*BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+2*BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+2*BSIZE, y, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 1: {
                    if (x >= (2*BSIZE) && x <= (GAME_WIDTH-(2*BSIZE))
                        && (pixels[x-2*BSIZE][y+BSIZE].isActive || pixels[x-2*BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x-BSIZE][y+BSIZE].isActive || pixels[x-BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x][y+BSIZE].isActive || pixels[x][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-2*BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x-BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 2: {
                    if (y >= BSIZE && y <= (GAME_HEIGHT-(3*BSIZE))
                        && (pixels[x+BSIZE][y-BSIZE].isActive || pixels[x+BSIZE][y-BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y].isActive || pixels[x+BSIZE][y].isEmpty)
                        && (pixels[x+BSIZE][y+BSIZE].isActive || pixels[x+BSIZE][y+BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x+BSIZE, y-BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x+BSIZE, y, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
                case 3: {
                    if (x >= BSIZE && x <= (GAME_WIDTH-(2*BSIZE))
                        && (pixels[x-BSIZE][y+2*BSIZE].isActive || pixels[x-BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x][y+2*BSIZE].isActive || pixels[x][y+2*BSIZE].isEmpty)
                        && (pixels[x+BSIZE][y+2*BSIZE].isActive || pixels[x+BSIZE][y+2*BSIZE].isEmpty)
                        && (pixels[x+2*BSIZE][y+2*BSIZE].isActive || pixels[x+2*BSIZE][y+2*BSIZE].isEmpty)) {
                        clearTetrominoBlocks();
                        tetromino.blocks[0] = spawnBlock(x-BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[1] = spawnBlock(x, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[2] = spawnBlock(x+BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.blocks[3] = spawnBlock(x+2*BSIZE, y+2*BSIZE, tetromino.color);
                        tetromino.rotation++;
                    }
                } break;
            }            
        } break;

        default: break;
    }
    return oldRotation != tetromino.rotation;
}