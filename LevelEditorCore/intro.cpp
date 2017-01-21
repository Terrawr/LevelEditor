//Includes
#include "GameState.h"
#include "GameObject.h"
#include "Texture.h"
#include <SDL_image.h>
#include "Texture.h"

#include <string>
#include <fstream>

#include "Command.h"

//////////////////////////////////////////////
static COMMAND_CALLBACK(CMD_EXIT); //!<-- Terminates the Game
static COMMAND_CALLBACK(CMD_TERMINATE_STATE); //!<-- Terminats this State

static COMMAND_CALLBACK(CMD_NEXT_STATE); //!<-- Moves this state to the next one. 
static COMMAND_CALLBACK(CMD_PREVIOUS_STATE); //!<-- Moves this state to the previous one. 

static COMMAND_CALLBACK(CMD_CURRENT_PAUSE);
static COMMAND_CALLBACK(CMD_CURRENT_RESUME);

static COMMAND_CALLBACK(CMD_RELOAD_MAP);
//////////////////////////////////////////////

#define FADE_SPEED 0.07f

static int leftButtonMouse = 0;
static int rightButtonMouse = 0;
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


	//TextureBanner = IMG_Load("..\\resources\\firstbanner.png");
	//Banner = SDL_CreateTextureFromSurface(obj->Renderer, TextureBanner);
	Banner_Rect.w = 0.4 * obj->Width;
	Banner_Rect.h = 0.4 * obj->Height;
	Banner_Rect.x = (obj->Width / 2) - (Banner_Rect.w / 2);
	Banner_Rect.y = (obj->Height / 2) - (Banner_Rect.h / 2);
	
	


	//TextureCopyright = IMG_Load("..\\resources\\copy.png");
	//Copyright = SDL_CreateTextureFromSurface(obj->Renderer, TextureCopyright);
	Copy_Rect.x = 0;
	Copy_Rect.y = 0.7 * obj->Height;
	Copy_Rect.w = obj->Width;
	Copy_Rect.h = 0.2 * obj->Height;
	
	/*initilizeTexture(&Fade, obj->Renderer);
	loadFromFile(&Fade, "..\\resources\\firstbanner.png");*/
	Fade.mWidth = Banner_Rect.w;
	Fade.mHeight = Banner_Rect.h;


	
}

///State destruction/////////////////
CHANGESTATE(IntroOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
	obj->Collection[obj->CurrentStateIndex]->isOnPause = true;
	printf("ONEXIT NOW---\n");
	/*SDL_DestroyTexture(Banner);
	SDL_DestroyTexture(Copyright);
	destroyTexture(&Fade);*/
	alpha = 0;
	alphaCalc = 0;
	TimeCount = 0;
	obj->CurrentStateIndex++;
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
	

		setAlpha(rm_getTexture(obj, "firstbanner"), alpha);

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
			registerCommand(obj, CMD_TERMINATE_STATE, TERMINATE_STATE);
			//IntroOnExitState(obj);
			
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

	render(rm_getTexture(obj,"firstbanner"), Banner_Rect.x*0.5f, Banner_Rect.y*0.5f, NULL, 0, 0, SDL_FLIP_NONE);
	render(rm_getTexture(obj, "copy"), Copy_Rect.x, Copy_Rect.y, NULL, 0, 0, SDL_FLIP_NONE);
	//L_RenderCopy(obj->Renderer, Copyright, NULL, &Copy_Rect);

	SDL_RenderPresent(obj->Renderer);
}



int MouseOverButton(GameObj* obj, SDL_Rect Button)
{
	//Testing if Mouse is over Button
	//Return 1 == true, Return 0 == false

	if (obj->MouseX >= Button.x && obj->MouseX <= (Button.x + Button.w) && obj->MouseY >= Button.y && obj->MouseY <= (Button.y + Button.h))
	{
		return 1;
	}
	else
		return 0;
}

COMMAND_CALLBACK(CMD_EXIT) {
	obj->isRunning = true;
}

COMMAND_CALLBACK(CMD_TERMINATE_STATE) {
	IntroOnExitState(obj);
}
