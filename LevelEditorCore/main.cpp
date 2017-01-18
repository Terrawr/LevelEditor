#include <stdlib.h>
#include <SDL.h>
#include <vector>
#include <chrono>

#include "GameState.h"
#include "GameObject.h"

#include "SplashScreen.h"
#include "Splashscreen2.h"
#include "EditorState.h"
#include "IntroScreen.h"
#include "mainmenu.h"


#include "Command.h"


//resources in folder updated

int gQuit = SDL_FALSE;

struct Command;

int main(int argc, char* argv[]) 
{
	GameObj*  Root = createGameObjectHandle();
	initializeGameObj(Root,"LevelEditor", 1440,786);

	Root->Assets.RessourcePath = "../resources/";

	//The Order of initilization is IMPORTANT. I changed it. First Screen, now your Menu and then some demo

	/*FIRST STATE*/
	GameState* IntroScreen = createGameState_ObjectInstance(Root); //<---- INTRO
	initializeGameState(IntroScreen, "IntroScreen", -1,
		IntroOnEnterState,
		IntroOnExitState,
		IntroOnPauseState,
		IntroOnResumeState,
		IntroUpdate,
		IntroRender,
		IntroInput);
	///SECOND STATE
	GameState* MainMenu = createGameState_ObjectInstance(Root); //<----- MENU
	initializeGameState(MainMenu, "MainMenu", -1,
		MainMenuOnEnterState,
		MainMenuOnExitState,
		MainMenuOnPauseState,
		MainMenuOnResumeState,
		MainMenuUpdate,
		MainMenuRender,
		MainMenuInput);
	/*THIRD STATE*/
	GameState* LevelEditor = createGameState_ObjectInstance(Root); //<---- APPLICATION or SOMETHING ELSE
	initializeGameState(LevelEditor, "LevelEditor", -1,
		EditorOnEnterState,
		EditorOnExitState,
		EditorOnPauseState,
		EditorOnResumeState,
		EditorUpdate,
		EditorRender,
		EditorInput);
	///FOURTH STATE
	///FIFTH STATE

	Root->CurrentStateIndex = 0;

	

	float lastFrameTime = 0;
	while (!Root->isRunning) {

		auto timePoint1(std::chrono::high_resolution_clock::now());
		//SDL_Log(".....CurrentState %d\n", Root->CurrentStateIndex); //<---- added this so you can see on your CONSOLE which state you are currently in. Thats the reason i remove fullscreen mode everytime you putt it back to see the console ;P 
		if(!Root->Collection.empty()){

			while (!Root->HolyCommands.empty()){
				Command* cmd = Root->HolyCommands.back();
				switch (cmd->Type)
				{
					case EXIT:
					{
						cmd->action(Root, 0.f);
						Root->HolyCommands.pop_back();
					}break;
					case STATEUP:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;
			
				}
			}

			if (!Root->Collection[Root->CurrentStateIndex]->isInitialized)
				Root->Collection[Root->CurrentStateIndex]->onEnter(Root);

			if (Root->Collection[Root->CurrentStateIndex]->isActive)
				Root->Collection[Root->CurrentStateIndex]->onResume(Root);

			if (Root->Collection[Root->CurrentStateIndex]->isOnPause)
				Root->Collection[Root->CurrentStateIndex]->onPause(Root);

			Root->Collection[Root->CurrentStateIndex]->Input(Root, lastFrameTime);
			Root->Collection[Root->CurrentStateIndex]->Update(Root, lastFrameTime);
			Root->Collection[Root->CurrentStateIndex]->Render(Root, lastFrameTime);

		} else {
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				{
					Root->isRunning = true;
				}
			}
		}



		auto timePoint2(std::chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);
		float ft{ std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(
			elapsedTime)
			.count() };
		lastFrameTime = ft;
	
	}


	return 0;
}