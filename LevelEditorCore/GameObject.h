#pragma once
#include "LevelEditor.h"
#include <SDL.h>
#include <vector>
#include <queue>
#include "RessourceManager.h"



struct GameState;
struct Command;
struct RessourceManager;
struct GameObj
{
	bool					 isRunning = false;
	int						 CurrentStateIndex;
	std::vector<GameState*>  Collection;
	std::vector<Command*>	 HolyCommands;

	RessourceManager		Assets;


	int						Width, Height;
	int						MouseX, MouseY;

	SDL_Window*				Window;
	SDL_Renderer*			Renderer;

	
};


//Creates GameObject in Memory
GameObj* createGameObjectHandle();
void     initializeGameObj(GameObj*,char*Title,int width,int height);

void setActiveState(int index);





