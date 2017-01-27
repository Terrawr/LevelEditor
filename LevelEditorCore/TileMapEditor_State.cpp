#include "GameState.h"
#include "GameObject.h"
#include "Texture.h"
#include "Command.h"
#include <SDL.h>
#include <iostream>

#include "Tiles.h"

#include "guisan.hpp"
#include "guisan\sdl.hpp"

#include "LevelEditor.h"
using namespace gcn;

#pragma region "The HolyCommands"

static COMMAND_CALLBACK(CMD_EXIT); //!<-- Terminates the Game
static COMMAND_CALLBACK(CMD_TERMINATE_STATE); //!<-- Terminats this State

static COMMAND_CALLBACK(CMD_NEXT_STATE); //!<-- Moves this state to the next one. 
static COMMAND_CALLBACK(CMD_PREVIOUS_STATE); //!<-- Moves this state to the previous one. 
static COMMAND_CALLBACK(CMD_CURRENT_PAUSE);
static COMMAND_CALLBACK(CMD_CURRENT_RESUME);
static COMMAND_CALLBACK(CMD_RELOAD_MAP);

#pragma endregion




#pragma region "Global Variables"

static GameObj*				Root = NULL;
static GameState*			This = NULL;

TM_TileMap		gMapViewTiles;

Texture			gTex_MapView;
Texture			gTex_TileView;

SDL_Surface*	gSurf_UserInterface;
Texture			gTex_UIDrawContext;

gcn::Container*	gRoot_ContainerWidget;
gcn::Container* gMenu_ContainerWidget;
gcn::Container* gPropertyView_ContainerWidget;

gcn::Button*	gMenu_SaveMap_ButtonWidget;
gcn::Button*	gMenu_ResetMap_ButtonWidget;
gcn::Button*	gMenu_Undo_ButtonWidget;
gcn::Button*	gMenu_Exit_ButtonWidget;
gcn::Button*	gMenu_ExitAndSave_ButtonWidget;

gcn::Image*		gPropertyView_ImageWidget;
gcn::Icon*		gPropertyView_IconWidget; //<-- Needed to display an Image


int gCurrentChosenTileID = 0;
SDL_Rect Mouse = { 0,0,0,0 };

std::fstream csv;

enum TEXTBOXCONTENTTYPES{
	TYPE,
	CATEGORY,
	ANGLE,
	NAME,
	MAXCONTENTTYPES
};
gcn::TextField* gPropertyView_TextFieldWidget_Array[TEXTBOXCONTENTTYPES::MAXCONTENTTYPES];
gcn::Label*		gPropertyView_LabelWidget_Array[TEXTBOXCONTENTTYPES::MAXCONTENTTYPES];

#pragma endregion

#pragma region "Helperclass"
class TextureImage : public gcn::SDLImage {
public:
	TextureImage(Texture* t) :gcn::SDLImage(NULL, false) {
		initilizeTexture(&this->t, Root->Renderer);
	}

	/**
	* Gets the SDL surface for the image.
	*
	* @return the SDL surface for the image.
	*/
	Texture* getTexture() const {};


	// Inherited from Image

	virtual void free() {};

	virtual int getWidth() const {};

	virtual int getHeight() const {};

	virtual Color getPixel(int x, int y) {};

	virtual void putPixel(int x, int y, const Color& color) {};

	virtual void convertToDisplayFormat() {};

protected:
	Texture t;
};
class TextureImageLoader : public gcn::SDLImageLoader
{
public:
	virtual Image* load(Texture* tex, SDL_Rect Clip, bool convertToDisplayFormat = true)
	{

	}
};

#pragma endregion

#pragma region "Actionlistner"

class MenuButtonListner : public gcn::ActionListener
{
public:

	void action(const gcn::ActionEvent& actionEvent) {


		if (actionEvent.getId() == "Save") {}
		if (actionEvent.getId() == "Exit") {
			registerCommand(Root, CMD_EXIT, TERMINATE_STATE);
		}
		if (actionEvent.getId() == "Save") {}
		if (actionEvent.getId() == "Save") {}
		if (actionEvent.getId() == "Save") {}
	}
};

#pragma endregion

#pragma region "Forward declarations"
#pragma endregion

CHANGESTATE(TileMapEditor_OnEnter) {
	
	Root = obj;
	This = Root->Collection[Root->CurrentStateIndex];
	
	//csv.open("data.csv", std::ios_base::in | std::ios_base::out | std::ios_base::app);
	/*if (!csv.is_open())
		abort();*/
	auto map = TM_loadTileMapJSON("Test.json");
	gMapViewTiles = TM_InitializeTileMapFromJSON(map);

#pragma region "Initialization of Objects"

	SDL_FreeSurface(Root->UserInterface_Display);
	SDL_DestroyTexture(Root->UserInterface_TextureDisplay);
	Root->UserInterface_Display = SDL_CreateRGBSurface(0, Root->Width, Root->Height, 32, 0, 0, 0, 255);

	SDL_FillRect(Root->UserInterface_Display, NULL,0xff00ff);
	if (Root->UserInterface_Display == nullptr) {

		std::cerr << SDL_GetError() << "\n";
		abort();
	}
	
	/*SDL_SetColorKey(Root->UserInterface_Display, SDL_TRUE, SDL_MapRGB(Root->UserInterface_Display->format,0xff,0x00,0xff));
	SDL_SetSurfaceBlendMode(Root->UserInterface_Display, SDL_BlendMode::SDL_BLENDMODE_BLEND);*/

	Root->UserInterface_TextureDisplay = SDL_CreateTextureFromSurface(Root->Renderer, Root->UserInterface_Display);
	//SDL_SetTextureBlendMode(Root->UserInterface_TextureDisplay, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	
	Root->graphics->setTarget(Root->UserInterface_Display);

	
	initilizeTexture(&gTex_MapView, Root->Renderer);
	initilizeTexture(&gTex_TileView, Root->Renderer);

	
	//createBlank(&gTex_UIDrawContext, Root->Width, Root->Height, SDL_TEXTUREACCESS_TARGET);
	createBlank(&gTex_MapView, Root->Width*0.5f, Root->Height*0.75, SDL_TEXTUREACCESS_TARGET);
	createBlank(&gTex_TileView, Root->Width*0.2f, Root->Height*0.75, SDL_TEXTUREACCESS_TARGET);

	auto WidgetOffsetX = [](gcn::Widget* a, gcn::Widget* b) -> int {
		return a->getDimension().x + a->getDimension().width + b->getDimension().width;
	};

#pragma region "GUI Container"

	gRoot_ContainerWidget			= new gcn::Container;
	gMenu_ContainerWidget			= new gcn::Container;
	gPropertyView_ContainerWidget	= new gcn::Container;

	gRoot_ContainerWidget->setDimension({ 0,0,Root->Width,Root->Height });
	gMenu_ContainerWidget->setDimension({ 0,0,Root->Width,70 });

	gPropertyView_ContainerWidget->setDimension({ Root->Width - gTex_TileView.mWidth - 10,{ (int)(Root->Height*0.2f) },gTex_TileView.mWidth,gTex_TileView.mHeight });
	gPropertyView_ContainerWidget->setBaseColor({ 255,0,0 });
	gMenu_ContainerWidget->setBaseColor({ 0,255,0 });
	//gRoot_ContainerWidget->setBaseColor({ 0,0,255,0 });
	gRoot_ContainerWidget->setOpaque(false);

	
#pragma endregion

#pragma region "Menu Widgets"

	gMenu_SaveMap_ButtonWidget = new gcn::Button("Save Map");
	gMenu_ResetMap_ButtonWidget = new gcn::Button("Reset Map");
	gMenu_Undo_ButtonWidget = new gcn::Button("Undo");
	gMenu_Exit_ButtonWidget = new gcn::Button("Exit");
	gMenu_ExitAndSave_ButtonWidget = new gcn::Button("Exit_Save");

	gMenu_SaveMap_ButtonWidget->adjustSize();
	gMenu_SaveMap_ButtonWidget->adjustSize();
	gMenu_ResetMap_ButtonWidget->adjustSize();
	gMenu_Undo_ButtonWidget->adjustSize();
	gMenu_ExitAndSave_ButtonWidget->adjustSize();
	gMenu_Exit_ButtonWidget->adjustSize();

#pragma endregion

#pragma region "PropertyView Widgets"

	gPropertyView_ImageWidget = Root->imageLoader->load("../resources/demo_tiles.bmp");
	gPropertyView_IconWidget = new gcn::Icon(gPropertyView_ImageWidget);
	gPropertyView_IconWidget->setPosition(150, 20);

	gPropertyView_ContainerWidget->setOpaque(true);
	gPropertyView_ContainerWidget->add(gPropertyView_IconWidget);

	for (int i = 0, offX=10,offY=100; i < MAXCONTENTTYPES; i++)
	{
		gPropertyView_TextFieldWidget_Array[i]	= new gcn::TextField("Please replace with Value");
		gPropertyView_LabelWidget_Array[i] = new gcn::Label("Empty Label");

		if (i != 0) {
			offX = WidgetOffsetX(gPropertyView_LabelWidget_Array[i], gPropertyView_TextFieldWidget_Array[i]) + 10;
			offY += 50;
			gPropertyView_LabelWidget_Array[i]->setDimension({ 10, offY,100,20 });
			gPropertyView_LabelWidget_Array[i]->setBaseColor({ 0,0,0 });
			gPropertyView_TextFieldWidget_Array[i]->setDimension({ offX, offY,100,20 });

			gPropertyView_ContainerWidget->add(gPropertyView_TextFieldWidget_Array[i]);
			gPropertyView_ContainerWidget->add(gPropertyView_LabelWidget_Array[i]);
		}
		else {

			//gPropertyView_LabelWidget_Array[i]->setPosition(offX, 50);
			//gPropertyView_TextFieldWidget_Array[i]->setPosition(WidgetOffsetX(gPropertyView_LabelWidget_Array[i], gPropertyView_TextFieldWidget_Array[i]), offY);

			//gPropertyView_ContainerWidget->add(gPropertyView_TextFieldWidget_Array[i]);
			//gPropertyView_ContainerWidget->add(gPropertyView_LabelWidget_Array[i]);
		}
	}


#pragma endregion
	

#pragma endregion

#pragma region "Compose UI"

	Root->UserInterface->setTop(gRoot_ContainerWidget);
	gRoot_ContainerWidget->add(gMenu_ContainerWidget);
	gRoot_ContainerWidget->add(gPropertyView_ContainerWidget);


	gMenu_ContainerWidget->add(gMenu_SaveMap_ButtonWidget);
	gMenu_ContainerWidget->add(gMenu_ResetMap_ButtonWidget);
	gMenu_ContainerWidget->add(gMenu_Undo_ButtonWidget);
	gMenu_ContainerWidget->add(gMenu_ExitAndSave_ButtonWidget);
	gMenu_ContainerWidget->add(gMenu_Exit_ButtonWidget);


	gMenu_SaveMap_ButtonWidget->setPosition(5, 5);
	gMenu_ResetMap_ButtonWidget->setPosition(WidgetOffsetX(gMenu_SaveMap_ButtonWidget, gMenu_ResetMap_ButtonWidget), 5);
	gMenu_Undo_ButtonWidget->setPosition(WidgetOffsetX(gMenu_ResetMap_ButtonWidget, gMenu_Undo_ButtonWidget) , 5);
	gMenu_ExitAndSave_ButtonWidget->setPosition(WidgetOffsetX(gMenu_Undo_ButtonWidget, gMenu_ExitAndSave_ButtonWidget) , 5);
	gMenu_Exit_ButtonWidget->setPosition(WidgetOffsetX(gMenu_ExitAndSave_ButtonWidget, gMenu_Exit_ButtonWidget), 5);

#pragma region "Connect Buttons to Behaviour"

	MenuButtonListner* MenuListner = new MenuButtonListner;
	gMenu_Exit_ButtonWidget->addActionListener(MenuListner);
	gMenu_Exit_ButtonWidget->setActionEventId("Exit");
	
#pragma endregion


#pragma endregion

	This->isInitialized = true;
}

CHANGESTATE(TileMapEditor_OnExit) {
	This->isInitialized = false;
}
CHANGESTATE(TileMapEditor_OnPause) {
	This->isActive = false;
	This->isOnPause = true;
}
CHANGESTATE(TileMapEditor_OnResume) {
	This->isOnPause = false;
}

TOPROCESS(TileMapEditor_Update) {
	Root->UserInterface->logic();

	SDL_Rect MapViewRect = { 10, Root->Height*0.2,gTex_MapView.mWidth,gTex_MapView.mHeight };

	int gridsize = 50;

	Mouse.x = gridsize * std::floor((float)((Root->MouseX / gridsize) + 0.5f)) + 10 ;
	Mouse.y = gridsize * std::floor((float)((Root->MouseY / gridsize) + 0.5f)) - 10;
	if (isMouseOverButton(Root, MapViewRect))
	{

		Mouse.x = gridsize * std::floor((float)((Root->MouseX / gridsize) + 0.5f)) +10;
		Mouse.y = gridsize * std::floor((float)((Root->MouseY / gridsize) + 0.5f)) -10;

		

	}
}
TOPROCESS(TileMapEditor_Input) {
	SDL_Event e;
	SDL_Rect TileSheetViewRect = { gTex_MapView.mWidth + 50, (float)(Root->Height*0.2),gTex_TileView.mWidth + 15,gTex_TileView.mHeight };
	
	//SDL_StartTextInput();
	while (SDL_PollEvent(&e))
	{
		//Forwarding Events to GUI
		Root->input->pushInput(e);
		if (e.type == SDL_QUIT )
		{
			registerCommand(Root, CMD_EXIT, TERMINATE_GAME);
		}
		if (e.type == SDL_KEYDOWN) {
			if(e.key.keysym.sym == SDLK_ESCAPE)
				registerCommand(Root, CMD_EXIT, TERMINATE_GAME);
		}
		Mouse = { Root->MouseX ,Root->MouseY ,50,50 };
		///////////////WARNING LOGIC SHOULD BE CONTAINED WITHIN THE UPDATE FUNCTION YOU IDIOT/////////////////////////////////
		if (isMouseOverButton(Root, TileSheetViewRect))
		{
			int gridsize = 50;
			auto TS_RatioW = TileSheetViewRect.w / gridsize; //WARNING TILE SIZE HARDCODED!!!!!!!!!!!!!!!!!
			auto TS_RatioH = TileSheetViewRect.w / gridsize; //WARNING TILE SIZE HARDCODED!!!!!!!!!!!!!!!!!
			
			Mouse.x = gridsize * std::floor((float)((Root->MouseX / gridsize) + 0.5f)) + 10;
			Mouse.y = gridsize * std::floor((float)((Root->MouseY / gridsize) + 0.5f)) - 10;

			//std::cerr << "MouseRect: " << Mouse.x << " | " << Mouse.y << "----" << Mouse.w << " | " << Mouse.h << "\n";

			int ID = 0;
			for (int m = 0; m < TS_RatioH; m++, ID++)
			{
				for (int n = 0; n < TS_RatioW; n++, ID++) {



					SDL_Rect dest = { 0,0,50 - 2, 5 - 2 };
					dest.x = n * 50 + TileSheetViewRect.x; //Add offset relativ from the windows 0,0 COORD
					dest.y = m * 50 + TileSheetViewRect.y; //Add offset relativ from the windows 0,0 COORD
														   //std::cerr << "++DesRect: " << dest.x << " | " << dest.y << "-" << dest.w << "|" << dest.h << "\n";
					

					//std::cerr<< CurrentGID << ";" << CurrentID << "\n";
					
					

					//std::cerr << "-------------Current TileView ID: " << CurrentID << "\n";
					if (ID == TS_RatioW)
					{
						break;
					}

				}
				if (ID == TS_RatioW)
				{
					break;
				}
			}
				

			
		}
		//////////////////////////////////////////////////////////IDIOT///////////////////////////////////////////////////////

	}

	auto CurrentGID = TM_getGlobalGridID(TileSheetViewRect, Mouse, 50);


	auto CurrentID = TM_getGridID(TileSheetViewRect, Mouse, 50, 92);
	//SDL_StopTextInput();
	SDL_GetMouseState(&obj->MouseX, &obj->MouseY);
}

TOPROCESS(TileMapEditor_Render) {

	SDL_Rect MapView = { 0,0,gTex_MapView.mWidth-10,gTex_MapView.mHeight };
	SDL_Rect TileView = { 0,0,gTex_TileView.mWidth + 15,gTex_TileView.mHeight };

	Root->UserInterface->draw();
	SDL_UpdateTexture(Root->UserInterface_TextureDisplay, NULL, Root->UserInterface_Display->pixels, Root->UserInterface_Display->pitch);

	SDL_RenderClear(Root->Renderer);
	SDL_RenderCopy(Root->Renderer, Root->UserInterface_TextureDisplay, NULL, NULL); //Render First the UserInterface managed by GUISan

	////
	setAsRenderTarget(&gTex_MapView);
	renderTileMap(&gMapViewTiles, Root->Renderer);

	setAsRenderTarget(&gTex_TileView);
	renderTileSheetView(&gMapViewTiles.Tilesets[0], Root->Renderer);

	SDL_SetRenderTarget(Root->Renderer, NULL);
	////
	
	render(&gTex_MapView, 10, Root->Height*0.2,
		&MapView, 0, 0, SDL_FLIP_NONE);
	render(&gTex_TileView, gTex_MapView.mWidth+50, Root->Height*0.2,
		&TileView, 0, 0, SDL_FLIP_NONE);

	/*for (int i = 0; i < Root->Height / 50; i++)
		for (int j = 0; j < Root->Width / 50; j++)
		{
			SDL_Rect GridTile = { 50 * j+10, i * 50-10, 50,50 };
			SDL_RenderDrawRect(Root->Renderer, &GridTile);
		}*/


	SDL_SetRenderDrawColor(Root->Renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(Root->Renderer, &Mouse);

	SDL_RenderPresent(Root->Renderer);
}



#pragma region "Implementations of the Holy Commands"
static COMMAND_CALLBACK(CMD_EXIT) {
	Root->isRunning = true;
} //!<-- Terminates the Game
static COMMAND_CALLBACK(CMD_TERMINATE_STATE) {} //!<-- Terminats this State

static COMMAND_CALLBACK(CMD_NEXT_STATE) {} //!<-- Moves this state to the next one. 
static COMMAND_CALLBACK(CMD_PREVIOUS_STATE) {} //!<-- Moves this state to the previous one. 
static COMMAND_CALLBACK(CMD_CURRENT_PAUSE) {}
static COMMAND_CALLBACK(CMD_CURRENT_RESUME) {}
static COMMAND_CALLBACK(CMD_RELOAD_MAP) {}
#pragma endregion