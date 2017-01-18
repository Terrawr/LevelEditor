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

	std::map<std::string, Texture*>		 Textures;
	std::map<std::string, TTF_Font*>     Fonts;
	std::map<std::string, std::string>					 Texts;
	std::map<std::string, SDL_Rect*> Boxes;
	//std::map<std::string, Mix_Music*>    Music;

	RessourceManager() :Textures(), Fonts(), Texts() {

	}

	~RessourceManager() = default;

};


void createBoxForRM(int x, int y, int w, int h, const std::string& NAme);

void loadTextureFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);
void loadFontsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);
void loadTextsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);


SDL_Rect*		getBox(GameObj* obj, const std::string& ResourceName);
Texture*		getTexture(GameObj* obj, const std::string& ResourceName);
TTF_Font*		getFont(GameObj* obj, const std::string& ResourceName);
std::string&	getText(GameObj*obj, const std::string& ResourceName);