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


//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CHANGESTATE(IntroEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;


	//Load all Ressources here
	//
}

///State destruction/////////////////
CHANGESTATE(IntroOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
}

///State pausing/////////////////
CHANGESTATE(IntroOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}

///State unpausing/////////////////
CHANGESTATE(IntroOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
}



//HIER KOMMT DEINE GAMELOGIC REIN BZW DEINE USERINTERFACE LOGIC ODER WAS AUCH IMMER AN LOGIC
TOPROCESS(IntroUpdate) {
	

}

//HIER NIMMST DIE BENUTZTER EINGABE ENTGEGEN UND VERARBEITES SDL EVENTS
TOPROCESS(IntroInput) {
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

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(IntroRender) {
	SDL_RenderClear(obj->Renderer);
	
	//get on screen things and stuffy stuff

	SDL_RenderPresent(obj->Renderer);
}