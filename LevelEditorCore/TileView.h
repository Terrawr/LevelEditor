#pragma once


CHANGESTATE(TileView_OnEnter);
CHANGESTATE(TileView_OnExitState);
CHANGESTATE(TileView_OnPauseState);
CHANGESTATE(TileView_OnResumeState);

TOPROCESS(TileView_Update);
TOPROCESS(TileView_Input);
TOPROCESS(TileView_Render);