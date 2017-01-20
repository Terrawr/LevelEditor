#include "RessourceManager.h"
#include "GameObject.h"

#include <fstream>
#include <sstream>

#include "SDL_ttf.h"
#include <SDL_ttf.h>




void rm_loadTextureFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName) {

	Texture* t = (Texture*) malloc(sizeof(Texture));
	auto path = obj->Assets.RessourcePath + FilePath;
	initilizeTexture(t, obj->Renderer);
	loadFromFile(t, (char*)path.c_str());

	if (t == NULL)
		abort();
	
	obj->Assets.Textures.insert(std::make_pair(RessourceName, t));

}
void rm_loadFontsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName) {
	TTF_Font* t = NULL;
	auto path = obj->Assets.RessourcePath + FilePath;
	t = TTF_OpenFont(path.c_str(), 16);
	if (t == NULL) {

	}
	
	obj->Assets.Fonts.insert(std::make_pair(RessourceName, t));
}
void rm_loadTextsFromFile(GameObj* obj, const std::string& FilePath, const std::string& RessourceName) {

	auto path = obj->Assets.RessourcePath + FilePath;
	std::string line;

	std::fstream TextFile(path.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app); //<--read-only access
	std::stringstream textstream;

	if (TextFile.is_open()) {

		while (std::getline(TextFile, line))  //<-- Read one line of Content till the end of File
		{
			textstream << line;
		}
	}

	obj->Assets.Texts.insert(std::make_pair(RessourceName, textstream.str()));
}

Texture*		rm_getTexture(GameObj* obj, const std::string& ResourceName) {


	return obj->Assets.Textures[ResourceName];

}
TTF_Font*		rm_getFonts(GameObj* obj, const std::string& ResourceName) {

	return obj->Assets.Fonts[ResourceName];

}
std::string&    rm_getText(GameObj*obj, const std::string& ResourceName) {

	return obj->Assets.Texts[ResourceName];
}


void rm_storeString(GameObj* obj, const std::string& String, const std::string& Key) {
	obj->Assets.Texts.insert(
		std::make_pair(Key, String)
	);
}