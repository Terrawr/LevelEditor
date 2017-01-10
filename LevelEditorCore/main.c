#include <stdlib.h>
#include <SDL2\SDL.h>

#include "MenuState.h"
#include "GameState.h"

int gQuit = SDL_FALSE;

int InititalizeGame(char* Title, int w, int h);
void processInput();
void UpdateWorld();
void DrawWorld();

int main(int argc, char* argv[]) {

	if (InititalizeGame("LevelEditor RPG", 800, 600)) {
		//Error
	}

	State States[4];

	States[0].Update = MenuUpdate;
	States[0].Render = MenuRender;
	States[0].Input = MenuInput;

	///...
	///States[1].Update = GameUpdate;
	///...
	///...
	///State[3].Update = IntroUpdate;

	while (!gQuit) {
	
		for (int i = 0; i < 4; i++)
		{
			States[i].Update();
			States[i].Input();
			States[i].Render();
		}
	}


	return 0;
}

int InititalizeGame(char* Title, int w, int h) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		//Error
		gQuit = SDL_TRUE;
		return SDL_FALSE;
	}
	return SDL_TRUE;
}

void processInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			gQuit = SDL_TRUE;
	}

}
void UpdateWorld() {

}
void DrawWorld() {

}