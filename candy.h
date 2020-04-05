
//{{BLOCK(candy)

//======================================================================
//
//	candy, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 246 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 7872 + 2048 = 10432
//
//	Time-stamp: 2020-04-04, 21:01:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CANDY_H
#define GRIT_CANDY_H

#define candyTilesLen 7872
extern const unsigned short candyTiles[3936];

#define candyMapLen 2048
extern const unsigned short candyMap[1024];

#define candyPalLen 512
extern const unsigned short candyPal[256];

#endif // GRIT_CANDY_H

//}}BLOCK(candy)
