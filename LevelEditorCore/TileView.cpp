#include "LevelEditor.h"
#include "GameObject.h"
#include "GameState.h"
#include "Texture.h"

//CONSTANTS
constexpr	int TILEVIEW_WIDTH	= 700;
constexpr   int TILEVIEW_HEIGHT = 540;
//GLOBAL Private Data Member
static Texture DrawingContext;

static GameState* Root = NULL;
static GameState* This = NULL;

void EventHandler(SDL_Event* e) {
	SDL_Log("callback for Event handling is called NOW\n");
	if (e->type == SDL_QUIT || e->key.keysym.sym == SDLK_ESCAPE)
	{

	}
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.sym) {
		case SDLK_e:
			SDL_Log("Pop most current State\n");
			Root->InternalStates.pop_back();
			Root->INTERNALCURRENTINDEX--;
			break;
		}
	}
}

//INTERFACE-IMPLEMENTATION
CHANGESTATE(TileView_OnEnter) {

	SDL_Log(">>>>>>>>>INIT TileView\n");
	SDL_SetRenderDrawColor(obj->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	initilizeTexture(&DrawingContext, obj->Renderer);
	createBlank(&DrawingContext, TILEVIEW_WIDTH, TILEVIEW_HEIGHT, SDL_TEXTUREACCESS_TARGET);
	
	setBlendMode(&DrawingContext, SDL_BLENDMODE_BLEND);
	setAlpha(&DrawingContext, SDL_ALPHA_OPAQUE); //100% visible

	
	This = obj->Collection[obj->CurrentStateIndex]->InternalStates
		[
		   obj->Collection[obj->CurrentStateIndex]->INTERNALCURRENTINDEX
	    ];
	Root = obj->Collection[obj->CurrentStateIndex];

	//Explicitly overriding eventhandler
	This->EventHandler = EventHandler;
}
CHANGESTATE(TileView_OnExitState) {

	destroyTexture(&DrawingContext);
	Root = NULL;
	This = NULL;

}
CHANGESTATE(TileView_OnPauseState) {

}
CHANGESTATE(TileView_OnResumeState) {

}

TOPROCESS(TileView_Update) {

}
TOPROCESS(TileView_Input) {
	SDL_Log("---->%s: ProcessInput for InternalState", "TileView");
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;
		}
	}
}
TOPROCESS(TileView_Render) {
	SDL_Log(">>>INTERNAL RENDER CALL TO THE HELP\n");
	setAsRenderTarget(&DrawingContext);
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);
	///////////////////////////////////////////////////////////////////////////
	////////////////YOU START DRAWING OF YOUR INTERNAL STATE HERE//////////////






	///////////////////////////////////////////////////////////////////////////
	/////////////////////////DO NOT TOUCH OR I KILL YOU////////////////////////
	///////////////////////////////////////////////////////////////////////////
	SDL_SetRenderTarget(obj->Renderer, NULL);
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	render(&DrawingContext, 10, 10, NULL, 0, NULL, SDL_FLIP_NONE);
}