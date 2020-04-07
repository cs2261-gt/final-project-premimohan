
//{{BLOCK(candy)

//======================================================================
//
//	candy, 256x512@4, 
//	+ palette 256 entries, not compressed
//	+ 219 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x64 
//	Total size: 512 + 7008 + 4096 = 11616
//
//	Time-stamp: 2020-04-06, 15:46:17
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CANDY_H
#define GRIT_CANDY_H

#define candyTilesLen 7008
extern const unsigned short candyTiles[3504];

#define candyMapLen 4096
extern const unsigned short candyMap[2048];

#define candyPalLen 512
extern const unsigned short candyPal[256];

#endif // GRIT_CANDY_H

//}}BLOCK(candy)
