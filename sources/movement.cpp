// checks for each activeBlock if 
// - it has reached the bottom OR
// - the pixel directly below the (x,y) coordinate is taken by a non active block
bool canMoveDown() {
    u16 x, y;
    for (int i = 0; i < 4; i++) {
        x = activeBlocks[i].x;
        y = activeBlocks[i].y;
        if (y == 0) return false;
        if (!pixels[y-1][x].isEmpty && !pixels[y-1][x].isActive) return false; 
    }
    return true;
}

void moveDown() {
    for (u16 i = 0; i < GAME_HEIGHT; i++) {
        for (u16 j = 0; j < GAME_WIDTH; j++) {
            if (pxl.isActive) {
                pixels[i-BSIZE][j] = {pxl.color, pxl.isActive, pxl.isEmpty};
                pxl = {};
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        activeBlocks[i].y -= BSIZE;
    }
}

// checks for each activeBlock if 
// - it has reached the left border OR
// - the pixel directly to the left of the (x,y) pixel is taken by a non active block
bool canMoveLeft() {
    u16 x, y;
    for (int i = 0; i < 4; i++) {
        x = activeBlocks[i].x;
        y = activeBlocks[i].y;
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
        activeBlocks[i].x -= BSIZE;
    }
}

// checks for each activeBlock if 
// - it has reached the right border OR
// - the pixel directly to the right of the (x,y) pixel is taken by a non active block
bool canMoveRight() {
    u16 x, y;
    for (int i = 0; i < 4; i++) {
        x = activeBlocks[i].x;
        y = activeBlocks[i].y;
        if (x == GAME_WIDTH-BSIZE) return false;
        if (!pixels[y][x+1].isEmpty && !pixels[y][x+1].isActive) return false; 
    }
    return true;
}

void moveRight() {
    for (u16 i = GAME_HEIGHT - 1; i != 0; i--) {
        for (u16 j = GAME_WIDTH - 1; j != 0; j--) {
            if (pxl.isActive) {
                pixels[i][j+BSIZE] = {pxl.color, pxl.isActive, pxl.isEmpty};
                pxl = {};
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        activeBlocks[i].x += BSIZE;
    }
}