#include <stdlib.h>
#include <SDL.h>
#include <vector>

#include "GameState.h"
#include "GameObject.h"

#include "SplashScreen.h"
#include "Splashscreen2.h"

int gQuit = SDL_FALSE;


int main(int argc, char* argv[]) 
{
	GameObj*  Root = createGameObjectHandle();
	initializeGameObj(Root,"LevelEditor",800,600);
	
	GameState SplashScreen;
	SplashScreen.Update = SplashUpdate;
	SplashScreen.Input = SplashInput;
	SplashScreen.Render = SplashRender;
	SplashScreen.onEnter = SplashonEnter;
	SplashScreen.onExit = SplashonExit;

	registerState(Root, &SplashScreen);
	Root->CurrentStateIndex = 0;

	while (!Root->isRunning) {

		if (!Root->Collection[Root->CurrentStateIndex]->isActive)
			Root->Collection[Root->CurrentStateIndex]->onEnter(Root);
		Root->Collection[Root->CurrentStateIndex]->Input(Root,0.016f);
		Root->Collection[Root->CurrentStateIndex]->Update(Root, 0.016f);
		Root->Collection[Root->CurrentStateIndex]->Render(Root, 0.016f);
	
	}

	getchar();
	getchar();

	return 0;
}