#pragma once
#include <SDL.h>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include <fstream>
#include <sstream>

#include "LevelEditor.h"
#include "Texture.h"

#include "json.h"

using json = nlohmann::json;

#pragma region "oldtileengine interface version"

typedef std::vector<std::vector<std::vector< int>>>  array3D;

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

	int x, y;					//Position on TileSheet image file!!!!!!!!!!!!
	int TileWidth, TileHeight;  //
	int TileType;				//TileType
	int LayerIndex;				//Describes in which layer the Tile should be drawn
	
	
}Tile;

typedef struct TILESETMETAINFORMATION
{
	Texture						Tilesheet; //<-- The Actual image where all tiles a stored used for in one Map
	std::map<int, Tile>			TileSetMetaInformaton; //<-- Here we store all the information where and in which size the tiles are stored within the image aka our used tilesheet!!!
	std::map<std::string,int>	TileTypes; //<-- Because we never know how many different types of tiles a new map could contain we store all types provided by the user here as string



}TileSet;

typedef struct TILEMAP_LAYOUTINFORMATION {

	TileSet 				mCurrentTileset;
	array3D					mTileMap;

	int columns;
	int rows;

	TILEMAP_LAYOUTINFORMATION() : mTileMap(500, std::vector<std::vector<int>>(500, std::vector<int>(500))) {}

	TILEMAP_LAYOUTINFORMATION(int l,int r,int c) : mTileMap(l, std::vector<std::vector<int>>(r, std::vector<int>(c))) {}

} TileMap;

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
Tile te_createTile(int x, int y, int w, int h, int index, int type);

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
void te_loadTileSet(const std::string& location, TileSet* Set,SDL_Renderer* renderer);

/** Gives you a COPY of an tile saved in a TileSet
* \param Set is the Tileset storing all metainformation of available tiles
* \param type is a string which is used as key to access the corresponding tile
* \returns COPY of corresponding stored TILE within the TileSet
*/
Tile te_getTileFromTileset(TileSet* Set, const std::string& type);

/** Renders a specific Tile of given Type onto the screen at given Coordinates
* \param Set is TileSet with the corresponding Tiles
* \param type is the tile type stored in the given TileSet
* \param x represent X-Coord of the tile on the SCREEN
* \param y represent Y-Coord of the tile on the SCREEN
* 
* Draws a single Tile onto the Screen at the given Coordinates X,Y
*
*/
void re_renderSingleTile(TileSet* Set, const std::string& TileType, int x, int y);

TileMap				te_LoadTileMap(GameObj* obj, const std::string& PathToMap);
std::vector<Tile>	te_createRenderableTiles(GameObj* obj, TileMap* mapdata);
std::string te_translateTypeInformation(TileSet* Set, int type);

#pragma endregion

struct TM_TilesetImage {
	std::string path;
	int width, height;
};

struct TM_Tileset {
	std::string		Name;
	int GID;
	int TileW, TileH;
	TM_TilesetImage* TilesetImage;
};

struct TM_Layer {
	std::string		Name;
	int				width;
	int				height;
	std::vector<int>	TileID;
};

struct TM_TileMap {
	std::string				Name;
	std::vector<TM_Tileset> Tilesets;
	std::vector<TM_Layer>	Layers;
};


json		TM_loadTileMapJSON(const std::string& PathToMap);
TM_TileMap	TM_InitializeTileMapFromJSON(const json& Map);

void renderTileMap(TM_TileMap* Map, SDL_Renderer* renderer);





