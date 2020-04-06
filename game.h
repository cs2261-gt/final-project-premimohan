// function prototypes
void initGame();
void updateGame();
void drawGame();
void initPlatform();
void initGummy();
void initBees();
void updateGummy();
void aniBees();

// platform struct definition
typedef struct {
    int screenRow;
    int screenCol;
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
#define MAXPLATLEN 20

// max number of bees on screen
#define MAXBEELEN 4

// gravity 
#define GRAVITY 100
#define JUMPPOWER 1500