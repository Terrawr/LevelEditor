#include "GameObject.h"

//GameObj* createGameObjectHandle() {
//	GameObj* tmp = (GameObj*) malloc(sizeof(GameObj));
//	return tmp;  //c++ feature;
//}

GameObj* createGameObjectHandle() {
	return new GameObj;  //c++ feature;
}

void initializeGameObj(GameObj* obj, char*Title,int width, int height) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {

	}
	

	obj->Window = SDL_CreateWindow(Title, 20, 20, width, height, SDL_WINDOW_SHOWN);
	if (obj->Window == NULL);//Error

	obj->Renderer = SDL_CreateRenderer(obj->Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	obj->CurrentStateIndex = -1;
}

void registerState(GameObj* obj, GameState* state) {
	obj->Collection.push_back(state);
}
void deleteState(GameObj* obj, GameState* state) {
	
	obj->Collection.erase(
		std::find(
			std::begin(obj->Collection),
			std::end(obj->Collection),
			state));
}