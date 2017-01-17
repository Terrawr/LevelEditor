//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "Tiles.h"
#include <string>
#include <fstream>


//INTERNAL STATES INCLUDES
#include "TileView.h"



static int leftButtonMouse = 0;
static int rightButtonMouse = 0;

//Structs 
GameState INTERNAL;



//Globals
static TileSet SetOfTiles;
static GameObj*   Root = NULL;
static GameState* This = NULL;

//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CHANGESTATE(EditorOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	Root = obj;
	This = obj->Collection[obj->CurrentStateIndex];

	initializeGameState(&INTERNAL, "INTERNAL", -1,
		TileView_OnEnter,
		TileView_OnExitState,
		TileView_OnPauseState,
		TileView_OnResumeState,
		TileView_Update,
		TileView_Render,
		TileView_Input
	);
	obj->Collection[obj->CurrentStateIndex]->InternalStates.push_back(&INTERNAL);
	
	This->INTERNALCURRENTINDEX++;

	//All InternalStates has to be initialised even if you do not use them
	for (auto states : obj->Collection[obj->CurrentStateIndex]->InternalStates) {
		SDL_Log("Initialize INTERNAL STATE\n");
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


	if (This->INTERNALCURRENTINDEX > -1)
	{
		if (!obj->Collection[obj->CurrentStateIndex]->InternalStates.empty())
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
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_BACKSPACE) {
				EditorOnExitState(obj);
			}
			if (e.key.keysym.sym == SDLK_c) {
				//WARNING JUST AN EXAMPLE. YOU CAN DO IT DIFFERENTLY
				if (This->InternalStates.empty())
				{
					This->InternalStates.push_back(&INTERNAL);
					This->INTERNALCURRENTINDEX++;
				}
					

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
		
		if(!This->InternalStates.empty() && This->INTERNALCURRENTINDEX > -1)
			if (This->InternalStates[This->INTERNALCURRENTINDEX]->EventHandler != NULL)
				This->InternalStates[This->INTERNALCURRENTINDEX]->EventHandler(&e);

	}
	
		if (This->INTERNALCURRENTINDEX > -1)
		{
			if (!This->InternalStates.empty())
			{
				This->InternalStates[This->INTERNALCURRENTINDEX]->Input(obj, elapsedTime_Lag);
			}
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
	
	if (This->INTERNALCURRENTINDEX > -1)
	{
		if (!This->InternalStates.empty())
			This->InternalStates[This->INTERNALCURRENTINDEX]->Render(obj, elapsedTime_Lag);
	}

	

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
