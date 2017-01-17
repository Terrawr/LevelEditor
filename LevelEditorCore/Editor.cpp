//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "Tiles.h"
#include <string>
#include <fstream>



static int leftButtonMouse = 0;
static int rightButtonMouse = 0;

//Structs 
static int INTERNALCURRENTINDEX = -1;
static Texture INTERNAL_DC;
GameState INTERNAL;
CHANGESTATE(INTERNALOnEnterState);
CHANGESTATE(INTERNALOnExitState);
CHANGESTATE(INTERNALOnPauseState);
CHANGESTATE(INTERNALOnResumeState);

TOPROCESS(INTERNALUpdate);
TOPROCESS(INTERNALInput);
TOPROCESS(INTERNALRender);



//Globals
static TileSet SetOfTiles;

//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CHANGESTATE(EditorOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;

	initializeGameState(&INTERNAL, "INTERNAL", -1,
		INTERNALOnEnterState,
		INTERNALOnExitState,
		INTERNALOnPauseState,
		INTERNALOnResumeState,
		INTERNALUpdate,
		INTERNALRender,
		INTERNALInput
	);
	obj->Collection[obj->CurrentStateIndex]->InternalStates.push_back(&INTERNAL);

	//All InternalStates has to be initialised even if you do not use them
	for (auto states : obj->Collection[obj->CurrentStateIndex]->InternalStates) {
		states->onEnter(obj);
	}
	
	//Load all Ressources here
	//
	loadTileSet("..\\resources\\demo_tiles.tilesheet", &SetOfTiles,obj->Renderer);
}

///State destruction/////////////////
CHANGESTATE(EditorOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	//Every InternalState has to be destroyed.
	for (auto states : obj->Collection[obj->CurrentStateIndex]->InternalStates) {
		states->onExit(obj);
	}

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


	if (INTERNALCURRENTINDEX > -1)
	{
		obj->Collection[obj->CurrentStateIndex]->Input(obj,elapsedTime_Lag);
	}

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
		if (e.key.keysym.sym == SDLK_BACKSPACE) {
			EditorOnExitState(obj);
			SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
			while (SDL_PollEvent(&e));
		}
		if (e.key.keysym.sym == SDLK_c) {
			if (INTERNALCURRENTINDEX == -1)
			{
				INTERNALCURRENTINDEX = 0;
			}
			else {
				INTERNALCURRENTINDEX = -1;
			}
			SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
			while (SDL_PollEvent(&e));
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
		

	}
	
	if (INTERNALCURRENTINDEX > -1)
	{
		obj->Collection[obj->CurrentStateIndex]->InternalStates[INTERNALCURRENTINDEX]->Input(obj, elapsedTime_Lag);
	}
	SDL_GetMouseState(&obj->MouseX, &obj->MouseX);
}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(EditorRender) {

	/////////////////////////START DRAWING ON TEXTURE////////////////////////////
	//setAsRenderTarget(&TileMapArea);

	////SDL_SetRenderDrawColor(obj->Renderer, 0xFF, 0xFF, 0xFF,SDL_ALPHA_OPAQUE);
	//SDL_RenderClear(obj->Renderer);
	//SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xaa, 0xff, SDL_ALPHA_OPAQUE);
 //  
	//SDL_RenderFillRect(obj->Renderer, &rect);


	//////////////////////START DRAWING ON WINDOW/////////////////////////////
	//SDL_SetRenderTarget(obj->Renderer, NULL);
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);
	
	auto t = getTile(&SetOfTiles, "grass");

	SDL_Rect  tt = { t.x,t.y, t.TileWidth , t.TileHeight };

	//SDL_Log("Tile w = %d | Tile h = %d", tt.w, tt.h);

	render(&SetOfTiles.Tilesheet,
		100, 
		100 , 
		&tt , 0, NULL,
		SDL_FLIP_NONE);





	//SDL_RenderCopy(obj->Renderer, SetOfTiles.Tilesheet.Texture, &tt, &tt);
	
	if (INTERNALCURRENTINDEX > -1)
	{
		obj->Collection[obj->CurrentStateIndex]->InternalStates[INTERNALCURRENTINDEX]->Render(obj, elapsedTime_Lag);
	}

	

	SDL_RenderPresent(obj->Renderer);
}

CHANGESTATE(INTERNALOnEnterState){

	SDL_Log(">>>>>>>>>INIT Internal State\n");
	initilizeTexture(&INTERNAL_DC,obj->Renderer);
	SDL_SetRenderDrawColor(obj->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	createBlank(&INTERNAL_DC, 300, 300, SDL_TEXTUREACCESS_TARGET);
	setBlendMode(&INTERNAL_DC, SDL_BLENDMODE_BLEND);
	setAlpha(&INTERNAL_DC, SDL_ALPHA_OPAQUE / 4);

}
CHANGESTATE(INTERNALOnExitState){}
CHANGESTATE(INTERNALOnPauseState){}
CHANGESTATE(INTERNALOnResumeState){}

TOPROCESS(INTERNALUpdate){ SDL_Log(">>>INTERNAL UPDATE CALL TO THE HELP\n"); }
TOPROCESS(INTERNALInput){ SDL_Log(">>>INTERNAL INPUT CALL TO THE HELP\n"); }
TOPROCESS(INTERNALRender) { 
	
	
	SDL_Log(">>>INTERNAL RENDER CALL TO THE HELP\n");
	setAsRenderTarget(&INTERNAL_DC);
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xaa, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);
	///////////////////////////////////////////////////////////////////////////
	////////////////YOU START DRAWING OF YOUR INTERNAL STATE HERE//////////////

	




	///////////////////////////////////////////////////////////////////////////
	/////////////////////////DO NOT TOUCH OR I KILL YOU////////////////////////
	///////////////////////////////////////////////////////////////////////////
	SDL_SetRenderTarget(obj->Renderer, NULL);
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	render(&INTERNAL_DC, 100, 100, NULL, 0, NULL, SDL_FLIP_NONE);



};
