// function prototypes
void initCheat();
void updateCheat();
void drawCheat();
void initPlatform1();
void initGummy1();
void updateGummy1();
int checkForPlatform1();
int checkForBottom1();
void updatePlatform1();
int checkWhichPlatform1();
void checkPlatformActive1();

// // platform struct definition
// typedef struct {
//     int screenRow;
//     int screenCol;
//     int worldRow;
//     int worldCol;
//     int rdel;
//     int cdel;
//     int width;
//     int height;
//     int active;
// } Platform;

// // gummy struct definition
// typedef struct {
//     int screenRow;
//     int screenCol;
//     int worldRow;
//     int worldCol;
//     int rdel;
//     int cdel;
//     int width;
//     int height;
//     int active;
// } Gummy;

// // max number of platforms
// #define MAXPLATLEN 10

// // gravity 
// #define GRAVITY 3
// #define JUMPPOWER 200

// // constants
// #define WORLDHEIGHT 512
// #define WORLDWIDTH 256

// voff and hoff variables
extern int hOff;
extern int vOff;
extern int clouds_hOff;