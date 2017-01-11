//Includes
#include "GameState.h"
#include "GameObject.h"
#include <string>


//Globals


//Implementation
///State Initialization/////////////////
CHANGESTATE(EditorOnEnterState) {

}

///State destruction/////////////////
CHANGESTATE(EditorOnExitState) {

}

///State pausing/////////////////
CHANGESTATE(EditorOnPauseState) {

}

///State unpausing/////////////////
CHANGESTATE(EditorOnResumeState) {

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
	}

}

TOPROCESS(EditorRender) {

}