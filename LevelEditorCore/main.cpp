#include <stdlib.h>
#include <SDL2\SDL.h>
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

	GameState SplashScreen2;
	SplashScreen2.Update = SplashUpdate2;
	SplashScreen2.Input = SplashInput2;
	SplashScreen2.Render = SplashRender2;

	registerState(Root, &SplashScreen);
	registerState(Root, &SplashScreen2);
	Root->CurrentStateIndex = 0;

	while (!gQuit) {

		Root->Collection[Root->CurrentStateIndex]->Input(Root);
		Root->Collection[Root->CurrentStateIndex]->Update(Root);
		Root->Collection[Root->CurrentStateIndex]->Render(Root);

		if (Root->CurrentStateIndex == 0)
			Root->CurrentStateIndex = 1;
		else
			Root->CurrentStateIndex = 0;
	
	}


	return 0;
}