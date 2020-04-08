// function prototypes
void initGame();
void updateGame();
void drawGame();
void initPlatform();
void initGummy();
void initBees();
void updateGummy();
void aniBees();
// int platformCol(int colA, int rowA, int widthA, int heightA, int colB, int rowB, int widthB, int heightB);
int checkForPlatform();
int checkForBee();
void updatePlatform();

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
#define JUMPPOWER 150

// constants
#define WORLDHEIGHT 512
#define WORLDWIDTH 256

// voff and hoff variables
extern int hOff;
extern int vOff;