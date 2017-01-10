#pragma once
#include "LevelEditor.h"
#include <vector>

struct GameState;
struct GameObj;
//Functionpointer description

#define CHANGESTATE(name) void name()
#define TOPROCESS(name) void name(GameObj* obj)

typedef CHANGESTATE(changeState);
typedef TOPROCESS(toProcess);


struct GameState {
	char*					Name;
	int						ID;
	std::vector<GameState*>	InternalStates; //TODO(jojo): Necessary? or maybe different?

	//Must be coded for each State seperatly
	changeState* onEnter;
	changeState* onExit;
	
	changeState* onPause;
	changeState* onResume;

	toProcess*  Update;
	toProcess*  Input;
	toProcess*  Render;

};
