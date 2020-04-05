
//{{BLOCK(instructScreen)

//======================================================================
//
//	instructScreen, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 136 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4352 + 2048 = 6912
//
//	Time-stamp: 2020-04-04, 22:29:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_INSTRUCTSCREEN_H
#define GRIT_INSTRUCTSCREEN_H

#define instructScreenTilesLen 4352
extern const unsigned short instructScreenTiles[2176];

#define instructScreenMapLen 2048
extern const unsigned short instructScreenMap[1024];

#define instructScreenPalLen 512
extern const unsigned short instructScreenPal[256];

#endif // GRIT_INSTRUCTSCREEN_H

//}}BLOCK(instructScreen)
