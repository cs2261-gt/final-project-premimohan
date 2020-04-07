#include "myLib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "startScreen.h"
#include "instructScreen.h"
#include "clouds.h"
#include "spritesheet.h"
#include "candy.h"

// buttons
unsigned short buttons;
unsigned short oldButtons;

// create shadowOAM
OBJ_ATTR shadowOAM[128];

// states of game
enum {START, INSTRUCT, GAME, CHEAT, PAUSE, LOSE};
int state;

// random seed
int seed;

// prototypes of functions
void initialize();
void startState();
void instructState();
void gameState();
void cheatState();
void pauseState();
void loseState();
void goToStart();
void goToInstruct();
void goToGame();
void goToCheat();
void goToLose();
void goToPause();

int main() {
    // initialize the GBA settings
    initialize();
    while(1) {
        // update the button variables
        oldButtons = buttons;
        buttons = BUTTONS;
        // check state of the game and go to appropriate function
        switch(state) {
            case(START):
                startState();
            break;
            case(INSTRUCT):
                instructState();
            break;
            case(GAME):
                gameState();
            break;
            case(CHEAT):
                cheatState();
            break;
            case(LOSE):
                loseState();
            break;
            case(PAUSE):
                pauseState();
            break;
        }
    }
}

void initialize() {
    goToStart();
}

void goToStart() {
    // setting the frame rate
    waitForVBlank();
    // enable mode 0 and background 0
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    DMANow(3, startScreenPal, PALETTE, 256);
    DMANow(3, startScreenTiles, &CHARBLOCK[0], startScreenTilesLen/2);
    DMANow(3, startScreenMap, &SCREENBLOCK[28], startScreenMapLen/2);
    // set the background 0 register
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_SMALL; 
    // change the state of the game to START
    state = START;
}

void startState() {
    // setting the frame rate
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START)) {
        // go to instructions function
        goToInstruct();
    }
}

void goToInstruct() {
    // setting the frame rate
    waitForVBlank();
    // enable mode 0 and background 0
    DMANow(3, instructScreenPal, PALETTE, 256);
    DMANow(3, instructScreenTiles, &CHARBLOCK[0], instructScreenTilesLen/2);
    DMANow(3, instructScreenMap, &SCREENBLOCK[28], instructScreenMapLen/2);
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_SMALL; 
    // set the state of the game to INSTRUCT
    state = INSTRUCT;
}

void instructState() {
    // setting the frame rate
    waitForVBlank();
    // increment the seed
    seed++;
    if (BUTTON_PRESSED(BUTTON_START)) {
        // seed the random function
        srand(seed);
        // gotogame function
        goToGame();
        // initialize the game state
        initGame();
    }
}

void goToGame() {
    // setting the frame rate
    waitForVBlank();
    // load the background palette and tiles
    DMANow(3, candyPal, PALETTE, 256);
    DMANow(3, candyTiles, &CHARBLOCK[0], candyTilesLen/2);
    DMANow(3, candyMap, &SCREENBLOCK[28], candyMapLen/2);
    // set the background register
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_TALL;
    // move the screen onto the candy map
    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    // load spritesheet tiles and palette into memory
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen / 2);
    // hide all the sprites
    hideSprites();
    // enable the sprites
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE; 
    // wait for vblank
    waitForVBlank();
    // dma the shadowoam to the oam
    DMANow(3, shadowOAM, OAM, 512);
    // set the state of the game to GAME
    state = GAME;
}

void gameState() {
    // update the game
    updateGame();
    // draw the sprites
    drawGame();
    // setting the frame rate
    waitForVBlank();
    // copy the shadowOAM to the OAM
    DMANow(3, shadowOAM, OAM, 512);
    // move the screen according to voff and hoff
    REG_BG0HOFF = hOff;
    REG_BG0VOFF = vOff;
    // if the player presses start, go to pause state
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPause();
    }
}

void goToPause() {

}

void pauseState() {

}

void goToCheat() {

}

void cheatState() {

}

void goToLose() {

}

void loseState() {

}
