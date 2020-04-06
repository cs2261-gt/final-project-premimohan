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
    initPlatform();
    initGummy();
    initBees();
    time++;
}

void initPlatform() {
    platforms[0].screenRow = 152;
    platforms[0].screenCol = rand() % 240;
    platforms[0].rdel = 8;
    platforms[0].width = 16;
    platforms[0].height = 8;
    platforms[0].active = 1;
    for (int i = 1; i < MAXPLATLEN; i++) {
        platforms[i].screenRow = platforms[i-1].screenRow - 16;
        platforms[i].screenCol = rand() % 240;
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
    gummy.screenRow = platforms[0].screenRow - gummy.height + 4;
    gummy.screenCol = platforms[0].screenCol + 7;
    // need to implement gravity and change initial rdel
    gummy.rdel = 16; 
    // change cdel depending on how far gummy should be able to jump
    gummy.cdel = 2;
}

void initBees() {
    for (int i = 0; i < MAXBEELEN; i++) {
        bees[i].screenRow = rand() % 320;
        bees[i].screenCol = rand() % 240;
        bees[i].active = 1;
        bees[i].rdel = 0;
        bees[i].cdel = 16;
        bees[i].height = 8;
        bees[i].width = 16;
        bees[i].aniCounter = 0;
        bees[i].aniState = BEERIGHT;
        bees[i].curFrame = 0;
        bees[i].numFrames = 3;
        bees[i].minCol = bees[i].screenCol;
        bees[i].maxCol = bees[i].screenCol + 63;
    }
}

void updateGame() {
    for (int i = 0; i < MAXBEELEN; i++) {
        bees[i].aniCounter++;
    }
    updateGummy();
    aniBees();
}

void aniBees() {
    if (bees[0].aniCounter % 18 == 0) {
        for (int i = 0; i < MAXBEELEN; i++) {
            bees[i].screenCol += (bees[i].cdel-1);
            if (bees[i].screenCol == bees[i].maxCol) {
                bees[i].aniState = BEELEFT;
            } 
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
    if (BUTTON_PRESSED(BUTTON_UP)) {
        gummy.screenRow -= gummy.rdel;
    }
}

void drawGame() {
    // draw platforms
    for (int i = 0; i < MAXPLATLEN; i++) {
        shadowOAM[i].attr0 = platforms[i].screenRow | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_WIDE | ATTR0_NOBLEND;
        shadowOAM[i].attr1 = platforms[i].screenCol | ATTR1_TINY;
        shadowOAM[i].attr2 = ATTR2_TILEID(0, 0);
    }
    // draw gummy
    shadowOAM[127].attr0 = gummy.screenRow | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_TALL | ATTR0_NOBLEND;
    shadowOAM[127].attr1 = gummy.screenCol | ATTR1_TINY;
    shadowOAM[127].attr2 = ATTR2_TILEID(2, 0);
    // draw bees
    for (int i = 0; i < MAXBEELEN; i++) {
        shadowOAM[i + 20].attr0 = bees[i].screenRow | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_WIDE | ATTR0_NOBLEND;
        shadowOAM[i + 20].attr1 = bees[i].screenCol | ATTR1_TINY;
        shadowOAM[i + 20].attr2 = ATTR2_TILEID(bees[i].aniState, bees[i].curFrame*2);
    }
}