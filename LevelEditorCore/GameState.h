#pragma once
#include "LevelEditor.h"

//Functionpointer description
typedef void changeState(struct GameState*);
typedef void toProcess(struct GameState*, struct GameObject*);

typedef struct GameState {
	char*			Name;
	int				ID;
	ManagedArray	InternalStates; //TODO(jojo): Necessary? or maybe different?

	//Must be coded for each State seperatly
	changeState* onEnter;
	changeState* onExit;
	
	changeState* onPause;
	changeState* onResume;

	toProcess*  Update;
	toProcess*  Input;
	toProcess*  Render;

}State;