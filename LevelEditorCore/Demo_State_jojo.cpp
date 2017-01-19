#include "GameState.h"
#include "GameObject.h"
#include "RessourceManager.h"
#include "Command.h"

#include "Tiles.h"


////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Command Callbacks////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
COMMAND_CALLBACK(CMD_EXIT); //!<-- Terminates the Game
COMMAND_CALLBACK(CMD_TERMINATE_STATE); //!<-- Terminats this State

COMMAND_CALLBACK(CMD_NEXT_STATE); //!<-- Moves this state to the next one. 
COMMAND_CALLBACK(CMD_PREVIOUS_STATE); //!<-- Moves this state to the previous one. 

COMMAND_CALLBACK(CMD_CURRENT_PAUSE);
COMMAND_CALLBACK(CMD_CURRENT_RESUME);

COMMAND_CALLBACK(CMD_RELOAD_MAP);

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Self-Defined Structs//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Private Global Variables//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
GameObj*		Root			= NULL;
GameState*		This			= NULL;

TileMap			ExampleMap;
TileSet*		ExampeTileset	= NULL;

std::vector<Tile> Renderables;



CHANGESTATE(Demo_OnEnterState)
{
	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	//Init ModulGlobals
	Root = obj;
	This = Root->Collection[Root->CurrentStateIndex];

	ExampleMap = te_LoadTileMap(obj, obj->Assets.RessourcePath+rm_getText(obj,"Mapfile"));
	Renderables = te_createRenderableTiles(obj, &ExampleMap);
}
CHANGESTATE(Demo_OnExitState){
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	//destroy Modul Globals
	Root = NULL;
	This = NULL;
}
CHANGESTATE(Demo_OnPauseState){
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}
CHANGESTATE(Demo_OnResumeState){
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
}

TOPROCESS(Demo_Update){}
TOPROCESS(Demo_Input){
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			registerCommand(obj, CMD_EXIT, EXIT);
		}
		///////////////////////////////////////////////////////////
		///////////////////Keyboard////////////////////////////////
		//////////////////////////////////////////////////////////
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym) {
			case SDLK_r:
				registerCommand(obj,CMD_RELOAD_MAP, UNKOWN);
			}
		}
		if (e.type == SDL_KEYUP)
		{
			
		}
		//////////////////////////////////////////////////////////
		////////////////////Mouse/////////////////////////////////
		//////////////////////////////////////////////////////////
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{

		}
		if (e.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&obj->MouseX, &obj->MouseX);
		}
	}

	
}
TOPROCESS(Demo_Render){

	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);

	//SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, NULL, NULL);

	

	for (auto tile : Renderables) {
		re_renderSingleTile(&ExampleMap.mCurrentTileset,
							te_translateTypeInformation(&ExampleMap.mCurrentTileset,tile.TileType),
							tile.x,tile.y);
		SDL_Log("Tilelayerindex: %d | TileType[%d,%s]\n", tile.LayerIndex,tile.TileType, te_translateTypeInformation(&ExampleMap.mCurrentTileset, tile.TileType).c_str());
	}


	/*re_renderSingleTile(&ExampleMap.mCurrentTileset, "lava", 300, 300);
	render(&ExampleMap.mCurrentTileset.Tilesheet, 100, 100, NULL, 45, NULL, SDL_FLIP_NONE);*/

	SDL_RenderPresent(obj->Renderer);

}







/////////////////////IMPLEMENTATIONS OF CALLBACKS HERE///////////////////////////////
COMMAND_CALLBACK(CMD_EXIT) {
	obj->isRunning = true;
}

COMMAND_CALLBACK(CMD_TERMINATE_STATE) {
	Demo_OnExitState(obj);
}


COMMAND_CALLBACK(CMD_RELOAD_MAP) {
	ExampleMap = te_LoadTileMap(obj, obj->Assets.RessourcePath + rm_getText(obj, "Mapfile"));
	Renderables = te_createRenderableTiles(obj, &ExampleMap);
}