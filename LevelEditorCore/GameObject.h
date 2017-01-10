#pragma once
#include "LevelEditor.h"
#include "GameState.h"

typedef struct GameObjectHandle
{
	State*		 CurrentState;
	ManagedArray StateCollection;

	
}GameObj;


//Creates GameObject in Memory
GameObj* createGameObjectHandle();
void     initializeGameObj(GameObj*);

void registerState(GameObj*, State);
void deleteState(GameObj*, State);



