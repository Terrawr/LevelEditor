//Includes
#include "GameState.h"
#include "GameObject.h"
#include "UserInterface.h"
#include "Texture.h"

#include <string>
#include <fstream>


static int leftButtonMouse = 1;
static int rightButtonMouse = 1;

//Structs 


//Globals
static Texture* OldTarget;
static Texture TileMapArea;;
static SDL_Rect ButtonPosition[128];
static SDL_Rect rect,rect2;

static int dy = 100, dx = 100, dy2 = 100, dx2 = 100, speedx = 1, speedy = 1, speed2x = 1, speed2y = 1;
static int directx, directy;

//Implementation
///State Initialization/////////////////
CHANGESTATE(EditorOnEnterState) {

	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;

	initilizeTexture(&TileMapArea, obj->Renderer);
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	if (createBlank(&TileMapArea, 
		obj->Width - (obj->Width /100 * 50),
		obj->Height - (obj->Height / 100 * 50),
		SDL_TEXTUREACCESS_TARGET) == false) {
		printf("Try again :P\n");
	}
	rect = { 0,0,50,50 };
	rect2 = rect;
	//Load all Ressources here
	//
}

///State destruction/////////////////
CHANGESTATE(EditorOnExitState) {
	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
}

///State pausing/////////////////
CHANGESTATE(EditorOnPauseState) {
	obj->Collection[obj->CurrentStateIndex]->isActive = false;
}

///State unpausing/////////////////
CHANGESTATE(EditorOnResumeState) {
	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
}




TOPROCESS(EditorUpdate) {
	rect.x += (dx * 0.016) * speedx;
	rect.y += (dy * 0.016) * speedy;
	rect2.x += (dx2 * 0.018) * speed2x;
	rect2.y += (dy2 * 0.018) * speed2y;



	/* collide with edges of screen */
	if (rect.x < 0) {
		rect.x = 0;
		speedx = -speedx;
		dx += speedx;
	}
	else if (rect.x > TileMapArea.mWidth - rect.w) {
		rect.x = TileMapArea.mWidth - rect.w;
		speedx = -speedx;
	}
	if (rect.y < 0) {
		rect.y = 0;
		speedy = -speedy;
		dy += speedy;
	}
	else if (rect.y > TileMapArea.mHeight - rect.h) {
		rect.y = TileMapArea.mHeight - rect.h;
		speedy = -speedy;
	}
;

	/* collide with edges of screen */
	if (rect2.x < 0) {
		rect2.x = 0;
		speed2x = -speed2x;
		dx2 += speed2x;
	}
	else if (rect2.x > obj->Width - TileMapArea.mWidth) {
		rect2.x = obj->Width - TileMapArea.mWidth;
		speed2x = -speed2x;
			
	}
	if (rect2.y < 0) {
		rect2.y = 0;
		speed2y = -speed2y;
		dy2 += speed2y;
	}
	else if (rect2.y > obj->Height - TileMapArea.mHeight) {
		rect2.y = obj->Height - TileMapArea.mHeight;
		speed2y = -speed2y;
	}

}

TOPROCESS(EditorInput) {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		{
			obj->isRunning = true;
		}
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				obj->isRunning = true;
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

}

TOPROCESS(EditorRender) {

	///////////////////////START DRAWING ON TEXTURE////////////////////////////
	setAsRenderTarget(&TileMapArea);

	//SDL_SetRenderDrawColor(obj->Renderer, 0xFF, 0xFF, 0xFF,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(obj->Renderer);
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xaa, 0xff, SDL_ALPHA_OPAQUE);
   
	SDL_RenderFillRect(obj->Renderer, &rect);


	//////////////////////START DRAWING ON WINDOW/////////////////////////////
	SDL_SetRenderTarget(obj->Renderer, NULL);
	SDL_RenderClear(obj->Renderer);
	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);

	render(&TileMapArea,
		rect2.x, 
		rect2.y , 
		NULL , 0, NULL,
		SDL_FLIP_NONE);
	
	SDL_RenderPresent(obj->Renderer);
}