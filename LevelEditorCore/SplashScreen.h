#pragma once
#include "GameState.h"

enum SUPPORTEDCOMMANDTYPES{
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
