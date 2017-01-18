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
	std::map<std::string, std::unique_ptr<Texture>>		 Textures;
	std::map<std::string, TTF_Font*>     Fonts;
	std::map<std::string, std::string>					 Texts;
	//std::map<std::string, Mix_Music*>    Music;

	RessourceManager() :Textures(), Fonts(), Texts() {

	}

	~RessourceManager() = default;

};



void loadTextureFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);
void loadFontsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);
void loadTextsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName);

Texture*		getTexture(GameObj* obj, const std::string& ResourceName);
TTF_Font*		getFont(GameObj* obj, const std::string& ResourceName);
std::string&					getText(GameObj*obj, const std::string& ResourceName);