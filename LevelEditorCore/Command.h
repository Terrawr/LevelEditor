#pragma once
#include "LevelEditor.h"
#include <functional>


//DEFINES BEHAVIOUR FOR THE PROGRAMM. Internal State behaviour must be defined seperatly!!!!!!!!!!!!!!!!!!!!
enum {
	EXIT,
	STATEUP,
	STATEDOWN,
	TERMINATE_STATE,
	TERMINATE_GAME,
	NEXT_STATE,
	PREVIOUS_STATE,
	PAUSE_STATE,
	RESUME_STATE,
	UNKOWN
};

#define COMMAND_CALLBACK(name) void name(GameObj* obj, float dt)
typedef COMMAND_CALLBACK(CallBack);

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