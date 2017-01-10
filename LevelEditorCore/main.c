// "name" of that game? 
//any ideas?

#include <stdlib.h>
#include <SDL2\SDL.h>


int gQuit = SDL_FALSE;

int InititalizeGame(char* Title, int w, int h);
void processInput();
void UpdateWorld();
void DrawWorld();

int main(int argc, char* argv[]) {

	if (InititalizeGame("LevelEditor RPG", 800, 600)) {
		//Error
	}

	while (!gQuit) {
		void processInput();
		void UpdateWorld();
		void DrawWorld();
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