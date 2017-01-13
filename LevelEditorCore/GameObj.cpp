#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

static int screenwidth = 800;
static int screenheight = 480;

//GameObj* createGameObjectHandle() {
//	GameObj* tmp = (GameObj*) malloc(sizeof(GameObj));
//	return tmp;  //c++ feature;
//}

GameObj* createGameObjectHandle() {
	return new GameObj;  //c++ feature;
}

void getScreenResolution()
{
	int i;

	SDL_DisplayMode currentscreen;


	// Get current display mode of all displays.
	for (i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

		int should_be_zero = SDL_GetCurrentDisplayMode(i, &currentscreen);

		if (should_be_zero != 0)
			// In case of error...
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

		else
			// On success, print the current display mode.
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, currentscreen.w, currentscreen.h, currentscreen.refresh_rate);

		screenheight = currentscreen.h/2;
		screenwidth = currentscreen.w/2;
	}
}

void initializeGameObj(GameObj* obj, char*Title,int width, int height) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		//error
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error in File: %s on Line: %d. Build Time and Date: %s %s", __FILE__, __LINE__, __DATE__, __TIME__);
	}
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) ){
		//error
	}
	if (TTF_Init() == -1) {
		//error
	}

	getScreenResolution();

	obj->Window = SDL_CreateWindow(Title, 110, 110, screenwidth, screenheight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	if (obj->Window == NULL){
		//Error
	}

	obj->Renderer = SDL_CreateRenderer(obj->Window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
	if (obj->Renderer == NULL) {
		//error
	}

	obj->CurrentStateIndex = -1;
	obj->Width = screenwidth;
	obj->Height = screenheight;
}

