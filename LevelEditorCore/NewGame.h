#pragma once
#include "GameState.h"

CHANGESTATE(NewGameOnEnterState);
CHANGESTATE(NewGameOnExitState);
CHANGESTATE(NewGameOnPauseState);
CHANGESTATE(NewGameOnResumeState);

TOPROCESS(NewGameUpdate);
TOPROCESS(NewGameInput);
TOPROCESS(NewGameRender);