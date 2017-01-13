#include "GameState.h"
#include "GameObject.h"


void registerState(GameObj* obj, GameState* state) {
	obj->Collection.push_back(state);
}
void deleteState(GameObj* obj, GameState* state) {

	obj->Collection.erase(
		std::find(
			std::begin(obj->Collection),
			std::end(obj->Collection),
			state));
}


GameState* createGameStateObjectAt(GameObj* obj) {
	GameState* state = (GameState*)malloc(sizeof(GameState));
	registerState(obj, state);

	return state;
}

void initializeGameState(GameState* obj, const std::string& Name, int ID, changeState* OnEnter,
	changeState* OnExit,
	changeState* OnPause,
	changeState* OnResume,
	toProcess* Update,
	toProcess* Render,
	toProcess* Input) {

}