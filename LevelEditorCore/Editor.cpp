//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "SDL_image.h"
#include "Texture.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <string>
#include <fstream>

#define FONTSIZE 25

//All for Input, Update and stuffy stuff
static int leftButtonMouse = 0;
static int rightButtonMouse = 0;
static int MouseOverExitButton = 0;
static int MouseOverDeletButton = 0;
static int MouseOverCreateButton = 0;
static int MouseOverNPCButton = 0;
static int MouseOverQuestButton = 0;
static int ToolChosen = 2;
static int elapsedTime = 0;

//allRects
static SDL_Rect ExitToMainMenu_Rect; // JUST DEST ON SCREEN; TEXTURE IS TOOLBAR_RECT[12 and 13]
static SDL_Rect CreateOrLoad_Rect;
static SDL_Rect CreateNewMap_Rect;
static SDL_Rect LoadOldMap_Rect;
static SDL_Rect Background;
static TTF_Font* MenuFont;
static SDL_Color MenuCol = { 100,100,100 };

//ALL TEXTURES FOR TEXTS
static SDL_Texture* TextureTextExitToMainMenu = nullptr;
static SDL_Surface* TextExitToMainMenu = NULL;

//ALL SURFACES FOR TEXTS

/*0 delet, 1 create, 2 quest, 3 NPCS, 4/5 Arrows right/left ... ALL DESTINATIONS ON PIC!
6 del, 7 create, 8 quest, 9 NPC, 10 11 arrow right/left... ALL DESTINATIONS ON SCREEN!!!
12 frame on pic, 13 blue frame on pic*/
static SDL_Rect ToolBar_Rect[14];	




CHANGESTATE(EditorOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	loadTextureFromFile(obj, "resources.png", "Resources");
	loadTextureFromFile(obj, "NewGameBackGround.png", "WindowBackground");
	MenuFont = TTF_OpenFont("..\\resources\\test.ttf", FONTSIZE);
	if (!MenuFont)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		abort();
	}
	TextExitToMainMenu = TTF_RenderText_Solid( MenuFont, "   Exit to Main Menu   ", MenuCol);
	TextureTextExitToMainMenu = SDL_CreateTextureFromSurface(obj->Renderer, TextExitToMainMenu);
	
	ExitToMainMenu_Rect.w = 0.2 * obj->Width;
	ExitToMainMenu_Rect.h = 0.1 * obj->Height;
	ExitToMainMenu_Rect.x = 0.005 * obj->Width;
	ExitToMainMenu_Rect.y = 0.005 * obj->Height;


	if(1) //TOOLBAR RECT
	{
		ToolBar_Rect[0].w = 90;
		ToolBar_Rect[0].h = 90;
		ToolBar_Rect[0].x = 580;
		ToolBar_Rect[0].y = 0;
		ToolBar_Rect[1].w = 90;
		ToolBar_Rect[1].h = 90;
		ToolBar_Rect[1].x = 670;
		ToolBar_Rect[1].y = 0;
		ToolBar_Rect[2].w = 90;
		ToolBar_Rect[2].h = 90;
		ToolBar_Rect[2].x = 760;
		ToolBar_Rect[2].y = 0;
		ToolBar_Rect[3].w = 90;
		ToolBar_Rect[3].h = 90;
		ToolBar_Rect[3].x = 850;
		ToolBar_Rect[3].y = 0;
		ToolBar_Rect[4].w = 30;
		ToolBar_Rect[4].h = 90;
		ToolBar_Rect[4].x = 940;
		ToolBar_Rect[4].y = 0;
		ToolBar_Rect[5].w = 30;
		ToolBar_Rect[5].h = 90;
		ToolBar_Rect[5].x = 970;
		ToolBar_Rect[5].y = 0;
		ToolBar_Rect[6].w = 0.05625*obj->Width;
		ToolBar_Rect[6].h = 0.1*obj->Height;
		ToolBar_Rect[6].x = (obj->Width - 0.005 *obj->Width) - (ToolBar_Rect[6].w);
		ToolBar_Rect[6].y = (obj->Height - 0.005 *obj->Height) - (ToolBar_Rect[6].h);
		ToolBar_Rect[7].w = 0.05625*obj->Width;;
		ToolBar_Rect[7].h = 0.1*obj->Height;;
		ToolBar_Rect[7].x = (obj->Width - 0.005 *obj->Width) - (ToolBar_Rect[6].w);
		ToolBar_Rect[7].y = (obj->Height - 0.005 *obj->Height) - (ToolBar_Rect[6].h)*2 - (ToolBar_Rect[6].h / 2) *1;
		ToolBar_Rect[8].w = 0.05625*obj->Width;;
		ToolBar_Rect[8].h = 0.1*obj->Height;;
		ToolBar_Rect[8].x = (obj->Width - 0.005 *obj->Width) - (ToolBar_Rect[6].w);
		ToolBar_Rect[8].y = (obj->Height - 0.005 *obj->Height) - (ToolBar_Rect[6].h) * 3 - (ToolBar_Rect[6].h / 2)*2;
		ToolBar_Rect[9].w = 0.05625*obj->Width;;
		ToolBar_Rect[9].h = 0.1*obj->Height;;
		ToolBar_Rect[9].x = (obj->Width - 0.005 *obj->Width) - (ToolBar_Rect[6].w);
		ToolBar_Rect[9].y = (obj->Height - 0.005 *obj->Height) - (ToolBar_Rect[6].h) * 4 - (ToolBar_Rect[6].h / 2)*3;
	/*	ToolBar_Rect[10].w = ;
		ToolBar_Rect[10].h = ;
		ToolBar_Rect[10].x = ;
		ToolBar_Rect[10].y = ;
		ToolBar_Rect[11].w = ;
		ToolBar_Rect[11].h = ;
		ToolBar_Rect[11].x = ;
		ToolBar_Rect[11].y = ;*/
		ToolBar_Rect[12].w = 90;
		ToolBar_Rect[12].h = 90;
		ToolBar_Rect[12].x = 0;
		ToolBar_Rect[12].y = 30;
		ToolBar_Rect[13].w = 90;
		ToolBar_Rect[13].h = 90;
		ToolBar_Rect[13].x = 90;
		ToolBar_Rect[13].y = 30;
	}

	Background.h = obj->Height;
	Background.w = obj->Width;
	Background.x = 0;
	Background.y = 0;
}

///State destruction/////////////////
CHANGESTATE(EditorOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	obj->CurrentStateIndex--;

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

	if (MouseOverButton(obj, ExitToMainMenu_Rect) == 1)
	{
		MouseOverExitButton = 1;
		if (leftButtonMouse == 1)
		{
			EditorOnExitState(obj);
		}
	}
	else
	{
		MouseOverExitButton = 0;
	}

	if (MouseOverButton(obj, ToolBar_Rect[6]) == 1)
	{
		MouseOverDeletButton = 1;
		if (leftButtonMouse == 1)
		{
			ToolChosen = 1;
		}
	}
	else
	{
		MouseOverDeletButton = 0;
	}


	

	/*leftButtonMouse = 0;
	rightButtonMouse = 0;*/
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
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			leftButtonMouse = 1;
		}
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			rightButtonMouse = 1;
		}
		if (leftButtonMouse == 1)
		{
			elapsedTime += elapsedTime_Lag;
		}
		if (elapsedTime > 50)
		{
			elapsedTime = 0;
			leftButtonMouse = 0;
		}

	}
		
	SDL_GetMouseState(&obj->MouseX, &obj->MouseY);
}

//HIER ZEICHNEST DU NUR HIER!!!!!
TOPROCESS(EditorRender) {
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);

	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[12], &ExitToMainMenu_Rect);
	SDL_RenderCopy(obj->Renderer, TextureTextExitToMainMenu, NULL, &ExitToMainMenu_Rect);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[12], &ToolBar_Rect[6]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[0], &ToolBar_Rect[6]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[1], &ToolBar_Rect[7]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[2], &ToolBar_Rect[8]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[3], &ToolBar_Rect[9]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[12], &ToolBar_Rect[7]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[12], &ToolBar_Rect[8]);
	SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[12], &ToolBar_Rect[9]);

	if (MouseOverExitButton == 1)
		SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[13], &ExitToMainMenu_Rect);

	if (MouseOverDeletButton == 1)
		SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[13], &ToolBar_Rect[6]);

	switch (ToolChosen)
	{
	case 1: //del
		{
		SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[13], &ToolBar_Rect[6]);
		break;
		}
	case 2:
		{
		SDL_RenderCopy(obj->Renderer, getTexture(obj, "Resources")->mTexture, &ToolBar_Rect[13], &ToolBar_Rect[7]);
		break;
		}
	}
	

	SDL_RenderPresent(obj->Renderer);
}
