//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"
#include "SDL_image.h"
#include "Texture.h"

#include <string>
#include <fstream>

#define FADE_SPEED 0.07f

static int leftButtonMouse = 1;
static int rightButtonMouse = 1;
static int alpha = 0;
static int alphaCalc = 0;
static int TimeCount = 0;

//Structs 


//Globals
static SDL_Texture* Banner = nullptr;
static SDL_Texture* Copyright = nullptr;
static SDL_Surface* TextureBanner = NULL;
static SDL_Surface* TextureCopyright = NULL;
static SDL_Rect Banner_Rect;
static SDL_Rect Copy_Rect;
static Texture Fade;




//Implementation
///State Initialization/////////////////
//Hier initialisierst du ALLE deine VARIABLEN
//NUR HIER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CHANGESTATE(IntroOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);


	//Load all Ressources here


	TextureBanner = IMG_Load("..\\resources\\firstbanner.png");
	Banner = SDL_CreateTextureFromSurface(obj->Renderer, TextureBanner);
	Banner_Rect.x = 480;
	Banner_Rect.y = 250;
	Banner_Rect.w = 640;
	Banner_Rect.h = 400;


	TextureCopyright = IMG_Load("..\\resources\\copy.png");
	Copyright = SDL_CreateTextureFromSurface(obj->Renderer, TextureCopyright);
	Copy_Rect.x = 350;
	Copy_Rect.y = 700;
	Copy_Rect.w = 900;
	Copy_Rect.h = 200;

	initilizeTexture(&Fade, obj->Renderer);
	loadFromFile(&Fade, "..\\resources\\firstbanner.png");


	
}

///State destruction/////////////////
CHANGESTATE(IntroOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
	obj->Collection[obj->CurrentStateIndex]->isOnPause = true;
	printf("ONEXIT NOW---\n");
	obj->CurrentStateIndex++;
	SDL_DestroyTexture(Banner);
	SDL_DestroyTexture(Copyright);
	destroyTexture(&Fade);
}

///State pausing/////////////////
CHANGESTATE(IntroOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}

///State unpausing/////////////////
CHANGESTATE(IntroOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
}



//HIER KOMMT DEINE GAMELOGIC REIN BZW DEINE USERINTERFACE LOGIC ODER WAS AUCH IMMER AN LOGIC
TOPROCESS(IntroUpdate) {
	

		setAlpha(&Fade, alpha);

		if (alpha < SDL_ALPHA_OPAQUE)
		{
			alphaCalc += FADE_SPEED * elapsedTime_Lag;
			alpha = alphaCalc;
		}

		if (alpha >= SDL_ALPHA_OPAQUE)
		{
			alpha = SDL_ALPHA_OPAQUE;
			alphaCalc = (float)SDL_ALPHA_OPAQUE;
		}
	
		TimeCount += elapsedTime_Lag;

		if (TimeCount > 4000)
		{

			if (alpha < SDL_ALPHA_OPAQUE)
			{
				alphaCalc -= FADE_SPEED * elapsedTime_Lag;
				alpha = alphaCalc;
			}

			if (alpha >= SDL_ALPHA_OPAQUE)
			{
				alpha = SDL_ALPHA_OPAQUE;
				alphaCalc = (float)SDL_ALPHA_OPAQUE;
			}
		}

}

//HIER NIMMST DIE BENUTZTER EINGABE ENTGEGEN UND VERARBEITES SDL EVENTS
TOPROCESS(IntroInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;
			
		}
		if (e.key.keysym.sym == SDLK_RETURN) {
			IntroOnExitState(obj);
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
TOPROCESS(IntroRender) {
	SDL_RenderClear(obj->Renderer);
	
	//get on screen things and stuffy stuff
	/*SDL_RenderCopy(obj->Renderer, Banner, NULL, &Banner_Rect);*/

	render(&Fade, Banner_Rect.x, Banner_Rect.y, NULL, 0, 0, SDL_FLIP_NONE);
	SDL_RenderCopy(obj->Renderer, Copyright, NULL, &Copy_Rect);

	SDL_RenderPresent(obj->Renderer);
}