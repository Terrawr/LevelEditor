#include "Tiles.h"
#include <fstream>
#include <sstream>


/***
/path/to/tilesheet/imagefile.bmp
grass 0 0 30 30
ground 0 30 30 30
door 0 60 60 30
...
...
...
*/


void loadTileSet(const std::string& location,TileSet* Set) {
	std::ifstream tileset(location.c_str()); //<--read-only access
	std::string imagepath;
	///Read the Header
	std::string line;
	std::getline(tileset, line);

	loadFromFile(&Set->Tilesheet, (char*)line.c_str());
	line.clear();

	while (std::getline(tileset, line))  //<-- Read one line of Content till the end of File
	{
		std::istringstream iss(line);
		int tileX, tileY; //<-- Position on the Tilesheet
		int tileW, tileH; //<-- Outlines of the actuall Tile
		std::string TileType; //<-- Type of the tile
		if (!(iss >> TileType >> tileX >> tileY >> tileW >> tileH)) { break; } //<-- Read values of an line or quit loop if error occured
		
		Set->TileTypes.insert(TileType);
		Set->TileSetMetaInformaton.insert(
			std::make_pair(TileType,
				createRectShape((float)tileX, (float)tileY, (float)tileW, (float)tileH)
			));
	}

	return;
}