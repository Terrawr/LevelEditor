#include "GameObject.h"
#include "GameState.h"

#include "mainmenu.h"

//Globals
static SDL_Rect NewGameBackground_Rect;
static SDL_Rect Cancel_Rect;
static SDL_Rect Create_Rect;
//Buttons...
static SDL_Rect Arrows_Rect[4]; 
//1 and 2 are dests on png, 3 and 4 are dests on screen... left->right

//others
static SDL_Rect CharacterFrame_Rect[4];
static SDL_Rect Guy_Rect[8];

void initValues(GameObj* obj) {
	printf("%d", obj->CurrentStateIndex);
	////Background of new game state
	//NewGameBackground = IMG_Load("..\\resources\\newgamebackground.png");
	//TexNewGameBackground = SDL_CreateTextureFromSurface(obj->Renderer, NewGameBackground);
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

	//You do not need to load an image you already have loaded once before!!!!
	//CharacterFrame = IMG_Load("..\\resources\\resources.png");
	//TextureCharacterFrame = SDL_CreateTextureFromSurface(obj->Renderer, CharacterFrame);


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
	Guy_Rect[7].h = 63;/*
					   Guy = IMG_Load("..\\resources\\characters.png");
					   TexGuy = SDL_CreateTextureFromSurface(obj->Renderer, Guy);*/

	TextCancel = TTF_RenderText_Solid(MenuFont, "    Cancel    ", MenuCol);
	//TextureTextCancel = SDL_CreateTextureFromSurface(obj->Renderer, TextCancel);
	rm_storeTextureFromSurface(obj, TextCancel, "text_cancel");

	TextCreate = TTF_RenderText_Solid(MenuFont, "    Create    ", MenuCol);
	//TextureTextCreate = SDL_CreateTextureFromSurface(obj->Renderer, TextCreate);
	rm_storeTextureFromSurface(obj, TextCreate, "text_create");

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

CHANGESTATE(NewGameOnEnterState)
{
	obj->Collection[obj->CurrentStateIndex]->isInitialized = true;
	SDL_SetRenderDrawColor(obj->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	initValues(obj);
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


	//
	changeButtonStateIf(obj, &Create_Rect, &MouseOnCancel);
	changeButtonStateIf(obj, &Create_Rect, &MouseOnCreate);


	if (MouseOverButton(obj, Arrows_Rect[2]) == 1 && leftButtonMouse == 1)
	{
		justOneTurn++;
		if (justOneTurn == 1)
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
	if ((MouseOverButton(obj, Cancel_Rect) == 1) && leftButtonMouse == 1)
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

			registerCommand(obj, CMD_TERMINATE_STATE, TERMINATE_STATE);
			//MainMenuOnExitState(obj);
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

	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "newgame_background")->mTexture, NULL, &NewGameBackground_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Frame_Rect, &Cancel_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Frame_Rect, &Create_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &CharacterFrame_Rect[0], &CharacterFrame_Rect[2]);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "characters")->mTexture, &Guy_Rect[characterchoice], &CharacterFrame_Rect[3]);

	if (MouseOnCancel == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameClicked_Rect, &Cancel_Rect);
		else
			SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameChosen_Rect, &Cancel_Rect);
	}
	if (MouseOnCreate == 1)
	{
		if (leftButtonMouse == 1)
			SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameClicked_Rect, &Create_Rect);
		else
			SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &FrameChosen_Rect, &Create_Rect);
	}

	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, NULL, &Cancel_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, NULL, &Create_Rect);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Arrows_Rect[0], &Arrows_Rect[2]);
	SDL_RenderCopy(obj->Renderer, rm_getTexture(obj, "resources")->mTexture, &Arrows_Rect[1], &Arrows_Rect[3]);






	SDL_RenderPresent(obj->Renderer);
}
