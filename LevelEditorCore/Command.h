#pragma once
#include "LevelEditor.h"
#include <functional>

struct GameObj;
typedef struct COMMANDDESCRICPTION {

	int				Type;
	std::function<void(GameObj*, float delta)>	action;

}Command;