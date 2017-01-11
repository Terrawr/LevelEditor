#pragma once
#include "LevelEditor.h"
#include <vector>

//forward Declaration of structs to prevent circular dependencies
struct GameState;
struct GameObj;

//Functionpointer description
#define CHANGESTATE(name) void name(GameObj* obj)
#define TOPROCESS(name) void name(GameObj* obj, float elapsedTime_Lag)

//creating Functionpointer types
typedef CHANGESTATE(changeState);
typedef TOPROCESS(toProcess);


struct GameState {
	char*					Name;
	int						ID;
	bool					isInitialized = false;;
	bool					isActive = false;
	bool					isOnPause = false;
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
