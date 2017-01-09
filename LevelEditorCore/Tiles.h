#pragma once
#include <SDL2\SDL.h>

//Describes the possible Types for Tiles
typedef enum {
	UNKOWN,
	NONE,
	BACKGROUND,
	MAXCOUNT_OF_TYPES
}TILETYPES;

typedef struct TILEMETAINFORMATION {

	int x, y;					//Position on Screen
	int TileWidth, TileHeight;  //
	int TileType;				//TileType
	int LayerIndex;				//Describes in which layer the Tile should be drawn
	SDL_Texture* TileSheet;		//ImageSource
	SDl_Rect*    TypeClip;		//Area & Coord within the ImageSource

}Tile;