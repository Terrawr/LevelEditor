#include <stdlib.h>
#include <SDL.h>
#include <vector>
#include <chrono>

#include "GameState.h"
#include "GameObject.h"

#include "SplashScreen.h"
#include "Splashscreen2.h"
#include "EditorState.h"

int gQuit = SDL_FALSE;


int main(int argc, char* argv[]) 
{
	GameObj*  Root = createGameObjectHandle();
	initializeGameObj(Root,"LevelEditor", 1440,786);


	GameState LevelEditor;
	LevelEditor.onEnter = EditorOnEnterState;
	LevelEditor.onExit = EditorOnExitState;
	LevelEditor.onPause= EditorOnPauseState;
	LevelEditor.onResume = EditorOnResumeState;

	LevelEditor.Update = EditorUpdate;
	LevelEditor.Render = EditorRender;
	LevelEditor.Input = EditorInput;
	
	registerState(Root, &LevelEditor);
	Root->CurrentStateIndex = 0;

	float lastFrameTime = 0;
	while (!Root->isRunning) {

		auto timePoint1(std::chrono::high_resolution_clock::now());

		if (!Root->Collection.empty()) {

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