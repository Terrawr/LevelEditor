#pragma once
#include "LevelEditor.h"
#include <functional>



enum {
	EXIT,
	STATEUP,
	STATEDOWN,
	UNKOWN
};

typedef void CallBack(GameObj*, float delta);
struct GameObj;

struct Command {

	int					Type;
	CallBack*			action;

};


static inline Command* createCommand(CallBack* action, int type) {
	Command* tmp = new Command;
	tmp->action = action;
	tmp->Type = type;
	return tmp;
};

static inline void registerCommand(GameObj* obj, CallBack* action, int type) {
	Command* tmp = createCommand(action, type);
	obj->HolyCommands.push_back(tmp);
}