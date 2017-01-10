#pragma once
#include "LevelEditor.h"
#include <SDL2\SDL.h>
#include <vector>


struct GameState;
struct GameObj
{
	int						 CurrentStateIndex;
	std::vector<GameState*>  Collection;

	SDL_Window*				Window;
	SDL_Renderer*			Renderer;
	
};


//Creates GameObject in Memory
GameObj* createGameObjectHandle();
void     initializeGameObj(GameObj*,char*Title,int width,int height);

void setActiveState(int index);

void registerState(GameObj*, GameState*);
void deleteState(GameObj*, GameState*);



