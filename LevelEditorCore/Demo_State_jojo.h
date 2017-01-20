#pragma once


#include "GameState.h"

CHANGESTATE(Demo_OnEnterState);
CHANGESTATE(Demo_OnExitState);
CHANGESTATE(Demo_OnPauseState);
CHANGESTATE(Demo_OnResumeState);

TOPROCESS(Demo_Update);
TOPROCESS(Demo_Input);
TOPROCESS(Demo_Render);

