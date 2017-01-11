#pragma once
#include "GameState.h"

CHANGESTATE(EditorOnEnterState);
CHANGESTATE(EditorOnExitState);

TOPROCESS(EditorUpdate);
TOPROCESS(EditorInput);
TOPROCESS(EditorRender);