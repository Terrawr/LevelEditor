#pragma once
#include "LevelEditor.h"
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

/////////////////////WARNING PURE C++ CODE /////////////////////////////////////////

