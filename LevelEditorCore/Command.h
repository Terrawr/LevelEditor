#pragma once
#include "LevelEditor.h"


typename void** AnyFunction;

typedef struct COMMANDDESCRICPTION {

	int				Type;
	AnyFunction		CommandCallback;

}Command;