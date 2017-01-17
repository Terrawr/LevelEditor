//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "Tiles.h"
#include <string>
#include <fstream>

#include <iostream>



static int leftButtonMouse = 0;
static int rightButtonMouse = 0;

//Structs 


//Globals
static TileSet SetOfTiles;

//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CHANGESTATE(EditorOnEnterState) {
	SDL_Log(">>>>Editor OnEnter\n");

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	//You initialize a INTERNAL STATE like any other state
	

	SDL_Log(">>>>REGISTER INTERNAL STATE NOW\n");
	//But you have to register it by manually!!!
	

	SDL_Log(">>>>>Start loading Resources\n");
	//Load all Ressources here
	//
	loadTileSet("..\\resources\\demo_tiles.tilesheet", &SetOfTiles,obj->Renderer);

	SDL_Log(">>>>>>>>>>>>>>>>>>>>On Enter has finished\n");
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
	

	//SDL_Log("FrameTime[s]: %f | FrameTime[ms]: %f | FPS: %f \n", (elapsedTime_Lag/1000.f), (elapsedTime_Lag ), ( 1000.f / elapsedTime_Lag ));




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





	//SDL_RenderCopy(obj->Renderer, SetOfTiles.Tilesheet.mTexture, &tt, &tt);

	//You have to draw your INTERNALSTATE BEFORE you present you "normal" state
	//otherwise you will see nothing
		
	SDL_RenderPresent(obj->Renderer);

}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////




//CHANGESTATE(INTERNAL_OnEnterState) {
//	//You init the texture you want to use to render your internal
//	//state. If you would have decided that both your "normal" state
//	//and your INTERNAL-state share the same drawing context then you 
//	//would not need this!!!!!!!!! But only then.
//	initilizeTexture(&INTERNAL_GRAPHICCONTEXT, obj->Renderer);
//
//	//Because in this example you decided to use a seperat drawing context
//	//you create blank Texture with no content on it. You are responsible 
//	//for drawing this Texture!!!!
//	createBlank(&INTERNAL_GRAPHICCONTEXT, 300, 300, SDL_TEXTUREACCESS_TARGET);
//
//
//}
//CHANGESTATE(INTERNAL_OnExitState) {}
//CHANGESTATE(INTERNAL_OnPauseState) {}
//CHANGESTATE(INTERNAL_OnResumeState) {}
//
//TOPROCESS(INTERNAL_Update) {
//	SDL_Log(">>>>>>>>>>INTERNAL STATE RENDERFUNCTION CALL\n");
//	setAsRenderTarget(&INTERNAL_GRAPHICCONTEXT);
//	SDL_SetRenderDrawColor(obj->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderClear(obj->Renderer);
//
//	SDL_RenderPresent(obj->Renderer);
//	SDL_SetRenderTarget(obj->Renderer, NULL);
//	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
//
//}
//TOPROCESS(INTERNAL_Input) {}
//TOPROCESS(INTERNAL_Render) {}
