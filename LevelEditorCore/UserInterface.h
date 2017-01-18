#pragma once
#include "Texture.h"
#include "LevelEditor.h"
/*
Contains all functions and structs necessary for our
internal User interface.

What needs doing here:
TODO(jojo):
+Implementing Buttons
+Implementing TextInputBoxes
+Implementing TextOutputBoxes
+Implementing PictureBox
+Implementing Toolbar
+implementing Treeview
+implementing 
*/

struct UI_INTERFACEDESCRIPTION;

#define UI_PUBLICFUNCTION(name) void name(UI_INTERFACEDESCRIPTION*,float deltatime)
typedef UI_PUBLICFUNCTION(uiPublic);

typedef struct UI_INTERFACEDESCRIPTION {

	Texture*		DrawingContext;
	int				ID;

	uiPublic*		Render;
	uiPublic*		Update;
	uiPublic*		Input;


}UI;




void UI_initializeUserInterface();
void UI_createWindow(Box);

