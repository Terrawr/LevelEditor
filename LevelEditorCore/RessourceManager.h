#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Texture.h"


#include <SDL.h>
#include <SDL_ttf.h>
struct GameObj;
struct RessourceManager {

	std::string RessourcePath;

	std::string MapsPath;

	std::map<std::string, Texture*>		 Textures;
	std::map<std::string, TTF_Font*>     Fonts;
	std::map<std::string, std::string>					 Texts;
	std::map<std::string, SDL_Rect*> Boxes;
	//std::map<std::string, Mix_Music*>    Music;

	RessourceManager() :Textures(), Fonts(), Texts() {

	}

	~RessourceManager() = default;

};


void rm_storeBox(GameObj* obj,int x, int y, int w, int h, const std::string& Key);
void rm_storeString(GameObj* obj, const std::string& String, const std::string& Key);
void rm_storeTexture(GameObj* obj, Texture* tex, const std::string& Key);
void rm_storeFont(GameObj* obj, TTF_Font* font, const std::string& Key);

void rm_loadTextureFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);
void rm_loadFontsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);
void rm_loadTextsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);


SDL_Rect*		rm_getBox(GameObj* obj, const std::string& ResourceName);
Texture*		rm_getTexture(GameObj* obj, const std::string& ResourceName);
TTF_Font*		rm_getFont(GameObj* obj, const std::string& ResourceName);
std::string&	rm_getText(GameObj*obj, const std::string& ResourceName);