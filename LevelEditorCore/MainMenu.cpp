//Includes
#include "GameState.h"
#include "GameObject.h"
#include "Texture.h"
#include <SDL_image.h>
#include "Texture.h"
#include <SDL_ttf.h>
#include <SDL.h>



#include <string>
#include <fstream>

#include "NewGame.h"
#include "mainmenu.h"

#define FONTSIZE 25 //is not the original font size, its how much ppx it has...
#define ON 1
#define OFF 0



//Globals
static GameObj*				Root = NULL;
static GameState*			This = NULL;

int leftButtonMouse = 0;
int justOneTurn = 0;
int rightButtonMouse = 0;
int elapsedTime = 0;
int elapsedTimeClick = 0;
int chosenwindow = 0;
int turnsToProcess = 0;
int characterchoice = 0; //0-7

int charactersizeh = 0;
int charactersizew = 0;


//static SDL_Texture* Background = nullptr;
//static SDL_Texture* Frame = nullptr;
//static SDL_Texture* FrameChosen = nullptr;
////static SDL_Texture* FrameClicked = nullptr;
//static SDL_Surface* TextureBackground = NULL;
//static SDL_Surface* TextureFrame = NULL;
//static SDL_Surface* TextureFrameChosen = NULL;
//static SDL_Surface* TextureFrameClicked = NULL;
 SDL_Rect Frame_Rect;
 SDL_Rect FrameChosen_Rect;
 SDL_Rect FrameClicked_Rect;
 SDL_Rect Background_Rect;
 SDL_Rect CreateNewGame_Rect;
 SDL_Rect LoadGame_Rect;
 SDL_Rect LevelEditor_Rect;
 SDL_Rect Exit_Rect;
 TTF_Font* MenuFont;
 SDL_Color MenuCol = { 255,255,255 };

 SDL_Surface* TextNewGame = nullptr;
//static SDL_Texture* TextureTextNewGame = nullptr;
 SDL_Surface* TextLoadGame = nullptr;
//static SDL_Texture* TextureTextLoadGame = nullptr;
 SDL_Surface* TextLevelEditor = nullptr;
//static SDL_Texture* TextureTextLevelEditor = nullptr;
 SDL_Surface* TextExit = nullptr;/*
static SDL_Texture* TextureTextExit = nullptr;
static SDL_Texture* TextureTextCancel = nullptr;*/
 SDL_Surface* TextCancel = nullptr;
//static SDL_Texture* TextureTextCreate = nullptr;
 SDL_Surface* TextCreate = nullptr;


 int MouseOnNewGame = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
 int MouseOnLoadGame = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
 int MouseOnLevelEditor = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
 int MouseOnExit = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
 int MouseOnCancel = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, CreateNewGameMenu Button
 int MouseOnCreate = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, CreateNewGameMenu Button

static GameState NewGame; //<---- NewGame


//Buttons...
static SDL_Rect Arrows_Rect[4]; //1 and 2 are dests on png, 3 and 4 are dests on screen... left->right
//others
static SDL_Rect CharacterFrame_Rect[4];//0 is destination on png pic, 1 is with blue printings, 2 is dest on Screen

//static SDL_Surface* CharacterFrame = nullptr;
//static SDL_Texture* TextureCharacterFrame = nullptr;
//static SDL_Texture* TexGuy = nullptr;
//static SDL_Surface* Guy = nullptr;


//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CHANGESTATE(MainMenuOnEnterState) {
	Root = obj;
	This = Root->Collection[Root->CurrentStateIndex];
	This->isInitialized = true;


	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	//Load all Ressources here

	MenuFont = TTF_OpenFont("..\\resources\\test.ttf", FONTSIZE);
	if (MenuFont == NULL)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		abort();
	}


	TextNewGame = TTF_RenderText_Solid(MenuFont, "    New Game    ", MenuCol);
	//TextureTextNewGame = SDL_CreateTextureFromSurface(obj->Renderer, TextNewGame);
	rm_storeTextureFromSurface(obj, TextNewGame, "text_newgame");

	TextLoadGame = TTF_RenderText_Solid(MenuFont, "    Load Game    ", MenuCol);
	//TextureTextLoadGame = SDL_CreateTextureFromSurface(obj->Renderer, TextLoadGame);
	rm_storeTextureFromSurface(obj, TextLoadGame, "text_loadgame");

	TextLevelEditor = TTF_RenderText_Solid(MenuFont, "    Level Editor    ", MenuCol);
	//TextureTextLevelEditor = SDL_CreateTextureFromSurface(obj->Renderer, TextLevelEditor);
	rm_storeTextureFromSurface(obj, TextLevelEditor, "text_leveleditor");

	TextExit = TTF_RenderText_Solid(MenuFont, "    Exit    ", MenuCol);
	//TextureTextExit = SDL_CreateTextureFromSurface(obj->Renderer, TextExit);
	rm_storeTextureFromSurface(obj, TextExit, "text_exit");

	//TextureBackground = IMG_Load("..\\resources\\background.png");
	//Background = SDL_CreateTextureFromSurface(obj->Renderer, TextureBackground);
	Background_Rect.x = 0;
	Background_Rect.y = 0;

	Background_Rect.w = obj->Width;
	Background_Rect.h = obj->Height;

	//TextureFrame = IMG_Load("..\\resources\\resources.png");
	//Frame = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	//FrameChosen = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);
	//FrameClicked = SDL_CreateTextureFromSurface(obj->Renderer, TextureFrame);

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
	Exit_Rect.y =/* 0.75555 */ 0.85 * obj->Height;

	//Because you are not utilizing the InternalGameState system you do not need to init a new gamestate
	//simply because you are not using a single internal state here!!!!
	/*initializeGameState(&NewGame, "NewGame", -1,
		NewGameOnEnterState,
		NewGameOnExitState,
		NewGameOnPauseState,
		NewGameOnResumeState,
		NewGameUpdate,
		NewGameRender,
		NewGameInput);
	*/
}

///State destruction/////////////////
CHANGESTATE(MainMenuOnExitState) {
	This->isInitialized = false;
	This->isActive = false;
	This->isOnPause = true;
	SDL_Log("----ON EXIT NOW----\n");

	/*SDL_DestroyTexture(Background);
	SDL_DestroyTexture(Frame);
	SDL_DestroyTexture(FrameChosen);
	SDL_DestroyTexture(FrameClicked);
	SDL_DestroyTexture(TextureCharacterFrame);
	SDL_DestroyTexture(TextureTextExit);
	SDL_DestroyTexture(TextureTextNewGame);
	SDL_DestroyTexture(TextureTextLoadGame);
	SDL_DestroyTexture(TextureTextLevelEditor);
	SDL_DestroyTexture(TexNewGameBackground);
	SDL_DestroyTexture(TexGuy);

	SDL_FreeSurface(Guy);
	SDL_FreeSurface(TextureBackground);
	SDL_FreeSurface(TextureFrame);
	SDL_FreeSurface(TextureFrameChosen);
	SDL_FreeSurface(TextureFrameClicked);
	SDL_FreeSurface(TextNewGame);
	SDL_FreeSurface(TextLoadGame);
	SDL_FreeSurface(TextLevelEditor);
	SDL_FreeSurface(TextExit);
	SDL_FreeSurface(TextCancel);
	SDL_FreeSurface(TextCreate);*/


	if (isMouseOverButton(obj, Exit_Rect) == 1)
	{
		registerCommand(obj, StateGoesDown, STATEDOWN);
	}
	if (isMouseOverButton(obj, LevelEditor_Rect) == 1)
	{
		registerCommand(obj, StateGoesUp, STATEUP);
	}
		

	
}

///State pausing/////////////////
CHANGESTATE(MainMenuOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = true;
	SDL_Log("----ON PAUSE NOW----\n");
	switch (chosenwindow)
	{
	case 1:
		if (turnsToProcess == 0)
		NewGameOnEnterState(obj);
		turnsToProcess++;
		break;
	case 0:
		//reset turnsToProcess
		turnsToProcess = 0;
		break;
	default:
		printf("wow...\n");
		break;
	}
}

///State unpausing/////////////////
CHANGESTATE(MainMenuOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
	SDL_Log("----ON RESUME NOW----\n");
}



//HIER KOMMT DEINE GAMELOGIC REIN BZW DEINE USERINTERFACE LOGIC ODER WAS AUCH IMMER AN LOGIC
TOPROCESS(MainMenuUpdate) {
	//SDL_Log("----UPDATE LOGIC NOW----\n");
	///should never be empty unless you plan to do nothing in your state!!!

	

	if (leftButtonMouse == 1)
	{
		elapsedTime += elapsedTime_Lag;
	}
	if (elapsedTime >= 100)
	{
		leftButtonMouse = 0;
		elapsedTime = 0;
	}

	//Choose which button should be highlighted or NOT
	//The solution works but 
	if (chosenwindow == 0) {
		//CheckButtonStates and apply change to the State of an Button
		changeButtonStateIf(obj, &CreateNewGame_Rect, &MouseOnNewGame);
		changeButtonStateIf(obj, &LoadGame_Rect, &MouseOnLoadGame);
		changeButtonStateIf(obj, &LevelEditor_Rect, &MouseOnLevelEditor);
		changeButtonStateIf(obj, &Exit_Rect, &MouseOnExit);
	}

	if (MouseOnExit == SDL_TRUE && leftButtonMouse == SDL_TRUE)
	{
		registerCommand(obj, CMD_EXIT, EXIT);
	}
	if (MouseOnNewGame == 1 && leftButtonMouse == 1)
	{
		chosenwindow = 1;
		registerCommand(Root, CMD_CURRENT_PAUSE, PAUSE_STATE);
		//MainMenuOnPauseState(obj);
	}
	if (chosenwindow == 1)
	{
		NewGameUpdate(obj, elapsedTime_Lag); //after thinking about should directly not be called here
	}
	if (isMouseOverButton(obj, LevelEditor_Rect) == 1 && leftButtonMouse == 1)
		//registerCommand(Root, CMD_TERMINATE_STATE, TERMINATE_STATE); //Cannot  add abstraction layer otherwise game brakes...
		MainMenuOnExitState(obj); 
		
}

//HIER NIMMST DIE BENUTZTER EINGABE ENTGEGEN UND VERARBEITES SDL EVENTS
TOPROCESS(MainMenuInput) {
	//SDL_Log("----UPDATE USERINPUT NOW----\n");
	
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;

		}
		if (e.key.keysym.sym == SDLK_1) {//<--- Changed from RETURN key to the NUMBER(1) key
			registerCommand(Root, CMD_TERMINATE_STATE, TERMINATE_STATE);
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
		

		SDL_GetMouseState(&obj->MouseX, &obj->MouseY);

	}
	//if(chosenwindow == 1)
	//	NewGameInput(obj, elapsedTime_Lag);

}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(MainMenuRender) {
	//SDL_Log("----UPDATE DRAWING NOW----\n");
	SDL_RenderClear(obj->Renderer);

	//Render all Frames and Background resources
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj,"background")->mTexture, NULL, &Background_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Frame_Rect, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Frame_Rect, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Frame_Rect, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Frame_Rect, &Exit_Rect);

	//Render Fonts
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj,"text_newgame")->mTexture, NULL, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "text_loadgame")->mTexture, NULL, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "text_leveleditor")->mTexture, NULL, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "text_exit")->mTexture, NULL, &Exit_Rect);


	if (chosenwindow == 0) 
	{
		//Render all Frames for Chosen and Clicked
		if (MouseOnNewGame == 1)
		{
			if (leftButtonMouse == 1)
			{
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameClicked_Rect, &CreateNewGame_Rect);
			}
			else
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameChosen_Rect, &CreateNewGame_Rect);
		}
		if (MouseOnLoadGame == 1)
		{
			if (leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameClicked_Rect, &LoadGame_Rect);
			else
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameChosen_Rect, &LoadGame_Rect);
		}
		if (MouseOnLevelEditor == 1)
		{
			if (leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameClicked_Rect, &LevelEditor_Rect);
			else
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameChosen_Rect, &LevelEditor_Rect);
		}
		if (MouseOnExit == 1)
		{
			if (leftButtonMouse == 1)
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameClicked_Rect, &Exit_Rect);
			else
				SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameChosen_Rect, &Exit_Rect);
		}
	}
	if(chosenwindow == 1)
		NewGameRender(obj, elapsedTime_Lag);
	
	
	
	
	//printf("%d %d %d %d", obj->MouseX, obj->MouseY, MouseOnNewGame, leftButtonMouse);

	if(chosenwindow == 0)
		SDL_RenderPresent(obj->Renderer);
	
}


void changeButtonStateIf(GameObj* obj, SDL_Rect* ButtonRect, int* state) {
	if (isMouseOverButton(obj, *ButtonRect) == 1)
		*state = 1;
	else
		*state = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Command Behaviour ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

COMMAND_CALLBACK(CMD_EXIT) {
	obj->isRunning = true;
}

COMMAND_CALLBACK(CMD_TERMINATE_STATE) {
	MainMenuOnExitState(obj);
}

COMMAND_CALLBACK(CMD_CURRENT_PAUSE) {
	MainMenuOnPauseState(obj);
}

void StateGoesUp(GameObj* obj, float deltatime) {
	obj->CurrentStateIndex++;
}

void StateGoesDown(GameObj* obj, float deltatime) {
	obj->CurrentStateIndex--;
}