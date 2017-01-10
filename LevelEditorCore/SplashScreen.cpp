#include "GameState.h"
#include "GameObject.h"

TOPROCESS(SplashUpdate) {

}

TOPROCESS(SplashRender) {
	SDL_RenderClear(obj->Renderer);
	SDL_SetRenderDrawColor(obj->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(obj->Renderer);
}

TOPROCESS(SplashInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(-1);
	}
}




TOPROCESS(SplashUpdate2) {

}

TOPROCESS(SplashRender2) {
	SDL_RenderClear(obj->Renderer);
	SDL_SetRenderDrawColor(obj->Renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(obj->Renderer);
}

TOPROCESS(SplashInput2) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(-1);
	}
}