//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "SDL_image.h"
#include "Texture.h"

#include <string>
#include <fstream>

#define msToWait 50


//Structs 


//Globals
static int leftButtonMouse = 0;
static int rightButtonMouse = 0;
static int elapsedTime = 0;

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

static int MouseOnNewGame = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile
static int MouseOnLoadGame = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile
static int MouseOnLevelEditor = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile
static int MouseOnExit = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile








//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CHANGESTATE(MainMenuOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	//Load all Ressources here


	/*TextureBackground = IMG_Load("..\\resources\\background.png");*/
	Background = SDL_CreateTextureFromSurface(obj->Renderer, TextureBackground);
	Background_Rect.x = 0;
	Background_Rect.y = 0;
	Background_Rect.w = obj->Width;
	Background_Rect.h = obj->Height;

	TextureFrame = IMG_Load("..\\resources\\resources.png");
	Frame = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	FrameChosen = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	FrameClicked = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);

	//Adresses on res.png
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

	//Tileadresses on window
	CreateNewGame_Rect.w = 0.16875 * obj->Width;
	CreateNewGame_Rect.h = 0.1 * obj->Height;
	CreateNewGame_Rect.x = 0.415625 * obj->Width;
	CreateNewGame_Rect.y = 0.42222222* obj->Height;

	
	LoadGame_Rect.w = 0.16875 * obj->Width;
	LoadGame_Rect.h = 0.1 * obj->Height;
	LoadGame_Rect.x = 0.415625 * obj->Width;
	LoadGame_Rect.y = 0.5333 * obj->Height;

	
	LevelEditor_Rect.w = 0.16875 * obj->Width;
	LevelEditor_Rect.h = 0.1 * obj->Height;
	LevelEditor_Rect.x = 0.415625 * obj->Width;
	LevelEditor_Rect.y = 0.64444 * obj->Height;

	
	Exit_Rect.w = 0.16875 * obj->Width;
	Exit_Rect.h = 0.1 * obj->Height;
	Exit_Rect.x = 0.415625 * obj->Width;
	Exit_Rect.y = 0.75555 * obj->Height;


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
	
	if (leftButtonMouse == 1)
	{
		elapsedTime += elapsedTime_Lag;
	}
	if (elapsedTime >= 300)
	{
		leftButtonMouse = 0;
		elapsedTime = 0;
	}

	if (obj->MouseX >= CreateNewGame_Rect.x && obj->MouseX <= (CreateNewGame_Rect.x + CreateNewGame_Rect.w) && obj->MouseY >= CreateNewGame_Rect.y && obj->MouseY <= (CreateNewGame_Rect.y + CreateNewGame_Rect.h))
		MouseOnNewGame = 1;
	else
		MouseOnNewGame = 0;

	if (obj->MouseX >= LoadGame_Rect.x && obj->MouseX <= (LoadGame_Rect.x + LoadGame_Rect.w) && obj->MouseY >= LoadGame_Rect.y && obj->MouseY <= (LoadGame_Rect.y + LoadGame_Rect.h))
		MouseOnLoadGame = 1;
	else
		MouseOnLoadGame = 0;

	if (obj->MouseX >= LevelEditor_Rect.x && obj->MouseX <= (LevelEditor_Rect.x + LevelEditor_Rect.w) && obj->MouseY >= LevelEditor_Rect.y && obj->MouseY <= (LevelEditor_Rect.y + LevelEditor_Rect.h))
		MouseOnLevelEditor = 1;
	else
		MouseOnLevelEditor = 0;

	if (obj->MouseX >= Exit_Rect.x && obj->MouseX <= (Exit_Rect.x + Exit_Rect.w) && obj->MouseY >= Exit_Rect.y && obj->MouseY <= (Exit_Rect.y + Exit_Rect.h))
		MouseOnExit = 1;
	else
		MouseOnExit = 0;


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
		SDL_GetMouseState(&obj->MouseX, &obj->MouseY);

	}

}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(MainMenuRender) {
	SDL_Log("----UPDATE DRAWING NOW----\n");
	SDL_RenderClear(obj->Renderer);

	SDL_RenderCopy(obj->Renderer, Background, NULL, &Background_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &Exit_Rect);

	if (MouseOnNewGame == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &CreateNewGame_Rect);
		else
			SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &CreateNewGame_Rect);
	}
	if (MouseOnLoadGame == 1)
	{
		if(leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &LoadGame_Rect);
		else
			SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &LoadGame_Rect);
	}
	if (MouseOnLevelEditor == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &LevelEditor_Rect);
		else
			SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &LevelEditor_Rect);
	}
	if (MouseOnExit == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &Exit_Rect);
		else
			SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &Exit_Rect);
	}
	
	printf("%d %d %d %d", obj->MouseX, obj->MouseY, MouseOnNewGame, leftButtonMouse);


	SDL_RenderPresent(obj->Renderer);
}