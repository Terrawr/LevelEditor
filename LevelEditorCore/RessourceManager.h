#pragma once
#include <map>
#include <vector>
#include <string>
#include "Texture.h"


#include <SDL.h>
#include <SDL_ttf.h>
struct GameObj;
struct RessourceManager {

	std::string RessourcePath;
	std::map<std::string, SDL_Surface*>  Surfaces;
	std::map<std::string, Texture*>		 Textures;
	std::map<std::string, TTF_Font*>     Fonts;
	//std::map<std::string, Mix_Music*>    Music;

};

void loadTexture(GameObj* obj, Texture* tex, const std::string& RessourceName);
Texture* getTexture(GameObj* obj, const std::string& ResourceName);