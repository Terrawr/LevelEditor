#pragma once
#include <SDL.h>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include "LevelEditor.h"
#include "Texture.h"


//Describes the possible Types for Tiles
typedef enum {
	_UNKOWN,
	GRAPHIC_NONE,
	LOGIC_NONE,
	GRAPHIC_BACKGROUND,
	LOGIC_BACKGROUND,
	MAXCOUNT_OF_TYPES
}TILETYPES;

typedef struct TILEMETAINFORMATION {

	int x, y;					//Position on Screen
	int TileWidth, TileHeight;  //
	int TileType;				//TileType
	int LayerIndex;				//Describes in which layer the Tile should be drawn
	
	
}Tile;

typedef struct TILESETMETAINFORMATION
{
	std::set<std::string>		TileTypes; //<-- Because we never know how many different types of tiles a new map could contain we store all types provided by the user here as string
	Texture						Tilesheet; //<-- The Actual image where all tiles a stored used for in one Map
	std::map<std::string, Tile>	TileSetMetaInformaton; //<-- Here we store all the information where and in which size the tiles are stored within the image aka our used tilesheet!!!



}TileSet;


Tile createTile(int x, int y, int w, int h, int index, int type);
/** Load an specific image containing several different Tiles

 */
void loadTileSet(const std::string& location, TileSet* Set,SDL_Renderer*);

Tile getTile(TileSet* Set, const std::string& type);

