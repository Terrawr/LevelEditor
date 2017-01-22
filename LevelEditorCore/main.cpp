#include <stdlib.h>
#include <SDL.h>
#include <vector>
#include <chrono>

#include "GameState.h"
#include "GameObject.h"

#include "Demo_State_jojo.h"
#include "EditorState.h"
#include "IntroScreen.h"
#include "mainmenu.h"

#include <>

#include "Command.h"

#pragma region "test"




#pragma endregion



void initGame(GameObj* obj) {
	obj->Assets.RessourcePath = "../resources/";

	rm_storeString(obj, "TheMap.map", "Mapfile");

	rm_loadTextureFromFile(obj, "firstbanner.png", "firstbanner");
	rm_loadTextureFromFile(obj, "copy.png", "copy");

	rm_loadTextureFromFile(obj, "resources.png", "resources");
	rm_loadTextureFromFile(obj, "NewGameBackGround.png", "WindowBackground");
	rm_loadTextureFromFile(obj, "test.bmp", "EditorBackground");

	rm_loadTextureFromFile(obj, "background.png", "background");
	rm_loadTextureFromFile(obj, "resources.png", "resources");

	rm_loadTextureFromFile(obj, "newgamebackground.png", "newgame_background");
	rm_loadTextureFromFile(obj, "characters.png", "characters");
	obj->Assets.MapsPath = "..\\resources\\maps\\";



}

struct Command;
int main(int argc, char* argv[]) 
{
	GameObj*  Root = createGameObjectHandle();
	initializeGameObj(Root,"LevelEditor", 1440,786);
	initGame(Root);

	//The Order of initilization is IMPORTANT. I changed it. First Screen, now your Menu and then some demo

	/*GameState* DEMOSTATE = createGameState_ObjectInstance(Root);
	initializeGameState(DEMOSTATE, "DEMOSTATE", -1,
		Demo_OnEnterState,
		Demo_OnExitState,
		Demo_OnPauseState,
		Demo_OnResumeState,
		Demo_Update,
		Demo_Render,
		Demo_Input);*/

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

	

	
	while (!Root->isRunning) {

		auto timePoint1(std::chrono::high_resolution_clock::now());
		//SDL_Log(".....CurrentState %d\n", Root->CurrentStateIndex); //<---- added this so you can see on your CONSOLE which state you are currently in. Thats the reason i remove fullscreen mode everytime you putt it back to see the console ;P 
		if(!Root->Collection.empty()){

			if (!Root->Collection[Root->CurrentStateIndex]->isInitialized)
				Root->Collection[Root->CurrentStateIndex]->onEnter(Root);

			if (Root->Collection[Root->CurrentStateIndex]->isActive)
				Root->Collection[Root->CurrentStateIndex]->onResume(Root);

			if (Root->Collection[Root->CurrentStateIndex]->isOnPause)
				Root->Collection[Root->CurrentStateIndex]->onPause(Root);

			Root->Collection[Root->CurrentStateIndex]->Input(Root, Root->lastFrameTime);
			Root->Collection[Root->CurrentStateIndex]->Update(Root, Root->lastFrameTime);
			Root->Collection[Root->CurrentStateIndex]->Render(Root, Root->lastFrameTime);

			/////////////////////////////////////////////////////////////////////////
			///////////////////Commands are Processed here///////////////////////////
			/////////////////////////////////////////////////////////////////////////

			while (!Root->HolyCommands.empty()) {
				Command* cmd = Root->HolyCommands.back();
				switch (cmd->Type)
				{
					case EXIT:
					case TERMINATE_GAME:
					{
						cmd->action(Root, 0.f);
						Root->HolyCommands.pop_back();
					}break;
					case STATEUP:
					case NEXT_STATE:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;
					case PREVIOUS_STATE:
					case STATEDOWN:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;
					case PAUSE_STATE:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;
					case RESUME_STATE:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;
					case UNKOWN:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;
					case TERMINATE_STATE:
					{
						cmd->action(Root, 0);
						Root->HolyCommands.pop_back();
					}break;

				}
			}

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
		Root->lastFrameTime = ft; //<-- Saves last frame time in milliseconds and stores them NOW globally
	
	}


	return 0;
}

