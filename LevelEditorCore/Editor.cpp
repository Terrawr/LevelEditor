//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "SDL_image.h"
#include "Texture.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <string>
#include <fstream>

//All for Input, Update and stuffy stuff
static int leftButtonMouse = 0;
static int rightButtonMouse = 0;

//all Surfaces

//all Textures


//allFonts


CHANGESTATE(EditorOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;

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



//HIER KOMMT DEINE GAMELOGIC REIN BZW DEINE USERINTERFACE LOGIC ODER WAS AUCH IMMER AN LOGIC
TOPROCESS(EditorUpdate) {
	

	SDL_Log("FrameTime[s]: %f | FrameTime[ms]: %f | FPS: %f \n", (elapsedTime_Lag/1000.f), (elapsedTime_Lag ), ( 1000.f / elapsedTime_Lag ));


	

	/*leftButtonMouse = 0;
	rightButtonMouse = 0;*/
}

//HIER NIMMST DIE BENUTZTER EINGABE ENTGEGEN UND VERARBEITES SDL EVENTS
TOPROCESS(EditorInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				leftButtonMouse = 1;
			}
			if (e.button.button == SDL_BUTTON_RIGHT)
			{
				rightButtonMouse = 1;
			}
		}
		if (e.type == SDL_KEYUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				leftButtonMouse = 0;
			}
			if (e.button.button == SDL_BUTTON_RIGHT)
			{
				rightButtonMouse = 0;
			}
		}
	}
		
	SDL_GetMouseState(&obj->MouseX, &obj->MouseX);
}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(EditorRender) {
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);
	


	SDL_RenderPresent(obj->Renderer);
}

//CHANGESTATE(INTERNALOnEnterState){
//
//	SDL_Log(">>>>>>>>>INIT TileView\n");
//	SDL_SetRenderDrawColor(obj->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//
//	initilizeTexture(&INTERNAL_DC, obj->Renderer);
//	createBlank(&INTERNAL_DC, obj->Width / 2 - 300, obj->Height / 2 - 300, SDL_TEXTUREACCESS_TARGET);
//
//	setBlendMode(&INTERNAL_DC, SDL_BLENDMODE_BLEND);
//	setAlpha(&INTERNAL_DC, SDL_ALPHA_OPAQUE/2); //50% visible
//
//}
//CHANGESTATE(INTERNALOnExitState){}
//CHANGESTATE(INTERNALOnPauseState){}
//CHANGESTATE(INTERNALOnResumeState){}
//
//TOPROCESS(INTERNALUpdate){ SDL_Log(">>>INTERNAL UPDATE CALL TO THE HELP\n"); }
//TOPROCESS(INTERNALInput){ SDL_Log(">>>INTERNAL INPUT CALL TO THE HELP\n"); }
//TOPROCESS(INTERNALRender) { 
//	
//	
//	SDL_Log(">>>INTERNAL RENDER CALL TO THE HELP\n");
//	setAsRenderTarget(&INTERNAL_DC);
//	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xaa, 0xff, SDL_ALPHA_OPAQUE);
//	SDL_RenderClear(obj->Renderer);
//	///////////////////////////////////////////////////////////////////////////
//	////////////////YOU START DRAWING OF YOUR INTERNAL STATE HERE//////////////
//
//	
//
//
//
//
//	///////////////////////////////////////////////////////////////////////////
//	/////////////////////////DO NOT TOUCH OR I KILL YOU////////////////////////
//	///////////////////////////////////////////////////////////////////////////
//	SDL_SetRenderTarget(obj->Renderer, NULL);
//	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
//	render(&INTERNAL_DC, 100, 100, NULL, 0, NULL, SDL_FLIP_NONE);
//
//
//
//};
