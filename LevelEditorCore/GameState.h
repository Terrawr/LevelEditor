#pragma once
#include "LevelEditor.h"
#include <vector>

//forward Declaration of structs to prevent circular dependencies
struct GameState;
struct GameObj;

//Functionpointer description
#define CHANGESTATE(name) void name(GameObj* obj)
#define TOPROCESS(name) void name(GameObj* obj, float elapsedTime_Lag)

//creating Functionpointer types
typedef CHANGESTATE(changeState);
typedef TOPROCESS(toProcess);

/**
* \brief GameState is the Interface description for all possible Gamestates
*
*
* GameState only stores some Metainformation which are independet from any
* possible given state such as the status about state of initialisation or
* state of being active or on pause.
*
*
* It also stores pointer to functions. A GameState does not care about the 
* implementation of those given function pointer as long as they are conform
* to the description of those functionpointers. Through this we achieve somekind
* polymorphism in C. The Actuall implementation of this "Interface" happens in 
* diffierent moduls which exposes 7 functions in their header files which can then
* be assign to the Function pointer in this structur.
*
* By storing serveral Instances of GameStates, each Instance storing different
* pointer to functions or different implementations of this functionpointer, we gain
* the capability of executing different behaviour at different poinst in time but still
* using the very same structure.
*/
struct GameState {
	char*					Name;
	int						ID;
	bool					isInitialized = false;;
	bool					isActive = false;
	bool					isOnPause = false;
	std::vector<GameState*>	InternalStates; //TODO(jojo): Necessary? or maybe different?

	//Must be coded for each State seperatly
	changeState* onEnter;
	changeState* onExit;
	
	changeState* onPause;
	changeState* onResume;

	toProcess*  Update;
	toProcess*  Input;
	toProcess*  Render;

	GameState() : InternalStates() {}

};

//
/**
* \brief Create a new Instance of an GameState 
*
* \param GameObj reference to the Global GameObject where all GameStates are stored
*
* Creates a new Instance and register the same Instance 
* directly in the Gameobj. GameState still needs to be 
* initialized BEFORE use!!!! WARNING THIS FUNCTION IS USING MALLOC/c++ style new
*/
GameState* createGameState_ObjectInstance(GameObj* obj);
/**
* \brief Destroys instances of GameState
*
* \param GameObj reference to the Global GameObject where all GameStates are stored
* \param GameState the state which should be removed from the System
*
* Creates a new Instance and register the same Instance
* directly in the Gameobj. GameState still needs to be
* initialized BEFORE use!!!! WARNING THIS FUNCTION IS USING MALLOC/c++ style new
*/
void	   destroyObjectInstanceOf_GameState(GameObj*, GameState* state);

/**
* \brief Intialised a earlier created Gamestate instance if not already Intialised Instance
* \param GameState which should be initialized.
* \param Name of the given Gamestate. does not need to be unique.
* \param ID of the given GameSTate. Should be unique.
* \param OnExit pointer to specific function which implements the behaviour if States Exit
* \param OnPause pointer to specific function which implements the behaviour if States is pausing
* \param OnResume pointer to specific function which implements the behaviour if States resuming
* \param Update pointer to specific function which implements the behaviour of the update
* \param Render pointer to specific function which implements the behaviour of the render
* \paramn Input pointer to specific function which implements the behaviour of the input
*
* This function does nothing else the overriding the given function pointer stored in the 
* struct "GameState" to the corresponding functions representing the actual state you want
* to execute to later point in time in your program.
*/
void initializeGameState(GameState* obj, const std::string& Name, int ID, changeState* OnEnter,
	changeState* OnExit,
	changeState* OnPause,
	changeState* OnResume,
	toProcess* Update,
	toProcess* Render,
	toProcess* Input);

void registerState(GameObj* obj, GameState*);
void deleteState(GameObj*, GameState*);
