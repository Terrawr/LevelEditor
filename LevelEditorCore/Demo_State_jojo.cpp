//#include "GameState.h"
//#include "GameObject.h"
//#include "RessourceManager.h"
//#include "Command.h"
//
//#include "Tiles.h"
//#include <io.h>
//#include <iostream>
//
//#include "guisan/include/guisan.hpp"
//#include "guisan\include\guisan\sdl.hpp"
//
//#define __WIN__
//
///*
//* All of the default widgets
//*/
//gcn::Container* top;                 // A top container
////gcn::Label* label;                   // A label
////gcn::Icon* icon;                     // An icon (image)
////gcn::Button* button;                 // A button
////gcn::TextField* textField;           // One-line text field
////gcn::TextBox* textBox;               // Multi-line text box
////gcn::ScrollArea* textBoxScrollArea;  // Scroll area for the text box
//gcn::ListBox* listBox;               // A list box
////gcn::DropDown* dropDown;             // Drop down
////gcn::CheckBox* checkBox1;            // Two checkboxes
////gcn::CheckBox* checkBox2;
////gcn::RadioButton* radioButton1;      // Three radio buttons
////gcn::RadioButton* radioButton2;
////gcn::RadioButton* radioButton3;
////gcn::Slider* slider;                 // A slider
////gcn::Image *image;                   // An image for the icon
////gcn::Window *window;
////gcn::Image *guisanLogoImage;
////gcn::Icon* guisanLogoIcon;
////gcn::ScrollArea* nestedScrollArea;
////gcn::Container* nestedContainer;
////gcn::Slider* nestedSlider;
//
//int clickCountButton1 = 0; // Count clicks for button1
//int clickCountButton2 = 0; // Count clicks for button2
//
//gcn::Button* button1;     // A button for actionlistening
//gcn::Button* button2;     // Another button for actionlistening
//gcn::Label* label1;       // And a label for button1 click count display
//gcn::Label* label2;       // And another label for button2 click count display
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Command Callbacks////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//PRIVATE COMMAND_CALLBACK(CMD_EXIT); //!<-- Terminates the Game
//PRIVATE COMMAND_CALLBACK(CMD_TERMINATE_STATE); //!<-- Terminats this State
//
//PRIVATE COMMAND_CALLBACK(CMD_NEXT_STATE); //!<-- Moves this state to the next one. 
//PRIVATE COMMAND_CALLBACK(CMD_PREVIOUS_STATE); //!<-- Moves this state to the previous one. 
//
//PRIVATE COMMAND_CALLBACK(CMD_CURRENT_PAUSE);
//PRIVATE COMMAND_CALLBACK(CMD_CURRENT_RESUME);
//
//PRIVATE COMMAND_CALLBACK(CMD_RELOAD_MAP);
//
//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Private Global Variables//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//static GameObj*		Root			= NULL;
//GameState*			This			= NULL;
//
//static TileMap		ExampleMap;
//static TileSet*		ExampeTileset	= NULL;
//
//static std::vector<Tile> Renderables;
//using namespace gcn;
//
//SDL_Surface* screen;
//SDL_Texture* _Texture;
//
//gcn::ImageFont* font;     // A font
//
//
//
///*
//* To be able to recieve actions we must have a class inheriting from
//* ActionListener and implementing the action function.
//* When an action is generated in a Widget (i.e when a button is clicked)
//* that widget calls the action function for all its action listeners.
//* Below we make a class to be able to recieve our buttons actions.
//*/
////class ButtonActionListener : public gcn::ActionListener
////{
////public:
////	// Implement the action function in ActionListener to recieve actions
////	// The eventId tells us which widget called the action function.
////	void action(const gcn::ActionEvent& actionEvent)
////	{
////		std::string str;
////		std::ostringstream os(str);
////
////		// Here we use the widget pointer to check which widget the action
////		// originated from.
////		if (actionEvent.getId() == "button1")
////		{
////			clickCountButton1++;
////			os << "Button1 clicks " << clickCountButton1;
////			// Change the caption to show number of clicks
////			label1->setCaption(os.str());
////			// Adjust the label to fit the new caption
////			label1->adjustSize();
////
////
////
////
////			registerCommand(Root, CMD_EXIT, EXIT);
////
////		
////
////
////
////		}
////		// Here we use the event id in order to check what action occured.
////		else if (actionEvent.getId() == "button2")
////		{
////			clickCountButton2++;
////			os << "Button2 clicks " << clickCountButton2;
////			// Change the caption to show number of clicks
////			label2->setCaption(os.str());
////			// Adjust the label to fit the new caption
////			label2->adjustSize();
////		}
////	}
////};
////
////								 
//								  
//
//
///*ButtonActionListener* buttonActionListener; */// A pointer to the above class
//
////std::string Chop(std::string &str)
////{
////	std::string res = str;
////	int len = str.length();
////	if (str[len - 1] == 'r')
////	{
////		res.replace(len - 1, 1, "");
////	}
////	len = str.length();
////	if (str[len - 1] == 'n')
////	{
////		res.replace(len - 1, 1, "");
////	}
////	return res;
////}
////std::string DumpEntry(_finddata_t &data)
////{
////	//auto  s = (ctime(&data.time_create));
////	//std::wstring createtime;
////	//createtime.insert(std::end(createtime), std::begin(s), std::end(s));
////	//std::cout << Chop(createtime) << "t";
////	//std::cout << data.size << "t";
////	if ((data.attrib & _A_SUBDIR) == _A_SUBDIR)
////	{
////		std::cout << "[" << data.name << "]" << std::endl;
////	}
////	else
////	{
////		std::cout << data.name << std::endl;
////	}
////
////	for (int i = 0; data.name[i] != '\0'; i++) {
////
////		if (data.name[i] == '\\')
////			data.name[i] = '/';
////	}
////
////	return std::string(data.name);
////}
////std::vector<std::string> readDir(const std::string& path)
////{
////	std::vector<std::string> tmp;
////
////
////#ifdef __WIN__
////	_finddata_t data;
////	int ff = _findfirst(path.c_str(), &data);
////	if (ff != -1)
////	{
////		int res = 0;
////		while (res != -1)
////		{
////			tmp.push_back(DumpEntry(data));
////			res = _findnext(ff, &data);
////		}
////		_findclose(ff);
////	}
////#else
////#endif
////
////	return tmp;
////}
//
///*
//* List boxes and dropdowns needs an instance of a listmodel
//* to know what elements they have.
//*/
//class DirList : public gcn::ListModel
//{
//
//	std::vector<std::string>  files;
//
//;
//
//public:
//
//	DirList(const std::string& path)
//	{
//
//		files = readDir(path);
//	}
//
//	DirList()
//	{
//
//		files = readDir("*");
//	}
//
//	int getNumberOfElements()
//	{
//		return files.size();
//	}
//
//	std::string getElementAt(int i)
//	{
//		//switch (i) {
//		//case 0:
//		//	return std::string("zero");
//		//case 1:
//		//	return std::string("one");
//		//case 2:
//		//	return std::string("two");
//		//case 3:
//		//	return std::string("three");
//		//case 4:
//		//	return std::string("four");
//		//default: // Just to keep warnings away
//		//	return std::string("");
//		//}
//
//		return files[i];
//	}
//
//	std::vector<std::string> getFiles(){
//		return this->files;
//	}
//};
//
//DirList DirectoryEntries;
//
////void initWidgets()
////{
////
////	/*
////	* Create all the widgets
////	*/
////	label = new gcn::Label("Label");
////
////	image = gcn::Image::load("guisan.png");
////	icon = new gcn::Icon(image);
////	
////
////	button = new gcn::Button("Button");
////	textField = new gcn::TextField("Text field");
////
////	textBox = new gcn::TextBox("Lorem ipsum dolor sit amet consectetur\n"
////		"adipiscing elit Integer vitae ultrices\n"
////		"eros Curabitur malesuada dolor imperdieat\n"
////		"ante facilisis ut convallis sem rutrum\n"
////		"Praesent consequat urna convallis leo\n"
////		"aliquam pellentesque Integer laoreet enim\n"
////		"vehicula libero blandit at pellentesque\n"
////		"ipsum vehicula Mauris id turpis hendrerit\n"
////		"tempor velit nec hendrerit nulla");
////
////	textBoxScrollArea = new gcn::ScrollArea(textBox);
////	textBoxScrollArea->setWidth(270);
////	textBoxScrollArea->setHeight(100);
////	textBoxScrollArea->setBorderSize(50);
////
////	/*listBox = new gcn::ListBox(&demoListModel);
////	listBox->setBorderSize(2);
////	listBox->setSize(200, 500);*/
////
////	/*dropDown = new gcn::DropDown(&demoListModel);*/
////
////	checkBox1 = new gcn::CheckBox("Checkbox 1");
////	checkBox2 = new gcn::CheckBox("Checkbox 2");
////
////	radioButton1 = new gcn::RadioButton("Radio Button 1", "radiogroup", true);
////	radioButton2 = new gcn::RadioButton("Radio Button 2", "radiogroup");
////	radioButton3 = new gcn::RadioButton("Radio Button 3", "radiogroup");
////
////	slider = new gcn::Slider(0, 10);
////	slider->setSize(100, 10);
////
////	window = new gcn::Window("I am a window  Drag me");
////	window->setBaseColor(gcn::Color(212, 255, 150, 190));
////	window->setSize(300, 300);
////	guisanLogoImage = gcn::Image::load("guisan-logo.png");
////	guisanLogoIcon = new gcn::Icon(guisanLogoImage);
////	
////	dropDown->setPosition(0, 0);
////
////	window->add(listBox);
////
////	nestedSlider = new gcn::Slider(0, 10);
////	nestedSlider->setSize(100, 10);
////
////	nestedContainer = new gcn::Container();
////	nestedContainer->setSize(400, 200);
////	nestedContainer->add(listBox, 0, 0);
////	nestedContainer->add(nestedSlider, 50, 70);
////
////	nestedScrollArea = new gcn::ScrollArea(nestedContainer);
////	nestedScrollArea->setSize(180, 90);
////	nestedScrollArea->setBorderSize(1);
////
////	/*
////	* Add them to the top container
////	*/
////	top->add(label, 290, 10);
////	top->add(icon, 10, 10);
////	top->add(button, 325, 10);
////	top->add(textField, 375, 10);
////	top->add(textBoxScrollArea, 290, 50);
////	top->add(listBox, 0, 0);
////	top->add(dropDown, 580, 10);
////	top->add(checkBox1, 580, 50);
////	top->add(checkBox2, 580, 70);
////	top->add(radioButton1, 580, 120);
////	top->add(radioButton2, 580, 140);
////	top->add(radioButton3, 580, 160);
////	top->add(slider, 580, 200);
////	top->add(window, 100, 350);
////	top->add(nestedScrollArea, 440, 350);
////
////
////
////	// Create buttons
////	button1 = new gcn::Button("Button 1");
////	button2 = new gcn::Button("Button 2");
////	// Set the buttons position
////	button1->setPosition(320, 230);
////	button2->setPosition(420, 230);
////	// Add the buttons to the top container
////	top->add(button1);
////	top->add(button2);
////
////	// Create labels
////	label1 = new gcn::Label("Button1 clicks 0");
////	label2 = new gcn::Label("Button2 clicks 0");
////	// Set the labels position
////	label1->setPosition(300, 200);
////	label2->setPosition(400, 200);
////	// Add the labels to the top container
////	top->add(label1);
////	top->add(label2);
////
////
////	// Set the buttons action event id's.
////	button1->setActionEventId("button1");
////	button2->setActionEventId("button2");
////
////	// Make an instance of the ButtonActionListener
////	buttonActionListener = new ButtonActionListener();
////
////	// Add the ButtonActionListener to the buttons action listeners
////	button1->addActionListener(buttonActionListener);
////	button2->addActionListener(buttonActionListener);
////}
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Self-Defined Structs//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//class ListAction : public gcn::ActionListener {
//	void action(const gcn::ActionEvent& actionEvent)
//	{
//
//		for (auto element : DirectoryEntries.getFiles()) {
//
//			if (element == actionEvent.getId())
//				;//registerCommand(Root, CMD_EXIT, EXIT);
//		}
//	}
//};
//
//
//
//
//CHANGESTATE(Demo_OnEnterState)
//{
//	//Init ModulGlobals
//	Root = obj;
//	This = Root->Collection[Root->CurrentStateIndex];
//	This->isInitialized = true;
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////////////////////////////////////////////
//	SDL_FreeSurface(Root->UserInterface_Display);
//	screen = SDL_CreateRGBSurface(0, Root->Width, Root->Height, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);
//	Root->UserInterface_Display = screen;
//	Root->graphics->setTarget(screen);	
//	// Set the top container
//	top = new gcn::Container();
//	top->setDimension(gcn::Rectangle(50, 0, 700, 480));
//
//	top->setOpaque(false);
//
//	Root->UserInterface->setTop(top);
//	
//
//
//	listBox = new gcn::ListBox(&DirectoryEntries);
//	listBox->setSize(200, 500);
//	top->add(listBox);
//
//	ListAction* action = new ListAction;
//	for (auto element : DirectoryEntries.getFiles()) {
//		listBox->setActionEventId(element);
//	}
//
//	listBox->addActionListener(action);
//
//	_Texture = SDL_CreateTextureFromSurface(Root->Renderer, Root->UserInterface_Display);
//	Root->UserInterface_TextureDisplay;
//	
//}
//CHANGESTATE(Demo_OnExitState){
//	obj->Collection[obj->CurrentStateIndex]->isInitialized = false;
//	//destroy Modul Globals
//	Root = NULL;
//	This = NULL;
//}
//CHANGESTATE(Demo_OnPauseState){
//	obj->Collection[obj->CurrentStateIndex]->isActive = false;
//}
//CHANGESTATE(Demo_OnResumeState){
//	obj->Collection[obj->CurrentStateIndex]->isOnPause = false;
//}
//
//TOPROCESS(Demo_Update){
//	// Let the gui perform it's logic (like handle input)
//	Root->UserInterface->logic();
//}
//TOPROCESS(Demo_Input){
//
//	// Poll input
//	//checkInput();
//	SDL_Event e;
//	while (SDL_PollEvent(&e))
//	{
//		//Forwarding Events to GUI
//		Root->input->pushInput(e);
//		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
//		{
//			registerCommand(obj, CMD_EXIT, EXIT);
//		}
//		///////////////////////////////////////////////////////////
//		///////////////////Keyboard////////////////////////////////
//		//////////////////////////////////////////////////////////
//		if (e.type == SDL_KEYDOWN)
//		{
//			switch (e.key.keysym.sym) {
//			case SDLK_r:
//				registerCommand(obj,CMD_RELOAD_MAP, UNKOWN);
//			}
//		}
//		if (e.type == SDL_KEYUP)
//		{
//			
//		}
//		//////////////////////////////////////////////////////////
//		////////////////////Mouse/////////////////////////////////
//		//////////////////////////////////////////////////////////
//		if (e.type == SDL_MOUSEBUTTONDOWN)
//		{
//
//		}
//		if (e.type == SDL_MOUSEBUTTONUP)
//		{
//
//		}
//		if (e.type == SDL_MOUSEMOTION)
//		{
//			SDL_GetMouseState(&obj->MouseX, &obj->MouseX);
//		}
//
//		
//	}
//
//	
//}
//TOPROCESS(Demo_Render){
//
//	// Draw the gui
//	Root->UserInterface->draw();
//	SDL_UpdateTexture(_Texture, NULL, screen->pixels, screen->pitch);
//
//
//
//	SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
//	SDL_RenderClear(obj->Renderer);
//
//
//	
//
//	SDL_RenderCopy(obj->Renderer,_Texture, NULL, NULL);
//
//	//SDL_SetRenderDrawColor(obj->Renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
//
//	/*for (auto tile : Renderables) {
//		re_renderSingleTile(&ExampleMap.mCurrentTileset,
//							te_translateTypeInformation(&ExampleMap.mCurrentTileset,tile.TileType),
//							tile.x,tile.y);
//		SDL_Log("Tilelayerindex: %d | TileType[%d,%s]\n", tile.LayerIndex,tile.TileType, te_translateTypeInformation(&ExampleMap.mCurrentTileset, tile.TileType).c_str());
//	}*/
//
//
//	/*re_renderSingleTile(&ExampleMap.mCurrentTileset, "lava", 300, 300);
//	render(&ExampleMap.mCurrentTileset.Tilesheet, 100, 100, NULL, 45, NULL, SDL_FLIP_NONE);*/
//
//	SDL_RenderPresent(obj->Renderer);
//
//}
//
//
//
//
//
//
//
///////////////////////IMPLEMENTATIONS OF CALLBACKS HERE///////////////////////////////
//COMMAND_CALLBACK(CMD_EXIT) {
//	obj->isRunning = true;
//}
//
//COMMAND_CALLBACK(CMD_TERMINATE_STATE) {
//	Demo_OnExitState(obj);
//}
//
//
//COMMAND_CALLBACK(CMD_RELOAD_MAP) {
//	ExampleMap = te_LoadTileMap(obj, obj->Assets.RessourcePath + rm_getText(obj, "Mapfile"));
//	Renderables = te_createRenderableTiles(obj, &ExampleMap);
//}