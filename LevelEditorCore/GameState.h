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

//Create a new Instance of an GameState and register the same
//Instance directly in the Gameobj. GameState still needs to
// be initialized BEFORE use!!!!
GameState* createGameState_ObjectInstance(GameObj* obj);

void initializeGameState(GameState* obj, const std::string& Name, int ID, changeState* OnEnter,
	changeState* OnExit,
	changeState* OnPause,
	changeState* OnResume,
	toProcess* Update,
	toProcess* Render,
	toProcess* Input);

void registerState(GameObj* obj, GameState*);
void deleteState(GameObj*, GameState*);
