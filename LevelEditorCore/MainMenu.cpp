//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "SDL_image.h"
#include "Texture.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include "Command.h"

#include <string>
#include <fstream>

#define FONTSIZE 25 //is not the original font size, its how much ppx it has...


//Structs 


//Globals
static int leftButtonMouse = 0;
static int justOneTurn = 0;
static int rightButtonMouse = 0;
static int elapsedTime = 0;
static int elapsedTimeClick = 0;
static int chosenwindow = 0;
static int turnsToProcess = 0;
static int characterchoice = 0; //0-7

static int charactersizeh = 0;
static int charactersizew = 0;


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
static TTF_Font* MenuFont;
static SDL_Color MenuCol = { 255,255,255 };
static SDL_Surface* TextNewGame = NULL;
static SDL_Texture* TextureTextNewGame = nullptr;
static SDL_Surface* TextLoadGame = NULL;
static SDL_Texture* TextureTextLoadGame = nullptr;
static SDL_Surface* TextLevelEditor = NULL;
static SDL_Texture* TextureTextLevelEditor = nullptr;
static SDL_Surface* TextExit = NULL;
static SDL_Texture* TextureTextExit = nullptr;
static SDL_Texture* TextureTextCancel = nullptr;
static SDL_Surface* TextCancel = NULL;
static SDL_Texture* TextureTextCreate = nullptr;
static SDL_Surface* TextCreate = NULL;


static int MouseOnNewGame = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
static int MouseOnLoadGame = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
static int MouseOnLevelEditor = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
static int MouseOnExit = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
static int MouseOnCancel = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, CreateNewGameMenu Button
static int MouseOnCreate = 0; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, CreateNewGameMenu Button

static GameState NewGame; //<---- NewGame
CHANGESTATE(NewGameOnEnterState);
CHANGESTATE(NewGameOnExitState);
CHANGESTATE(NewGameOnPauseState);
CHANGESTATE(NewGameOnResumeState);

TOPROCESS(NewGameUpdate);
TOPROCESS(NewGameInput);
TOPROCESS(NewGameRender);

//Globals
void StateGoesUp(GameObj* obj, float deltatime) {
	obj->CurrentStateIndex++;
}

void StateGoesDown(GameObj* obj, float deltatime) {
	obj->CurrentStateIndex--;
}

//Background spec..
static SDL_Texture* TexNewGameBackground = nullptr;
static SDL_Surface* NewGameBackground = NULL;
static SDL_Rect NewGameBackground_Rect;

//Buttons...
static SDL_Rect Cancel_Rect;
static SDL_Rect Create_Rect;
static SDL_Rect Arrows_Rect[4]; //1 and 2 are dests on png, 3 and 4 are dests on screen... left->right

//others
static SDL_Rect CharacterFrame_Rect[4]; //0 is destination on png pic, 1 is with blue printings, 2 is dest on Screen
static SDL_Surface* CharacterFrame = NULL;
static SDL_Texture* TextureCharacterFrame = nullptr;
static SDL_Texture* TexGuy = nullptr;
static SDL_Surface* Guy = NULL;
static SDL_Rect Guy_Rect[8];

//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CHANGESTATE(MainMenuOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	//Load all Ressources here

	MenuFont = TTF_OpenFont("..\\resources\\test.ttf", FONTSIZE);
	if (!MenuFont)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		abort();
	}


	TextNewGame = TTF_RenderText_Solid(MenuFont, "    New Game    ", MenuCol);
	TextureTextNewGame = SDL_CreateTextureFromSurface(obj->Renderer, TextNewGame);
	TextLoadGame = TTF_RenderText_Solid(MenuFont, "    Load Game    ", MenuCol);
	TextureTextLoadGame = SDL_CreateTextureFromSurface(obj->Renderer, TextLoadGame);
	TextLevelEditor = TTF_RenderText_Solid(MenuFont, "    Level Editor    ", MenuCol);
	TextureTextLevelEditor = SDL_CreateTextureFromSurface(obj->Renderer, TextLevelEditor);
	TextExit = TTF_RenderText_Solid(MenuFont, "    Exit    ", MenuCol);
	TextureTextExit = SDL_CreateTextureFromSurface(obj->Renderer, TextExit);

	TextureBackground = IMG_Load("..\\resources\\background.png");
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
	Exit_Rect.y =/* 0.75555 */ 0.85 * obj->Height;

	initializeGameState(&NewGame, "NewGame", -1,
		NewGameOnEnterState,
		NewGameOnExitState,
		NewGameOnPauseState,
		NewGameOnResumeState,
		NewGameUpdate,
		NewGameRender,
		NewGameInput);
	
}

///State destruction/////////////////
CHANGESTATE(MainMenuOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
	obj->Collection[obj->CurrentStateIndex]->isOnPause = true;
	SDL_Log("----ON EXIT NOW----\n");
	if (MouseOverButton(obj, Exit_Rect) == 1)
	{
		registerCommand(obj, StateGoesDown, STATEDOWN);
	}
	if (MouseOverButton(obj, LevelEditor_Rect) == 1)
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
	SDL_Log("----UPDATE LOGIC NOW----\n");
	///should never be empty unless you plan to do nothing in your state!!!

	

	if (leftButtonMouse == 1)
	{
		elapsedTime += elapsedTime_Lag;
	}
	if (elapsedTime >= 200)
	{
		leftButtonMouse = 0;
		elapsedTime = 0;
	}

	if (chosenwindow == 0) {
		if (MouseOverButton(obj, CreateNewGame_Rect) == 1)
			MouseOnNewGame = 1;
		else
			MouseOnNewGame = 0;

		if (MouseOverButton(obj, LoadGame_Rect) == 1)
			MouseOnLoadGame = 1;
		else
			MouseOnLoadGame = 0;

		if (MouseOverButton(obj, LevelEditor_Rect) == 1)
			MouseOnLevelEditor = 1;
		else
			MouseOnLevelEditor = 0;

		if (MouseOverButton(obj, Exit_Rect) == 1)
			MouseOnExit = 1;
		else
			MouseOnExit = 0;
		if (MouseOnExit == 1 && leftButtonMouse == 1)
			obj->isRunning = true;
	}

	if (MouseOnNewGame == 1 && leftButtonMouse == 1)
	{
		chosenwindow = 1;
		MainMenuOnPauseState(obj);
	}

	if (chosenwindow == 1)
		{
			NewGameUpdate(obj, elapsedTime_Lag);
		}
	if (MouseOverButton(obj, LevelEditor_Rect) == 1 && leftButtonMouse == 1)
		MainMenuOnExitState(obj);
		
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
		

		SDL_GetMouseState(&obj->MouseX, &obj->MouseY);

	}
	//if(chosenwindow == 1)
	//	NewGameInput(obj, elapsedTime_Lag);

}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(MainMenuRender) {
	SDL_Log("----UPDATE DRAWING NOW----\n");
	SDL_RenderClear(obj->Renderer);

	//Render all Frames and Background
	SDL_RenderCopy(obj->Renderer, Background, NULL, &Background_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &Exit_Rect);

	//Render Fonts
	SDL_RenderCopy(obj->Renderer, TextureTextNewGame, NULL, &CreateNewGame_Rect);
	SDL_RenderCopy(obj->Renderer, TextureTextLoadGame, NULL, &LoadGame_Rect);
	SDL_RenderCopy(obj->Renderer, TextureTextLevelEditor, NULL, &LevelEditor_Rect);
	SDL_RenderCopy(obj->Renderer, TextureTextExit, NULL, &Exit_Rect);


	if (chosenwindow == 0) 
	{
		//Render all Frames for Chosen and Clicked
		if (MouseOnNewGame == 1)
		{
			if (leftButtonMouse == 1)
			{
				SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &CreateNewGame_Rect);
			}
			else
				SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &CreateNewGame_Rect);
		}
		if (MouseOnLoadGame == 1)
		{
			if (leftButtonMouse == 1)
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
	}
	if(chosenwindow == 1)
		NewGameRender(obj, elapsedTime_Lag);
	
	
	
	
	printf("%d %d %d %d", obj->MouseX, obj->MouseY, MouseOnNewGame, leftButtonMouse);

	if(chosenwindow == 0)
	SDL_RenderPresent(obj->Renderer);
	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////NEW GAME STATE //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



CHANGESTATE(NewGameOnEnterState)
{
	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	printf("%d", obj->CurrentStateIndex);
	//Background of new game state
	NewGameBackground = IMG_Load("..\\resources\\newgamebackground.png");
	TexNewGameBackground = SDL_CreateTextureFromSurface(obj->Renderer, NewGameBackground);
	NewGameBackground_Rect.w = 0.875 * obj->Width;
	NewGameBackground_Rect.h = 0.7777777 * obj->Height;
	NewGameBackground_Rect.x = (obj->Width / 2) - (NewGameBackground_Rect.w / 2);
	NewGameBackground_Rect.y = (obj->Height / 2) - (NewGameBackground_Rect.h / 2);

	//Cancel Button
	Cancel_Rect.w = 0.17 * NewGameBackground_Rect.w;
	Cancel_Rect.h = 0.1 * NewGameBackground_Rect.h;
	Cancel_Rect.x = (((NewGameBackground_Rect.w / 3) - Cancel_Rect.w / 2)) + NewGameBackground_Rect.x;
	Cancel_Rect.y = (NewGameBackground_Rect.h * 0.777777778) + NewGameBackground_Rect.y;

	//Create Button
	Create_Rect.w = 0.17 * NewGameBackground_Rect.w;
	Create_Rect.h = 0.1 * NewGameBackground_Rect.h;
	Create_Rect.x = ((NewGameBackground_Rect.w * 0.66666666666666666667) - (Create_Rect.w / 2)) + NewGameBackground_Rect.x;
	Create_Rect.y = (NewGameBackground_Rect.h * 0.777777778) + NewGameBackground_Rect.y;

	//Character Textures Surfaces and positions...

	//CharacterFrame 

	CharacterFrame_Rect[0].w = 70;
	CharacterFrame_Rect[0].h = 85;
	CharacterFrame_Rect[0].x = 450;
	CharacterFrame_Rect[0].y = 150;
	CharacterFrame_Rect[1].w = 70;
	CharacterFrame_Rect[1].h = 85;
	CharacterFrame_Rect[1].x = 450;
	CharacterFrame_Rect[1].y = 235;
	CharacterFrame_Rect[2].w = 0.125 * obj->Width;
	CharacterFrame_Rect[2].h = 0.3333333333 * obj->Height;
	CharacterFrame_Rect[2].x = ((NewGameBackground_Rect.w / 2) - (CharacterFrame_Rect[2].w / 2)) + NewGameBackground_Rect.x;
	CharacterFrame_Rect[2].y = ((NewGameBackground_Rect.h / 2) - (CharacterFrame_Rect[2].h / 2)) + NewGameBackground_Rect.y;
	CharacterFrame_Rect[3].w = 0.1 * obj->Width;
	CharacterFrame_Rect[3].h = 0.233333 * obj->Height;
	CharacterFrame_Rect[3].x = ((NewGameBackground_Rect.w / 2) - (CharacterFrame_Rect[3].w / 2)) + NewGameBackground_Rect.x;
	CharacterFrame_Rect[3].y = ((NewGameBackground_Rect.h / 2) - (CharacterFrame_Rect[3].h / 2)) + NewGameBackground_Rect.y;
	CharacterFrame = IMG_Load("..\\resources\\resources.png");
	TextureCharacterFrame = SDL_CreateTextureFromSurface(obj->Renderer, CharacterFrame);


	//Characters "Guy" ... destinations on the png!

	Guy_Rect[0].x = 65;
	Guy_Rect[0].y = 0;
	Guy_Rect[0].w = 62;
	Guy_Rect[0].h = 63;
	Guy_Rect[1].x = 258;
	Guy_Rect[1].y = 0;
	Guy_Rect[1].w = 62;
	Guy_Rect[1].h = 63;
	Guy_Rect[2].x = 447;
	Guy_Rect[2].y = 0;
	Guy_Rect[2].w = 62;
	Guy_Rect[2].h = 63;
	Guy_Rect[3].x = 641;
	Guy_Rect[3].y = 0;
	Guy_Rect[3].w = 62;
	Guy_Rect[3].h = 63;
	Guy_Rect[4].x = 65;
	Guy_Rect[4].y = 255;
	Guy_Rect[4].w = 62;
	Guy_Rect[4].h = 63;
	Guy_Rect[5].x = 257;
	Guy_Rect[5].y = 255;
	Guy_Rect[5].w = 62;
	Guy_Rect[5].h = 63;
	Guy_Rect[6].x = 447;
	Guy_Rect[6].y = 255;
	Guy_Rect[6].w = 62;
	Guy_Rect[6].h = 63;
	Guy_Rect[7].x = 641;
	Guy_Rect[7].y = 255;
	Guy_Rect[7].w = 62;
	Guy_Rect[7].h = 63;
	Guy = IMG_Load("..\\resources\\characters.png");
	TexGuy = SDL_CreateTextureFromSurface(obj->Renderer, Guy);

	TextCancel = TTF_RenderText_Solid(MenuFont, "    Cancel    ", MenuCol);
	TextureTextCancel = SDL_CreateTextureFromSurface(obj->Renderer, TextCancel);
	TextCreate = TTF_RenderText_Solid(MenuFont, "    Create    ", MenuCol);
	TextureTextCreate = SDL_CreateTextureFromSurface(obj->Renderer, TextCreate);

	//Arrows....
	Arrows_Rect[0].w = 30;
	Arrows_Rect[0].h = 90;
	Arrows_Rect[0].x = 970;
	Arrows_Rect[0].y = 0;
	Arrows_Rect[1].w = 30;
	Arrows_Rect[1].h = 90;
	Arrows_Rect[1].x = 940;
	Arrows_Rect[1].y = 0;

	Arrows_Rect[2].w = 0.01875 * obj->Width;
	Arrows_Rect[2].h = 0.1 * obj->Height;
	Arrows_Rect[2].x = (obj->Width / 2) - Arrows_Rect[2].w - (0.6 * CharacterFrame_Rect[2].w);
	Arrows_Rect[2].y = ((NewGameBackground_Rect.h / 2) - (CharacterFrame_Rect[2].h / 2)) + NewGameBackground_Rect.y + (CharacterFrame_Rect[2].h / 2) - (Arrows_Rect[2].h / 2);

	Arrows_Rect[3].w = 0.01875 * obj->Width;
	Arrows_Rect[3].h = 0.07 *obj->Height;
	Arrows_Rect[3].x = (obj->Width / 2) + (0.6 * CharacterFrame_Rect[2].w);
	Arrows_Rect[3].y = ((NewGameBackground_Rect.h / 2) - (CharacterFrame_Rect[2].h / 2)) + NewGameBackground_Rect.y + (CharacterFrame_Rect[2].h / 2) - (Arrows_Rect[2].h / 2);

}

CHANGESTATE(NewGameOnExitState) {
	SDL_Log("----ON EXIT NOW----\n");
	chosenwindow = 0;
}

CHANGESTATE(NewGameOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
	SDL_Log("----ON PAUSE NOW----\n");
}

///State unpausing///////////////
CHANGESTATE(NewGameOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
	SDL_Log("----ON RESUME NOW----\n");
}

TOPROCESS(NewGameUpdate) {
	SDL_Log("----UPDATE LOGIC NOW----\n");
	///should never be empty unless you plan to do nothing in your state!!!
	

	if (leftButtonMouse == 1)
	{
		elapsedTime += elapsedTime_Lag;
	}
	if (elapsedTime > 200)
	{
		leftButtonMouse = 0;
		elapsedTime = 0;
	}
	if (justOneTurn > 0)
	{
		elapsedTimeClick += elapsedTime_Lag;
	}
	if (elapsedTimeClick > 100)
	{
		justOneTurn = 0;
		elapsedTimeClick = 0;
	}



	if (MouseOverButton(obj, Cancel_Rect) == 1)
		MouseOnCancel = 1;
	else
		MouseOnCancel = 0;
	if (MouseOverButton(obj, Create_Rect) == 1)
		MouseOnCreate = 1;
	else
		MouseOnCreate = 0;

	if (MouseOverButton(obj, Arrows_Rect[2]) == 1 && leftButtonMouse == 1)
	{
		justOneTurn++;
		if(justOneTurn == 1)
		characterchoice--;
		leftButtonMouse = 0;
	}
	if (MouseOverButton(obj, Arrows_Rect[3]) == 1 && leftButtonMouse == 1)
	{
		justOneTurn++;
		if (justOneTurn == 1)
		characterchoice++;
		leftButtonMouse = 0;
	}
	if (characterchoice > 7)
		characterchoice = 0;
	if (characterchoice < 0)
		characterchoice = 7;

	

	//End NewGameState
	if ((MouseOverButton(obj, Cancel_Rect) == 1)&& leftButtonMouse == 1)
	{
		NewGameOnExitState(obj);
		MainMenuOnResumeState(obj);
	}

}

TOPROCESS(NewGameInput) {
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

TOPROCESS(NewGameRender) {
	SDL_Log("----UPDATE DRAWING NOW----\n");
	/*SDL_RenderClear(obj->Renderer);*/

	SDL_RenderCopy(obj->Renderer, TexNewGameBackground, NULL, &NewGameBackground_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &Cancel_Rect);
	SDL_RenderCopy(obj->Renderer, Frame, &Frame_Rect, &Create_Rect);
	SDL_RenderCopy(obj->Renderer, TextureCharacterFrame, &CharacterFrame_Rect[0], &CharacterFrame_Rect[2]);
	SDL_RenderCopy(obj->Renderer, TexGuy, &Guy_Rect[characterchoice], &CharacterFrame_Rect[3]);

	if (MouseOnCancel == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &Cancel_Rect);
		else
			SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &Cancel_Rect);
	}
	if (MouseOnCreate == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, FrameClicked, &FrameClicked_Rect, &Create_Rect);
		else
			SDL_RenderCopy(obj->Renderer, FrameChosen, &FrameChosen_Rect, &Create_Rect);
	}

	SDL_RenderCopy(obj->Renderer, TextureTextCancel, NULL, &Cancel_Rect);
	SDL_RenderCopy(obj->Renderer, TextureTextCreate, NULL, &Create_Rect);
	SDL_RenderCopy(obj->Renderer, TextureCharacterFrame, &Arrows_Rect[0], &Arrows_Rect[2]);
	SDL_RenderCopy(obj->Renderer, TextureCharacterFrame, &Arrows_Rect[1], &Arrows_Rect[3]);



	


	SDL_RenderPresent(obj->Renderer);
}