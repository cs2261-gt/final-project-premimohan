#include  "spritesheet.h"
#include "myLib.h"
#include "lose.h"

// initialize crying bear sprite
ANISPRITE cryBear;

void initLose() {
    initCry();
}

void initCry() {
    cryBear.worldRow = 100;
    cryBear.worldCol = 112;
    cryBear.width = 16;
    cryBear.height = 32;
    cryBear.aniCounter = 0;
    cryBear.curFrame = 0;
    cryBear.numFrames = 3;
    cryBear.aniState = 7;
}

void updateLose() {
    cryBear.aniCounter++;
    updateCry();
    if (cryBear.aniCounter % 50 == 0) {
        if (cryBear.curFrame == (cryBear.numFrames - 1)) {
            cryBear.curFrame = 0;
        } else {
            cryBear.curFrame++;
        }
    }
}

void updateCry() {
    cryBear.screenRow = cryBear.worldRow;
    cryBear.screenCol = cryBear.worldCol;
}

void drawLose() {
    shadowOAM[30].attr0 = (cryBear.screenRow) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_TALL | ATTR0_NOBLEND;
    shadowOAM[30].attr1 = (cryBear.screenCol) | ATTR1_MEDIUM;
    shadowOAM[30].attr2 = ATTR2_TILEID(cryBear.aniState, cryBear.curFrame*4);
}