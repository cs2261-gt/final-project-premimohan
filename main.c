/**
Finished in the game so far:
- states have been implemented
- player can lose the game if they fall to the bottom of the screen or hit the bee
- screen automatically scrolls up as the game progresses
- player can jump on the platforms and platforms scroll up
- bees reappear after moving off screen with proper collision
- moving cloud background in the game state
- cheat state

What still needs to be added:
- fix all the art and make the backgrounds pretty

Bugs I have found:

How to play the game in its current state:
- As soon as you go to the game state, you have to press the "up" arrow to move up
- The gummy will automatically bound on platforms, however to move every further up
    you need to press the "up" arrow
- To move left and right, press the respective arrow keys
- To move through the states, press the start key
- Also press the start key to restart the game after losing the game
****** - to enable the cheat mode, press button A in the game state
**/

#include "myLib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "lose.h"
#include "cheat.h"
#include "sound.h"
#include "startScreen.h"
#include "instructScreen.h"
#include "loseScreen.h"
#include "clouds.h"
#include "spritesheet.h"
#include "candy.h"
#include "pauseScreen.h"
// include sound files
#include "gummySong.h"
#include "loseSound.h"

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

// cheat check
int cheat;

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
    setupSounds();
    setupInterrupts();
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
        stopSound();
        playSoundA(gummySong, GUMMYSONGLEN, 1);
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
    // load the candy background (bg 0) palette and tiles
    DMANow(3, candyPal, PALETTE, 256);
    DMANow(3, candyTiles, &CHARBLOCK[0], candyTilesLen/2);
    DMANow(3, candyMap, &SCREENBLOCK[28], candyMapLen/2);
    // set the bg 0 control register
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_TALL;
    // move the screen onto the candy map
    REG_BG1VOFF = vOff;
    REG_BG1HOFF = hOff;
    // load the clouds background (bg 1) tiles
    DMANow(3, cloudsTiles, &CHARBLOCK[1], cloudsTilesLen/2);
    DMANow(3, cloudsMap, &SCREENBLOCK[30], cloudsMapLen/2);
    // set up the bg 1 control register
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(30) | BG_4BPP | BG_SIZE_WIDE;
    // move the screen onto the clouds map
    REG_BG0HOFF = clouds_hOff;
    // load spritesheet tiles and palette into memory
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen / 2);
    // hide all the sprites
    hideSprites();
    // enable the sprites
    REG_DISPCTL = MODE0 | BG1_ENABLE | BG0_ENABLE | SPRITE_ENABLE; 
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
    // dma the shadowoam to the oam
    DMANow(3, shadowOAM, OAM, 512);
    // move the candy background according to voff and hoff
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;
    // move the cloud background based on the hoff
    REG_BG0HOFF = clouds_hOff;
    // if the player presses start, go to pause state
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPause();
    }
    if (BUTTON_PRESSED(BUTTON_A)) {
        goToCheat();
        cheat = 1;
    }
    if (checkForBee()) {
        stopSound();
        playSoundB(loseSound, LOSESOUNDLEN, 0);
        goToLose();
        initLose();
    }
    if (checkForBottom()) {
        stopSound();
        playSoundB(loseSound, LOSESOUNDLEN, 0);
        goToLose();
        initLose();
    }
}

void goToPause() {
    // setting the frame rate
    waitForVBlank();
    // enable mode 0 and background 0
    DMANow(3, pauseScreenPal, PALETTE, 256);
    DMANow(3, pauseScreenTiles, &CHARBLOCK[0], pauseScreenTilesLen/2);
    DMANow(3, pauseScreenMap, &SCREENBLOCK[28], pauseScreenMapLen/2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 512);
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_SMALL; 
    REG_BG0HOFF = 8;
    // set the state of the game to PAUSE
    state = PAUSE;

}

void pauseState() {
    // setting the frame rate
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START)) {
        if (cheat) {
            goToCheat();
        } else {
            goToGame();
        }
    }

}

void goToCheat() {
        // setting the frame rate
    waitForVBlank();
    // load the candy background (bg 0) palette and tiles
    DMANow(3, candyPal, PALETTE, 256);
    DMANow(3, candyTiles, &CHARBLOCK[0], candyTilesLen/2);
    DMANow(3, candyMap, &SCREENBLOCK[28], candyMapLen/2);
    // set the bg 0 control register
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_TALL;
    // move the screen onto the candy map
    REG_BG1VOFF = vOff;
    REG_BG1HOFF = hOff;
    // load the clouds background (bg 1) tiles
    DMANow(3, cloudsTiles, &CHARBLOCK[1], cloudsTilesLen/2);
    DMANow(3, cloudsMap, &SCREENBLOCK[30], cloudsMapLen/2);
    // set up the bg 1 control register
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(30) | BG_4BPP | BG_SIZE_WIDE;
    // move the screen onto the clouds map
    REG_BG0HOFF = clouds_hOff;
    // load spritesheet tiles and palette into memory
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen / 2);
    // hide all the sprites
    hideSprites();
    // enable the sprites
    REG_DISPCTL = MODE0 | BG1_ENABLE | BG0_ENABLE | SPRITE_ENABLE; 
    // wait for vblank
    waitForVBlank();
    // dma the shadowoam to the oam
    DMANow(3, shadowOAM, OAM, 512);
    // set the state of the game to GAME
    state = CHEAT;

}

void cheatState() {
    // update the game
    updateCheat();
    // draw the sprites
    drawCheat();
    // setting the frame rate
    waitForVBlank();
    // dma the shadowoam to the oam
    DMANow(3, shadowOAM, OAM, 512);
    // move the candy background according to voff and hoff
    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;
    // move the cloud background based on the hoff
    REG_BG0HOFF = clouds_hOff;
    // if the player presses start, go to pause state
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPause();
    }
    if (checkForBottom1()) {
        stopSound();
        playSoundB(loseSound, LOSESOUNDLEN, 0);
        goToLose();
        initLose();
    }

}

void goToLose() {
    // setting the frame rate
    waitForVBlank();
    // enable mode 0 and background 0
    DMANow(3, loseScreenPal, PALETTE, 256);
    DMANow(3, loseScreenTiles, &CHARBLOCK[0], loseScreenTilesLen/2);
    DMANow(3, loseScreenMap, &SCREENBLOCK[28], loseScreenMapLen/2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 512);
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_SMALL; 
    REG_BG0HOFF = 0;
    REG_BG0VOFF = 0;
    // set the state of the game to LOSE;
    state = LOSE;
}

void loseState() {
    updateLose();
    drawLose();
    // setting the frame rate
    waitForVBlank();
    // dma shadowOAM to OAM
    DMANow(3, shadowOAM, OAM, 512);
    if (BUTTON_PRESSED(BUTTON_START)) {
        // go to start function
        cheat = 0;
        goToStart();
    }
}
