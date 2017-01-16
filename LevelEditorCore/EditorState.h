#pragma once
#include "GameState.h"

CHANGESTATE(EditorOnEnterState);
CHANGESTATE(EditorOnExitState);
CHANGESTATE(EditorOnPauseState);
CHANGESTATE(EditorOnResumeState);

TOPROCESS(EditorUpdate);
TOPROCESS(EditorInput);
TOPROCESS(EditorRender);



static int a=0;