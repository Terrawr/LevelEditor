#pragma once
#include "LevelEditor.h"
#include <SDL.h>
#include <vector>
#include <queue>

struct GameState;
struct Command;
struct GameObj
{
	bool					 isRunning = false;
	int						 CurrentStateIndex;
	std::vector<GameState*>  Collection;
	std::queue<Command*>		 HolyCommands;

	int						Width, Height;
	int						MouseX, MouseY;

	SDL_Window*				Window;
	SDL_Renderer*			Renderer;
};


//Creates GameObject in Memory
GameObj* createGameObjectHandle();
void     initializeGameObj(GameObj*,char*Title,int width,int height);

void setActiveState(int index);

void registerState(GameObj* obj, GameState*);
void deleteState(GameObj*, GameState*);



