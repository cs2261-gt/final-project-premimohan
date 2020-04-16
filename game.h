// function prototypes
void initGame();
void updateGame();
void drawGame();
void initPlatform();
void initGummy();
void initBees();
void updateGummy();
void aniBees();
int checkForPlatform();
int checkForBee();
int checkForBottom();
void updatePlatform();
void updateBees();
//void updateBG();
int checkWhichPlatform();
void checkPlatformActive();
void platformPop();
void checkBeeActive();

// platform struct definition
typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;
    int active;
} Platform;

// gummy struct definition
typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;
    int active;
} Gummy;

// bee struct definition
typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int minCol;
    int maxCol;
    int rdel;
    int cdel;
    int width;
    int height;
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int active;
} Bee;

// max number of platforms
#define MAXPLATLEN 10

// max number of bees on screen
#define MAXBEELEN 4

// gravity 
#define GRAVITY 3
#define JUMPPOWER 200

// constants
#define WORLDHEIGHT 512
#define WORLDWIDTH 256

// voff and hoff variables
extern int hOff;
extern int vOff;