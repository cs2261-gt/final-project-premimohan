#include "myLib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
// import spritesheet and gamescreen
#include "spritesheet.h"
#include "clouds.h"

// create time variable
int time;
// create voff and hoff variables
int vOff;
int hOff;

// create pool of platforms
Platform platforms[MAXPLATLEN];
// create a gummy bear instance
Gummy gummy;
// create pool of bees
Bee bees[MAXBEELEN];

// states used for animating bees
enum {T0, T1, T2, BEERIGHT, T4, BEELEFT};

// function prototypes
void goToLose();

// initialize the game and increments the time variable
void initGame() {
    vOff = 352;
    hOff = 0;
    initPlatform();
    initGummy();
    initBees();
    time++;
}

void initPlatform() {
    platforms[0].worldRow = SCREENHEIGHT - 9 + vOff;
    platforms[0].worldCol = rand() % 223 + hOff;
    platforms[0].screenRow = platforms[0].worldRow - vOff;
    platforms[0].screenCol = platforms[0].worldCol - hOff;
    platforms[0].rdel = 8;
    platforms[0].width = 16;
    platforms[0].height = 8;
    platforms[0].active = 1;
    for (int i = 1; i < MAXPLATLEN; i++) {
        platforms[i].worldRow = platforms[i-1].worldRow - 15 + vOff;
        platforms[i].worldCol = rand() % 223 + hOff;
        platforms[i].screenRow = platforms[i].worldRow - vOff;
        platforms[i].screenCol = platforms[i].worldCol - hOff;
        platforms[i].rdel = 8;
        platforms[i].width = 16;
        platforms[i].height = 8;
        platforms[i].active = 1;
    }
}

void initGummy() {
    gummy.width = 8;
    gummy.height = 16;
    gummy.active = 1;
    gummy.worldRow = SHIFTUP(platforms[0].worldRow - gummy.height + 4);
    gummy.worldCol = platforms[0].worldCol + 6;
    // not sure how to get the screenrow from worldrow
    //gummy.screenRow = SHIFTDOWN(gummy.worldRow - vOff);
    //gummy.screenCol = gummy.worldCol - hOff;
    // need to implement gravity and change initial rdel
    gummy.rdel = 0; 
    // change cdel depending on how far gummy should be able to jump
    gummy.cdel = 2;
}

void initBees() {
    for (int i = 0; i < MAXBEELEN; i++) {
        bees[i].worldRow = rand() % 151 + vOff;
        bees[i].worldCol = rand() % 176 + hOff;
        bees[i].screenRow = bees[i].worldRow - vOff;
        bees[i].screenCol = bees[i].worldCol - hOff;
        bees[i].minCol = bees[i].worldCol;
        bees[i].maxCol = bees[i].worldCol + 64;
        bees[i].active = 1;
        bees[i].rdel = 0;
        bees[i].cdel = 16;
        bees[i].height = 8;
        bees[i].width = 16;
        bees[i].aniCounter = 0;
        bees[i].aniState = BEERIGHT;
        bees[i].curFrame = 0;
        bees[i].numFrames = 3;
    }
}

void updateGame() {
    for (int i = 0; i < MAXBEELEN; i++) {
        bees[i].aniCounter++;
    }
    updateGummy();
    aniBees();
}

// premi what's happening in this method pls figure it out
void aniBees() {
        for (int i = 0; i < MAXBEELEN; i++) {
            if (bees[i].aniCounter % 50 == 0) {
            // update the col based on whether going right or left
                if (bees[i].aniState == BEERIGHT) {
                    bees[i].worldCol += bees[i].cdel;
                } else if (bees[i].aniState == BEELEFT) {
                    bees[i].worldCol -= bees[i].cdel;
                }
                // flip the bee around if it's at max/min col 
                if (bees[i].worldCol >= bees[i].maxCol) {
                    bees[i].aniState = BEELEFT;
                    bees[i].curFrame = 0;
                    bees[i].worldCol -= bees[i].cdel;
                } else if (bees[i].worldCol <= bees[i].minCol) {
                    bees[i].aniState = BEERIGHT;
                    bees[i].curFrame = 0;
                    bees[i].worldCol += bees[i].cdel;
                } else {
                    if (bees[i].curFrame == (bees[i].numFrames - 1)) {
                        bees[i].curFrame = 0;
                    } else {
                        bees[i].curFrame++;
                    }
                }
                bees[i].screenCol = bees[i].worldCol - hOff;
            }
        }
}

void updateGummy() {
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        gummy.screenCol += gummy.cdel;
    } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
        gummy.screenCol -= gummy.cdel;
    }
    // assuming this is where i implement gravity ?
    // if (BUTTON_PRESSED(BUTTON_UP)) {
    //     gummy.worldRow += gummy.rdel;
    // } else {
    //     gummy.rdel = 0;
    // }
    gummy.screenRow = SHIFTDOWN(gummy.worldRow) - vOff;
    gummy.screenCol = gummy.worldCol - hOff;
}

void drawGame() {
    // draw platforms
    for (int i = 0; i < MAXPLATLEN; i++) {
        shadowOAM[i].attr0 = (ROWMASK & platforms[i].screenRow) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_WIDE | ATTR0_NOBLEND;
        shadowOAM[i].attr1 = (COLMASK & platforms[i].screenCol) | ATTR1_TINY;
        shadowOAM[i].attr2 = ATTR2_TILEID(0, 0);
    }
    // draw gummy
    shadowOAM[127].attr0 = (ROWMASK & gummy.screenRow) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_TALL | ATTR0_NOBLEND;
    shadowOAM[127].attr1 = (COLMASK & gummy.screenCol) | ATTR1_TINY;
    shadowOAM[127].attr2 = ATTR2_TILEID(2, 0);
    // draw bees
    for (int i = 0; i < MAXBEELEN; i++) {
        shadowOAM[i + 20].attr0 = (ROWMASK & bees[i].screenRow) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_WIDE | ATTR0_NOBLEND;
        shadowOAM[i + 20].attr1 = (COLMASK & bees[i].screenCol) | ATTR1_TINY;
        shadowOAM[i + 20].attr2 = ATTR2_TILEID(bees[i].aniState, bees[i].curFrame);
    }
}