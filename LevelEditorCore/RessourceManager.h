#pragma once
#include <map>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

struct RessourceManager {

	std::string RessourcePath;
	std::map<std::string, SDL_Surface*>  Surfaces;
	std::map<std::string, SDL_Texture*>  Textures;
	std::map<std::string, TTF_Font*>     Fonts;
	//std::map<std::string, Mix_Music*>    Music;

};