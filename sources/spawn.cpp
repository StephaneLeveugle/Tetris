Block spawnBlock(u16 startX, u16 startY, u32 color) {
    for (u16 i = startY; i < startY+BSIZE; i++) {
        for (u16 j = startX; j < startX+BSIZE; j++) {
            pxl.color = color;
            pxl.isActive = true;
            pxl.isEmpty = false;
        }
    }
    Block block = {startX, startY, color};
    return block;
}

void clearBlock(u16 startX, u16 startY) {
    for (u16 i = startY; i < startY+BSIZE; i++) {
        for (u16 j = startX; j < startX+BSIZE; j++) {
            pxl = {};
        }
    }
}

void clearTetrominoBlocks() {
    clearBlock(tetromino.blocks[0].x, tetromino.blocks[0].y);
    clearBlock(tetromino.blocks[1].x, tetromino.blocks[1].y);
    clearBlock(tetromino.blocks[2].x, tetromino.blocks[2].y);
    clearBlock(tetromino.blocks[3].x, tetromino.blocks[3].y);
}

void spawnI(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT - BSIZE) {
    const u32 cyan = 0x0000ffff;
    tetromino.color = cyan;
    tetromino.type = TetrominoType::I;
    tetromino.blocks[0] = spawnBlock(startX, startY, cyan);
    tetromino.blocks[1] = spawnBlock(startX + BSIZE, startY, cyan);
    tetromino.blocks[2] = spawnBlock(startX + 2*BSIZE, startY, cyan);
    tetromino.blocks[3] = spawnBlock(startX + 3*BSIZE, startY, cyan);
}

void spawnO(u16 startX = ((GAME_WIDTH/2)-BSIZE), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 yellow = 0x00ffff00;
    tetromino.color = yellow;
    tetromino.type = TetrominoType::O;
    tetromino.blocks[0] = spawnBlock(startX, startY, yellow);
    tetromino.blocks[1] = spawnBlock(startX + BSIZE, startY, yellow);
    tetromino.blocks[2] = spawnBlock(startX, startY + BSIZE, yellow);
    tetromino.blocks[3] = spawnBlock(startX + BSIZE, startY + BSIZE, yellow);
}

void spawnT(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT - (2*BSIZE)) {
    const u32 purple = 0x00800080;
    tetromino.color = purple;
    tetromino.type = TetrominoType::T;
    tetromino.blocks[0] = spawnBlock(startX, startY, purple);
    tetromino.blocks[1] = spawnBlock(startX + BSIZE, startY, purple);
    tetromino.blocks[2] = spawnBlock(startX + BSIZE, startY + BSIZE, purple);
    tetromino.blocks[3] = spawnBlock(startX + 2*BSIZE, startY, purple);
}

void spawnL(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 orange = 0x00FFA500;
    tetromino.color = orange;
    tetromino.type = TetrominoType::L;
    tetromino.blocks[0] = spawnBlock(startX, startY, orange);
    tetromino.blocks[1] = spawnBlock(startX + BSIZE, startY, orange);
    tetromino.blocks[2] = spawnBlock(startX + 2*BSIZE, startY, orange);
    tetromino.blocks[3] = spawnBlock(startX + 2*BSIZE, startY + BSIZE, orange);
}

void spawnJ(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 blue = 0x000000FF;
    tetromino.color = blue;
    tetromino.type = TetrominoType::J;
    tetromino.blocks[0] = spawnBlock(startX, startY, blue);
    tetromino.blocks[1] = spawnBlock(startX, startY+BSIZE, blue);
    tetromino.blocks[2] = spawnBlock(startX+BSIZE, startY, blue);
    tetromino.blocks[3] = spawnBlock(startX+(2*BSIZE), startY, blue);
}

void spawnZ(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-BSIZE) {
    const u32 red = 0x00FF0000;
    tetromino.color = red;
    tetromino.type = TetrominoType::Z;
    tetromino.blocks[0] = spawnBlock(startX, startY, red);
    tetromino.blocks[1] = spawnBlock(startX+BSIZE, startY, red);
    tetromino.blocks[2] = spawnBlock(startX+BSIZE, startY-BSIZE, red);
    tetromino.blocks[3] = spawnBlock(startX+(2*BSIZE), startY - BSIZE, red);
}

void spawnS(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 green = 0x0000FF00;
    tetromino.color = green;
    tetromino.type = TetrominoType::S;
    tetromino.blocks[0] = spawnBlock(startX, startY, green);
    tetromino.blocks[1] = spawnBlock(startX+BSIZE, startY, green);
    tetromino.blocks[2] = spawnBlock(startX+BSIZE, startY+BSIZE, green);
    tetromino.blocks[3] = spawnBlock(startX+(2*BSIZE), startY + BSIZE, green);
}

void spawnAny() {
    tetromino = {};
    int n = rand() % 7;
    n = 4; // test
    switch (n) {
        case 0: spawnI(); break;
        case 1: spawnO(); break;
        case 2: spawnT(); break;
        case 3: spawnL(); break;
        case 4: spawnJ(); break;
        case 5: spawnZ(); break;
        case 6: spawnS(); break;
    }
}