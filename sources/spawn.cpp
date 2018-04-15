Block spawnBlock(u16 startX, u16 startY, u32 color) {
    for (u16 i = startY; i < startY+BSIZE; i++) {
        for (u16 j = startX; j < startX+BSIZE; j++) {
            pxl.color = color;
            pxl.isActive = true;
            pxl.isEmpty = false;
        }
    }
    Block block = {startX, startY};
    return block;
}

void spawnI(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT - BSIZE) {
    const u32 cyan = 0x0000ffff;
    activeBlocks[0] = spawnBlock(startX, startY, cyan);
    activeBlocks[1] = spawnBlock(startX + BSIZE, startY, cyan);
    activeBlocks[2] = spawnBlock(startX + 2*BSIZE, startY, cyan);
    activeBlocks[3] = spawnBlock(startX + 3*BSIZE, startY, cyan);
}

void spawnO(u16 startX = ((GAME_WIDTH/2)-BSIZE), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 yellow = 0x00ffff00;
    activeBlocks[0] = spawnBlock(startX, startY, yellow);
    activeBlocks[1] = spawnBlock(startX + BSIZE, startY, yellow);
    activeBlocks[2] = spawnBlock(startX, startY + BSIZE, yellow);
    activeBlocks[3] = spawnBlock(startX + BSIZE, startY + BSIZE, yellow);
}

void spawnT(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT - BSIZE) {
    const u32 purple = 0x00800080;
    activeBlocks[0] = spawnBlock(startX, startY, purple);
    activeBlocks[1] = spawnBlock(startX + BSIZE, startY, purple);
    activeBlocks[2] = spawnBlock(startX + BSIZE, startY - BSIZE, purple);
    activeBlocks[3] = spawnBlock(startX + 2*BSIZE, startY, purple);
}

void spawnL(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 orange = 0x00FFA500;
    activeBlocks[0] = spawnBlock(startX, startY, orange);
    activeBlocks[1] = spawnBlock(startX, startY + BSIZE, orange);
    activeBlocks[2] = spawnBlock(startX+BSIZE, startY + BSIZE, orange);
    activeBlocks[3] = spawnBlock(startX+(2*BSIZE), startY + BSIZE, orange);
}

void spawnJ(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-BSIZE) {
    const u32 blue = 0x000000FF;
    activeBlocks[0] = spawnBlock(startX, startY, blue);
    activeBlocks[1] = spawnBlock(startX+BSIZE, startY, blue);
    activeBlocks[2] = spawnBlock(startX+(2*BSIZE), startY, blue);
    activeBlocks[3] = spawnBlock(startX+(2*BSIZE), startY - BSIZE, blue);
}

void spawnZ(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-BSIZE) {
    const u32 red = 0x00FF0000;
    activeBlocks[0] = spawnBlock(startX, startY, red);
    activeBlocks[1] = spawnBlock(startX+BSIZE, startY, red);
    activeBlocks[2] = spawnBlock(startX+BSIZE, startY-BSIZE, red);
    activeBlocks[3] = spawnBlock(startX+(2*BSIZE), startY - BSIZE, red);
}

void spawnS(u16 startX = ((GAME_WIDTH/2)-(2*BSIZE)), u16 startY = GAME_HEIGHT-(2*BSIZE)) {
    const u32 green = 0x0000FF00;
    activeBlocks[0] = spawnBlock(startX, startY, green);
    activeBlocks[1] = spawnBlock(startX+BSIZE, startY, green);
    activeBlocks[2] = spawnBlock(startX+BSIZE, startY+BSIZE, green);
    activeBlocks[3] = spawnBlock(startX+(2*BSIZE), startY + BSIZE, green);
}

void spawnAny() {
    int n = rand() % 7;
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