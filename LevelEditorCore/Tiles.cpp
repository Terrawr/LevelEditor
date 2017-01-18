#include "Tiles.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>


/***
/path/to/tilesheet/imagefile.bmp
//TYPENAME TYPE INDEX X Y W H
grass 0 0 0 0 30 30
ground 1 0 0 30 30 30
door  2 0 0 60 60 30
...
...
...
*/

Tile createTile(int x, int y, int w, int h, int index, int type) {
	Tile tmp;
	tmp.LayerIndex = index;
	tmp.TileHeight = h;
	tmp.TileWidth = w;
	tmp.x = x;
	tmp.y = y;
	tmp.TileType = type;

	return tmp;
}

void loadTileSet(const std::string& location,TileSet* Set,SDL_Renderer* renderer) {
	std::fstream tileset(location.c_str(),std::ios_base::in|std::ios_base::out); //<--read-only access
	
	if (tileset.is_open()) {
		std::string imagepath;
		///Read the Header
		std::string line;
		std::getline(tileset, line);

		initilizeTexture(&Set->Tilesheet, renderer);
		loadFromFile(&Set->Tilesheet, (char*)line.c_str());
		line.clear();

		while (std::getline(tileset, line))  //<-- Read one line of Content till the end of File
		{
			std::istringstream iss(line);




			int tileX, tileY; //<-- Position on the Tilesheet
			int tileW, tileH; //<-- Outlines of the actuall Tile
			int index, intType;
			std::string TileType; //<-- Type of the tile


			if (!(iss >> TileType >> intType >> index >>tileX >> tileY >> tileW >> tileH)) {
				SDL_Log("FileEnd"); continue;; //<-- skip if line is corrupted
			} //<-- Read values of an line or quit loop if error occured

			iss >> TileType;
			iss >> intType;

			SDL_Log("Tile(%s) \t[%d|%d] \t{w = %d|h = %d} ",TileType.c_str(),tileX,tileY, tileW, tileH);

			Set->TileTypes.insert(TileType);
			Set->TileSetMetaInformaton.insert(
				std::make_pair(TileType,
					createTile(tileX, tileY, tileW, tileH, index, intType)
				));
		}
	}
	else {
		//Error
	}

	
	SDL_Log("TilesetLoaded\n");
	return;
}

void renderSingleTile(TileSet* Set,const std::string& TileType, int x, int y) {

	Tile tmp = getTileFromTileset(Set, TileType);
	SDL_Rect DrawableArea = { 
		tmp.x ,tmp.y,
		tmp.TileWidth , tmp.TileHeight
	};

	render(&Set->Tilesheet,
		x,
		y,
		&DrawableArea, 0, NULL,
		SDL_FLIP_NONE);


}
//Create a COPY of an TILE
Tile getTileFromTileset(TileSet* Set, const std::string& type) {
	return Set->TileSetMetaInformaton[type];
}



void loadline(const std::string& line, int layer, int row, array3D& ar) {
	std::stringstream stream;

	int  type;
	stream << line;
	int i = 0;

	while (!stream.eof()) {
		stream >> type;
		ar[layer][row][i++] = type;
		if (stream.eof())
			break;
	}
}



/**
*/
TileMap LoadTileMap(GameObj* obj,const std::string& PathToMap) {

	std::fstream TextFile(PathToMap.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app); //<--read-only access
	std::stringstream textstream;
	std::string line;

	int col = 0;
	int rows = 0,currentrow=0;
	int layer = 0, currentLayer = 0;
	std::string tileset;

	TextFile >> tileset >> layer >> rows >> col;
	while (TextFile.get() != '\n'); //<-- Read till the end of line

	TileMap map(layer,rows,col); //<-- Initialize our 3D array
	map.columns = col;
	map.rows = rows;

	loadTileSet(tileset, &map.mCurrentTileset, obj->Renderer);



	if (TextFile.is_open()) { //<-- Start reading our *.map file

		
		while (std::getline(TextFile, line))  //<-- Read one line of Content till the end of File
		{
			if (line[0] != '-') //<-- if found a new layer is about to begin
			{
				if(currentrow < rows)
					loadline(line, currentLayer, currentrow++, map.mTileMap); //<-- is filling 1 row at time into our array
			}else {
				currentLayer++;
			}
			
		}
	}

	return map;

}