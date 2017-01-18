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

Tile te_createTile(int x, int y, int w, int h, int index, int type) {
	Tile tmp;
	tmp.LayerIndex = index;
	tmp.TileHeight = h;
	tmp.TileWidth = w;
	tmp.x = x;
	tmp.y = y;
	tmp.TileType = type;

	return tmp;
}

void te_loadTileSet(const std::string& location,TileSet* Set,SDL_Renderer* renderer)
{
	std::fstream tileset(location.c_str(),std::ios_base::in|std::ios_base::out); //<--read-only access
	
	if (tileset.is_open()) {
		///Read the Header
		std::string line;
		std::getline(tileset, line); //!<-- reads the location of the image containing the tiles

		initilizeTexture(&Set->Tilesheet, renderer);
		loadFromFile(&Set->Tilesheet, (char*)line.c_str()); //!<-- loads the image found in path(line)
		line.clear();

		while (std::getline(tileset, line))  //<-- Read one line of Content till the end of File
		{
			std::istringstream iss(line);
			int tileX, tileY; //<-- Position on the Tilesheet
			int tileW, tileH; //<-- Outlines of the actuall Tile
			int index, intType;
			std::string TileType; //<-- Type of the tile


			if (!(iss >> TileType >> intType >> index >>tileX >> tileY >> tileW >> tileH)) {//<-- Read values of an line or quit loop if error occured
				SDL_Log("FileEnd"); continue;; //<-- skip if line is corrupted
			} 

			iss >> TileType;
			iss >> intType;
			if (TileType == "NONE")
				continue;

			SDL_Log("Tile(%s) \t[%d|%d] \t{w = %d|h = %d} ",TileType.c_str(),tileX,tileY, tileW, tileH);

			//Stores Stringkey to IntegerKey. Basically a translationtable
			Set->TileTypes.insert(
				std::make_pair(TileType,intType)
			);

			Set->TileSetMetaInformaton.insert(
				std::make_pair(intType,
					te_createTile(tileX, tileY, tileW, tileH, index, intType)
				));
		}
	}
	else {
		//Error
	}

	
	SDL_Log("TilesetLoaded\n");
	return;
}

void re_renderSingleTile(TileSet* Set,const std::string& TileType, int x, int y) {

	Tile tmp = te_getTileFromTileset(Set, TileType);
	SDL_Rect DrawableArea = { 
		tmp.x ,tmp.y,
		tmp.TileWidth , tmp.TileHeight
	};

	render(&Set->Tilesheet,x,y,&DrawableArea, 0, NULL,SDL_FLIP_NONE);
	if (tmp.LayerIndex > 0) {
		SDL_Log("Render Layer: %d", tmp.LayerIndex);
	}


}


std::string te_translateTypeInformation(TileSet* Set,int type) {
	std::map<std::string, int>::const_iterator
		
		key = std::find_if(

		Set->TileTypes.begin(), Set->TileTypes.end(),
		[&](auto t) {
		return (t.second == type);
		}
	);
	if(key != Set->TileTypes.end())
		return key->first;
	return "";

}
//Create a COPY of an TILE
Tile te_getTileFromTileset(TileSet* Set, const std::string& type) {
	return Set->TileSetMetaInformaton[Set->TileTypes[type]];
}
Tile te_getTileFromTileset(TileSet* Set, int type) {
	return Set->TileSetMetaInformaton[type];
}


//PRIVATE FUNCTION
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
TileMap te_LoadTileMap(GameObj* obj,const std::string& PathToMap) {

	SDL_Log("--->Is Loading a TileMap: %s", PathToMap.c_str());
	std::fstream TextFile(PathToMap.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app); //<--read-only access
	std::stringstream textstream;
	std::string line;

	int col = 0;
	int rows = 0,currentrow=0;
	int layer = 0, currentLayer = 0;
	std::string tileset;
	TileMap *map = NULL;;

	if (TextFile.is_open()) { //<-- Start reading our *.map file

		TextFile >> tileset >> layer >> rows >> col; //<-- read  max values for layer, rows and columns
		while (TextFile.get() != '\n'); //<-- Read till the end of line

		map = new TileMap(layer, rows, col); //<-- Initialize our 3D array
		map->columns = col;
		map->rows = rows;

		te_loadTileSet(tileset, &map->mCurrentTileset, obj->Renderer);
		
		while (std::getline(TextFile, line))  //<-- Read one line of Content till the end of File
		{
			if (line[0] != '-') //<-- if found a new layer is about to begin
			{
				if(currentrow < rows )
					loadline(line, currentLayer, currentrow++, map->mTileMap); //<-- is filling 1 row at time into our array
			}else {
				currentLayer++;
				currentrow = 0;
				if (currentLayer == layer)
					break;
			}
			
		}
	}

	return *map;

}


std::vector<Tile>	te_createRenderableTiles(GameObj* obj, TileMap* mapdata) {

	std::vector<Tile> TemporaryCopy;

	for (unsigned layer = 0; layer < mapdata->mTileMap.size(); layer++) {
		for (unsigned row = 0; row < mapdata->mTileMap[layer].size(); row++) {
			for (unsigned col = 0; col < mapdata->mTileMap[layer][row].size(); col++) {

				SDL_Log("==========> Create Tiles for Layer: %d", layer);
				int type = mapdata->mTileMap[layer][row][col] ;
				int width = mapdata->mCurrentTileset.TileSetMetaInformaton[type].TileWidth;
				int height = mapdata->mCurrentTileset.TileSetMetaInformaton[type].TileHeight;
				
				if(type != 4)
					TemporaryCopy.push_back(
						te_createTile(width*col, height*row, width, height, layer, type)
					);
			}
		}
	}


	//std::sort(std::begin(TemporaryCopy), std::end(TemporaryCopy), [&](Tile a, Tile b) { return a.LayerIndex < b.LayerIndex; });

	return TemporaryCopy;//Copys the copy
}
