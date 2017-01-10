#pragma once
#include "LevelEditor.h"
#include <functional>

typedef void ActionReference(GameObj*, float delta);
struct GameObj;
struct Command {

	int				Type;
	ActionReference*	action;

};
void test(GameObj* obj, float t) 
{ 
	printf("Callbackfunction of a Command!!!\n");
	SDL_DestroyRenderer(obj->Renderer);
	obj->Renderer = NULL;
	SDL_DestroyWindow(obj->Window); 
	obj->Window = NULL;
};
Command* createCommand(ActionReference* action, int type) {
	Command* tmp = new Command;
	tmp->action = action;
	tmp->Type = type;
	return tmp;
};