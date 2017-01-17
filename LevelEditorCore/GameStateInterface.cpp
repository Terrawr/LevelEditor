#include "GameState.h"
#include "GameObject.h"


void registerState(GameObj* obj, GameState* state) {
	obj->Collection.push_back(state);
}
void deleteState(GameObj* obj, GameState* state) {

	auto stateIter = std::find(
		std::begin(obj->Collection),
		std::end(obj->Collection),
		state);

	obj->Collection.erase(stateIter);
	//Frees state because when create with createGameStateObject() malloc were used
	free(state);
}


GameState* createGameState_ObjectInstance(GameObj* obj) {
	GameState* state = new GameState(); // DO NOT USE MALLOC!!! BECAUSE WE USE STD::VECTOR WE NEED TO MAKE SURE CTOR OF STD::VECTOR IS CALLED
	registerState(obj, state);

	return state;
}


void destroyObjectInstanceOf_GameState(GameObj* obj, GameState* state) {
	deleteState(obj, state);
}

void initializeGameState(GameState* obj, const std::string& Name, int ID, changeState* OnEnter,
	changeState* OnExit,
	changeState* OnPause,
	changeState* OnResume,
	toProcess* Update,
	toProcess* Render,
	toProcess* Input) {

	obj->onEnter = OnEnter;
	obj->onExit = OnExit;
	obj->onPause = OnPause;
	obj->onResume = OnResume;

	obj->Update = Update;
	obj->Render = Render;
	obj->Input = Input;

	obj->ID = ID;
	obj->Name =(char*) Name.c_str();
	obj->isInitialized = false;


}