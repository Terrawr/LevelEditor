#pragma once
#include "LevelEditor.h"

//Functionpointer description
typedef void changeState(struct GameState*);
typedef void toProcess(struct GameState*, struct GameObject*);

typedef struct GameState {
	char* Name;
	int	  ID;


}State;