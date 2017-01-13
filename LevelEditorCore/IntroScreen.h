#pragma once
#include "GameState.h"

CHANGESTATE(IntroOnEnterState);
CHANGESTATE(IntroOnExitState);
CHANGESTATE(IntroOnPauseState);
CHANGESTATE(IntroOnResumeState);

TOPROCESS(IntroUpdate);
TOPROCESS(IntroInput);
TOPROCESS(IntroRender);