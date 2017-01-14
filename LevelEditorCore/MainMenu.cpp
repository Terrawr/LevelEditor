//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "SDL_image.h"
#include "Texture.h"

#include <string>
#include <fstream>


//Structs 


//Globals
static int leftButtonMouse = 0;
static int rightButtonMouse = 0;
static int MouseX = 0;
static int MouseY = 0;

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







//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CHANGESTATE(MainMenuOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	//Load all Ressources here


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
	printf("ONEXIT NOW---\n");
	obj->CurrentStateIndex++;

}

///State pausing/////////////////
CHANGESTATE(MainMenuOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}

///State unpausing/////////////////
CHANGESTATE(MainMenuOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
}



//HIER KOMMT DEINE GAMELOGIC REIN BZW DEINE USERINTERFACE LOGIC ODER WAS AUCH IMMER AN LOGIC
TOPROCESS(MainMenuUpdate) {




}

//HIER NIMMST DIE BENUTZTER EINGABE ENTGEGEN UND VERARBEITES SDL EVENTS
TOPROCESS(MainMenuInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;

		}
		if (e.key.keysym.sym == SDLK_1) {
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
		obj->MouseX = e.motion.x;
		obj->MouseY = e.motion.y;

	}

}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(MainMenuRender) {
	SDL_RenderClear(obj->Renderer);

	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &Exit_Rect);

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