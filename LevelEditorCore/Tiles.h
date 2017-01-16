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

/** Create a tile with values given by the functionparameter list
* \param x represent X-Coord of the tile on the SCREEN
* \param y represent Y-Coord of the tile on the SCREEN
* \param w represent width of an tile
* \param h represent height of an tile
* \param index represent the index of an tile, which determines in which order it shall be drawn
* \param type represent the type of the tile as an integer
*
* \returns a copy of an initilised tile.
*
*/
Tile createTile(int x, int y, int w, int h, int index, int type);

/** Load an specific image containing several different Tiles into an TileSet
* \param location specified the location on the disk
* \param Set the struct where the results should be stored
* \param renderer for some stupid reasons you need this, DON'T ask why. just do it.

* This function initilised all tiles in the tilset with the screen coordinates 0,0.
* If you want to use the tiles indivdually this behaviour is fine. But in case of
* rendering the tiles as "map" onto the screen this makes no sense because all tiles
* would be drawn at 0,0.
* 
* IT JUST LOAD ALL METADATA FOR LATER USE. 
*/
void loadTileSet(const std::string& location, TileSet* Set,SDL_Renderer* renderer);


/** Gives you a COPY of an tile saved in a TileSet
* \param Set is the Tileset storing all metainformation of available tiles
* \param type is a string which is used as key to access the corresponding tile
* \returns COPY of corresponding stored TILE within the TileSet
*/
Tile getTile(TileSet* Set, const std::string& type);


/** Renders a specific Tile of given Type onto the screen at given Coordinates
* \param Set is TileSet with the corresponding Tiles
* \param type is the tile type stored in the given TileSet
* \param x represent X-Coord of the tile on the SCREEN
* \param y represent Y-Coord of the tile on the SCREEN
* 
* Draws a single Tile onto the Screen at the given Coordinates X,Y
*
*/
void renderSingleTile(TileSet* Set, const std::string& TileType, int x, int y);

