#pragma once
#include "GameState.h"
#include "Command.h"

PUBLIC SDL_Rect Frame_Rect;
PUBLIC SDL_Rect FrameChosen_Rect;
PUBLIC SDL_Rect FrameClicked_Rect;
PUBLIC SDL_Rect Background_Rect;
PUBLIC SDL_Rect CreateNewGame_Rect;
PUBLIC SDL_Rect LoadGame_Rect;
PUBLIC SDL_Rect LevelEditor_Rect;
PUBLIC SDL_Rect Exit_Rect;
PUBLIC TTF_Font* MenuFont;
PUBLIC SDL_Color MenuCol;

PUBLIC int MouseOnNewGame ; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
PUBLIC int MouseOnLoadGame ; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
PUBLIC int MouseOnLevelEditor ; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
PUBLIC int MouseOnExit ; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, MainMenu Button
PUBLIC int MouseOnCancel ; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, CreateNewGameMenu Button
PUBLIC int MouseOnCreate; // 0 = Mouse not on this Tile, 1 = Mouse on this Tile, CreateNewGameMenu Button

PUBLIC SDL_Surface* TextNewGame;
PUBLIC SDL_Surface* TextLoadGame;
PUBLIC SDL_Surface* TextLevelEditor;
PUBLIC SDL_Surface* TextExit;
PUBLIC SDL_Surface* TextCancel;
PUBLIC SDL_Surface* TextCreate;


PUBLIC int leftButtonMouse;
PUBLIC int justOneTurn;
PUBLIC int rightButtonMouse;
PUBLIC int elapsedTime;
PUBLIC int elapsedTimeClick;
PUBLIC int chosenwindow;
PUBLIC int turnsToProcess;
PUBLIC int characterchoice; //0-7
PUBLIC int charactersizeh;
PUBLIC int charactersizew;

COMMAND_CALLBACK(CMD_EXIT); //!<-- Terminates the Game
COMMAND_CALLBACK(CMD_TERMINATE_STATE); //!<-- Terminats this State

COMMAND_CALLBACK(CMD_NEXT_STATE); //!<-- Moves this state to the next one. 
COMMAND_CALLBACK(CMD_PREVIOUS_STATE); //!<-- Moves this state to the previous one. 
COMMAND_CALLBACK(CMD_CURRENT_PAUSE);
COMMAND_CALLBACK(CMD_CURRENT_RESUME);
COMMAND_CALLBACK(CMD_RELOAD_MAP);
COMMAND_CALLBACK(StateGoesUp);
COMMAND_CALLBACK(StateGoesDown);

void changeButtonStateIf(GameObj* obj, SDL_Rect* ButtonRect, int* state);


CHANGESTATE(MainMenuOnEnterState);
CHANGESTATE(MainMenuOnExitState);
CHANGESTATE(MainMenuOnPauseState);
CHANGESTATE(MainMenuOnResumeState);

TOPROCESS(MainMenuUpdate);
TOPROCESS(MainMenuInput);
TOPROCESS(MainMenuRender);