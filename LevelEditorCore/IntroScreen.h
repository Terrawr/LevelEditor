#pragma once
#include "GameState.h"

//CHANGESTATE(IntroOnEnterState);
void IntroOnEnterState(GameObj* obj);

CHANGESTATE(IntroOnExitState);
CHANGESTATE(IntroOnPauseState);
CHANGESTATE(IntroOnResumeState);

TOPROCESS(IntroUpdate);
TOPROCESS(IntroInput);
TOPROCESS(IntroRender);