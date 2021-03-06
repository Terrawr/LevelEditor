#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDL_opengl.h"
#include <Windows.h>
#include <SDL_messagebox.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
#include <conio.h>
#include <direct.h>

#include "guisan.hpp"
#include "guisan\sdl.hpp"

static int screenwidth = 800;
static int screenheight = 480;

//
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

		//for fullscreen with 1 display
		/*screenheight = currentscreen.h;
		screenwidth = currentscreen.w;*/
		
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
	/*obj->Height =  screenheight;
	obj->Width =  screenwidth;*/
	obj->Width = 1000;
	obj->Height = 800;

	obj->Window = SDL_CreateWindow(Title, 50, 50, obj->Width, obj->Height, SDL_WINDOW_SHOWN| SDL_WINDOW_OPENGL);
	if (obj->Window == NULL){
		//Error
	}

	obj->Renderer = SDL_CreateRenderer(obj->Window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
	if (obj->Renderer == NULL) {
		//error
	}

	obj->CurrentStateIndex = -1;
	obj->lastFrameTime = 0.0f;


	///////////////////////////////////
	obj->UserInterface = new gcn::Gui();
	obj->imageLoader = new gcn::SDLImageLoader();
	obj->graphics = new gcn::SDLGraphics();
	obj->input = new gcn::SDLInput();
	
	// The ImageLoader in use is static and must be set to be
	// able to load images
	
	obj->UserInterface_Display = SDL_CreateRGBSurface(0, obj->Width, obj->Height, 24, 255, 0, 255, 255);
	
	if (obj->UserInterface_Display != NULL)
		obj->graphics->setTarget(obj->UserInterface_Display);
	else
	{
		
		fprintf(stderr, "Error: %s", SDL_GetError());
		abort();
	}
	obj->UserInterface_TextureDisplay = SDL_CreateTextureFromSurface(obj->Renderer, obj->UserInterface_Display);


	obj->UserInterface->setGraphics(obj->graphics);
	obj->UserInterface->setInput(obj->input);
	gcn::Image::setImageLoader(obj->imageLoader);
	// Load the image font.
	obj->font = new gcn::ImageFont("fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.");
	gcn::Widget::setGlobalFont(obj->font);
}



/// General function implementations going here please!!!
bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void changeButtonStateIf(GameObj* obj, SDL_Rect* ButtonRect, int* state) {
	if (isMouseOverButton(obj, *ButtonRect) == 1)
		*state = 1;
	else
		*state = 0;
}




