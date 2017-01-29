#pragma once

CHANGESTATE(TileMapEditor_OnEnter);
CHANGESTATE(TileMapEditor_OnExit);
CHANGESTATE(TileMapEditor_OnPause);
CHANGESTATE(TileMapEditor_OnResume);

TOPROCESS(TileMapEditor_Update);
TOPROCESS(TileMapEditor_Input);
TOPROCESS(TileMapEditor_Render);