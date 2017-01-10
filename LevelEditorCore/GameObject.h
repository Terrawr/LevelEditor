#pragma once
#include "LevelEditor.h"
#include "GameState.h"

typedef struct GameObjectHandle
{
	State*		 CurrentState;
	ManagedArray StateCollection;

	
}GameObj;


GameObj* createGameObjectHandle();
void     initializeGameObj(GameObj*);
