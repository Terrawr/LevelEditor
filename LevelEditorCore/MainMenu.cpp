//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"

#include "SDL_image.h"
#include <SDL_ttf.h>
#include "Texture.h"

#include <string>
#include <fstream>
#include "Texture.h"

//Structs 


//Globals
static int leftButtonMouse = 0;
static int rightButtonMouse = 0;
static int MouseX = 0;
static int MouseY = 0;

int countertime = 0;
static SDL_Texture* Background = nullptr;
static SDL_Texture* Frame = nullptr;
static SDL_Texture* FrameChosen = nullptr;
static SDL_Texture* FrameClicked = nullptr;
static SDL_Surface* TextureBackground = NULL;
static SDL_Surface* TextureFrame = NULL;
static SDL_Surface* TextureFrameChosen = NULL;
static SDL_Surface* TextureFrameClicked = NULL;
static SDL_Rect Frame_Rect;
static SDL_Rect FrameChosen_Rect;
static SDL_Rect FrameClicked_Rect;
static SDL_Rect Background_Rect;
static SDL_Rect CreateNewGame_Rect;
static SDL_Rect LoadGame_Rect;
static SDL_Rect LevelEditor_Rect;
static SDL_Rect Exit_Rect;

static Texture harald;
static TTF_Font* font;





//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CHANGESTATE(MainMenuOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	SDL_Color col = { 255,255,255,SDL_ALPHA_OPAQUE };
	//Load all Ressources here
	initilizeTexture(&harald, obj->Renderer);
	loadFromRenderedText(&harald, font, "Ich bin harald", col);


	TextureBackground = IMG_Load("..\\resources\\background.png");
	Background = SDL_CreateTextureFromSurface(obj->Renderer, TextureBackground);
	Background_Rect.x = 0;
	Background_Rect.y = 0;
	Background_Rect.w = 1600;
	Background_Rect.h = 900;

	TextureFrame = IMG_Load("...\\resources\\resources.png");
	Frame = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	FrameChosen = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	FrameClicked = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	Frame_Rect.x = 180;
	Frame_Rect.y = 150;
	Frame_Rect.w = 270;
	Frame_Rect.h = 90;
	FrameChosen_Rect.x = 180;
	FrameChosen_Rect.y = 240;
	FrameChosen_Rect.w = 270;
	FrameChosen_Rect.h = 90;
	FrameClicked_Rect.x = 180;
	FrameClicked_Rect.y = 330;
	FrameClicked_Rect.w = 270;
	FrameClicked_Rect.h = 90;

	CreateNewGame_Rect.x = 665;
	CreateNewGame_Rect.y = 380;
	CreateNewGame_Rect.w = 270;
	CreateNewGame_Rect.h = 90;

	LoadGame_Rect.x = 665;
	LoadGame_Rect.x = 480;
	LoadGame_Rect.w = 270;
	LoadGame_Rect.h = 90;

	LevelEditor_Rect.x = 665;
	LevelEditor_Rect.y = 580;
	LevelEditor_Rect.w = 270;
	LevelEditor_Rect.h = 90;

	Exit_Rect.x = 665;
	Exit_Rect.y = 680;
	Exit_Rect.w = 270;
	Exit_Rect.h = 90;



}

///State destruction/////////////////
CHANGESTATE(MainMenuOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
	obj->Collection[obj->CurrentStateIndex]->isOnPause = true;
	SDL_Log("----ON EXIT NOW----\n");

	obj->CurrentStateIndex--;

}

///State pausing/////////////////
CHANGESTATE(MainMenuOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
	SDL_Log("----ON PAUSE NOW----\n");
}

///State unpausing/////////////////
CHANGESTATE(MainMenuOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
	SDL_Log("----ON RESUME NOW----\n");
}



//HIER KOMMT DEINE GAMELOGIC REIN BZW DEINE USERINTERFACE LOGIC ODER WAS AUCH IMMER AN LOGIC
TOPROCESS(MainMenuUpdate) {
	SDL_Log("----UPDATE LOGIC NOW----\n");
	///should never be empty unless you plan to do nothing in your state!!!

	countertime += elapsedTime_Lag;

	if (countertime == 100) {
		countertime = 0;
	}


}

//HIER NIMMST DIE BENUTZTER EINGABE ENTGEGEN UND VERARBEITES SDL EVENTS
TOPROCESS(MainMenuInput) {
	SDL_Log("----UPDATE USERINPUT NOW----\n");
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;

		}
		if (e.key.keysym.sym == SDLK_1) {//<--- Changed from RETURN key to the NUMBER(1) key
			MainMenuOnExitState(obj);
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
		//Correct this. Apparently the version before were wrong. this 
		//Updates the X und Y Coordinate each Frame.
		SDL_GetMouseState(&obj->MouseX, &obj->MouseX);

	}

}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(MainMenuRender) {
	SDL_Log("----UPDATE DRAWING NOW----\n");
	SDL_RenderClear(obj->Renderer);

	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &Exit_Rect);
	
	render(&harald, 100, 100, NULL, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	SDL_RenderCopy(obj->Renderer, harald.mTexture, NULL, NULL);

	/// This seems to be part of the logic and shoud not be in the Render function.
	/// of course the SDL_RenderCopy call must remain here but the conditions when 
	/// to draw what should be known BEFORE you start rendering.
	if (MouseX >= CreateNewGame_Rect.x && MouseX <= (CreateNewGame_Rect.x + CreateNewGame_Rect.w))
	{
		if (MouseY >= CreateNewGame_Rect.y && MouseY <= (CreateNewGame_Rect.y + CreateNewGame_Rect.h))
		{
			if(leftButtonMouse == 0)
				SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &CreateNewGame_Rect);
			if(leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &CreateNewGame_Rect);
		}
		if (MouseY >= LoadGame_Rect.y && MouseY <= (LoadGame_Rect.y + LoadGame_Rect.h))
		{
			if(leftButtonMouse == 0)
				SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &LoadGame_Rect);
			if(leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &LoadGame_Rect);
		}
		if (MouseY >= LevelEditor_Rect.y && MouseY <= (LevelEditor_Rect.y + LevelEditor_Rect.h))
		{
			if(leftButtonMouse == 0)
				SDL_RenderCopy(obj->Renderer, FrameChosen, &LevelEditor_Rect, &LevelEditor_Rect);
			if (leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &LevelEditor_Rect);
		}
		if (MouseY >= Exit_Rect.y && MouseY <= (Exit_Rect.y + Exit_Rect.h))
		{
			if(leftButtonMouse == 0)
				SDL_RenderCopy(obj->Renderer, FrameChosen, &Exit_Rect, &Exit_Rect);
			if(leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &Exit_Rect);
		}

	}

	SDL_RenderPresent(obj->Renderer);
}