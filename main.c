#include "myLib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "startScreen.h"
#include "instructScreen.h"

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
    // increment the seed
    seed++;
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
    if (BUTTON_PRESSED(BUTTON_START)) {
        // gotogame function
        goToGame();
        // initialize the game state
        // initGame();
        // seed the random function
        srand(seed);
    }

}

void goToGame() {
    
}

void gameState() {

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
