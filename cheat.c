#include "myLib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "cheat.h"
#include "game.h"
// import spritesheet and gamescreen
#include "spritesheet.h"
#include "clouds.h"

// create time variable
int time;
// create frame variable
int frame;
// create voff and hoff variables
int vOff;
int hOff;
// create hoff variable for clouds
int clouds_hOff;
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
void hideSprites();

// initialize the game and increments the time variable
void initCheat() {
    vOff = 352;
    hOff = 0;
    clouds_hOff = 0;
    initPlatform1();
    initGummy1();
    time++;
    frame++;
}

void initPlatform1() {
    platforms[0].worldRow = SCREENHEIGHT - 9 + vOff;
    platforms[0].worldCol = 112 + hOff;
    platforms[0].rdel = 8;
    platforms[0].width = 16;
    platforms[0].height = 8;
    platforms[0].active = 1;
    for (int i = 1; i < MAXPLATLEN; i++) {
        platforms[i].worldRow = platforms[i-1].worldRow - 15;
        platforms[i].worldCol = 112;
        platforms[i].rdel = 8;
        platforms[i].width = 16;
        platforms[i].height = 8;
        platforms[i].active = 1;
    }
}

void initGummy1() {
    gummy.width = 8;
    gummy.height = 16;
    gummy.active = 1;
    gummy.worldRow = SHIFTUP(SCREENHEIGHT - 9 - gummy.height + vOff);
    gummy.worldCol = platforms[0].worldCol + 6;
    // need to implement gravity and change initial rdel
    gummy.rdel = 0;
    // change cdel depending on how far gummy should be able to jump
    gummy.cdel = 2;
}


void updateCheat() {
    updatePlatform1();
    checkPlatformActive1();
    updateGummy1();
    if (frame == 25) {
        vOff -= (2 + SHIFTDOWN(gummy.rdel));
        clouds_hOff += 2;
        frame = 0;
    }
    time++;
    frame++;
}

void updateGummy1() {
    if (BUTTON_HELD(BUTTON_RIGHT)) {
        gummy.worldCol += gummy.cdel;
    } else if (BUTTON_HELD(BUTTON_LEFT)) {
        gummy.worldCol -= gummy.cdel;
    }
    if (BUTTON_PRESSED(BUTTON_UP)) {
        gummy.rdel -= JUMPPOWER;
    }
    if (time % 200) {
        gummy.rdel += GRAVITY;
    }
    // checking if it's on a platform
    if (!checkForPlatform()) {
        gummy.worldRow += gummy.rdel;
    } else {
        gummy.rdel = 0;
        gummy.rdel -= JUMPPOWER;
        gummy.worldRow += gummy.rdel;
    }
    gummy.screenRow = SHIFTDOWN(gummy.worldRow) - vOff;
    gummy.screenCol = gummy.worldCol - hOff;
}

int checkForBottom1() {
    return (gummy.screenRow > (SCREENHEIGHT - 16));
}

void updatePlatform1() {
    for  (int i = 0; i < MAXPLATLEN; i++) {
        if (platforms[i].active) {
            platforms[i].screenRow = platforms[i].worldRow - vOff;
            platforms[i].screenCol = platforms[i].worldCol - hOff;
        }
    }
}

void checkPlatformActive1() {
    for (int i = 0; i < MAXPLATLEN; i++) {
        if (platforms[i].screenRow > 160) { 
            if(i == 0){
                platforms[i].worldRow = platforms[9].worldRow - 16;
                platforms[i].worldCol = 112;
            } else {
                platforms[i].worldRow = platforms[i-1].worldRow - 16;
                platforms[i].worldCol = 112;
            }
        }
    }
}

int checkForPlatform1() {
    for (int i = 0; i < MAXPLATLEN; i++) {
        if (collision(platforms[i].screenCol, platforms[i].screenRow, platforms[i].width, platforms[i].height, 
            gummy.screenCol, gummy.screenRow, gummy.width, gummy.height)) {
            return 1;
        }
    }
    return 0;
}

int checkWhichPlatform1() {
    for (int i = 0; i < MAXPLATLEN; i++) {
        if (collision(platforms[i].screenCol, platforms[i].screenRow, platforms[i].width, platforms[i].height, 
            gummy.screenCol, gummy.screenRow, gummy.width, gummy.height)) {
            return platforms[i].worldRow;
        }
    }
    return 0;
}

void drawCheat() {
    // draw platforms
    for (int i = 0; i < MAXPLATLEN; i++) {
        if (platforms[i].screenRow > 0 && platforms[i].active && platforms[i].screenRow < SCREENHEIGHT) {
            shadowOAM[i].attr0 = (ROWMASK & platforms[i].screenRow) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_WIDE | ATTR0_NOBLEND;
            shadowOAM[i].attr1 = (COLMASK & platforms[i].screenCol) | ATTR1_TINY;
            shadowOAM[i].attr2 = ATTR2_TILEID(0, 0);
        } else {
            shadowOAM[i].attr0 = ATTR0_HIDE;
        }

    }
    // draw gummy
    shadowOAM[127].attr0 = (ROWMASK & gummy.screenRow) | ATTR0_REGULAR | ATTR0_4BPP | ATTR0_TALL | ATTR0_NOBLEND;
    shadowOAM[127].attr1 = (COLMASK & gummy.screenCol) | ATTR1_TINY;
    shadowOAM[127].attr2 = ATTR2_TILEID(2, 0);
}