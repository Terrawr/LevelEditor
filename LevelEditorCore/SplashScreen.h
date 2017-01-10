#pragma once
#include "GameState.h"

enum SUPPORTEDCOMMANDTYPES{
	EXIT,
	MOVEUP,
	MOVEDOWN,
	MOVELEFT,
	MOVERIGHT
};

CHANGESTATE(SplashonEnter);
CHANGESTATE(SplashonExit);

TOPROCESS(SplashUpdate);
TOPROCESS(SplashInput);
TOPROCESS(SplashRender);
