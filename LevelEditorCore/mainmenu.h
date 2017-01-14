#pragma once
#include "GameState.h"

CHANGESTATE(MainMenuOnEnterState);
CHANGESTATE(MainMenuOnExitState);
CHANGESTATE(MainMenuOnPauseState);
CHANGESTATE(MainMenuOnResumeState);

TOPROCESS(MainMenuUpdate);
TOPROCESS(MainMenuInput);
TOPROCESS(MainMenuRender);