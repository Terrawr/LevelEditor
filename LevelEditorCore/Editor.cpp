//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"

#include <string>
#include <fstream>


static int leftButtonMouse = 1;
static int rightButtonMouse = 1;

//Structs 


//Globals
static Texture* OldTarget;
static Texture TileMapArea;;
static SDL_Rect ButtonPosition[128];



//Implementation
///State Initialization/////////////////
CHANGESTATE(EditorOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;

	initilizeTexture(&TileMapArea, obj->Renderer);
	if (createBlank(&TileMapArea, obj->Width - (obj->Width /100 * 45), obj->Height - (obj->Height / 100 * 20),SDL_TEXTUREACCESS_TARGET) == false) {
		printf("Try again :P\n");
	}

	//Load all Ressources here
	initilizeTexture( OldTarget, obj->Renderer);
	loadFromFile(OldTarget, "D:\\LevelEditor\\LevelEditor\\resources\\resources.png");
	loadTexture(obj, OldTarget, "AltesZiel");
	//
}

///State destruction/////////////////
CHANGESTATE(EditorOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
}

///State pausing/////////////////
CHANGESTATE(EditorOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}

///State unpausing/////////////////
CHANGESTATE(EditorOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
}




TOPROCESS(EditorUpdate) {

}

TOPROCESS(EditorInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;
		}
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				obj->isRunning = true;
			}
		//SDL_Mouse MotionAndButtons:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				leftButtonMouse = 1;
			}
			if (e.button.button == SDL_BUTTON_RIGHT)
			{
				rightButtonMouse = 1;
			}
			obj->MouseX = e.motion.x;
			obj->MouseY = e.motion.y;
		}

	}
}

TOPROCESS(EditorRender) {
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);

	render(getTexture(obj,"AltesZiel"), 20, obj->Height - TileMapArea.mHeight - 20, NULL , 0, NULL, SDL_FLIP_NONE);
	
	SDL_RenderPresent(obj->Renderer);
}