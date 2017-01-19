#pragma once
#include <queue>

#include "InterfaceInput.h"
#include "MouseInput.h"
#include "KeyInput.h"

namespace gui {
	class Key;
	/**
	* Generic input which can be used with any backend.
	*/
	class GenericInput : public InputInterface
	{
	public:

		/**
		* Constructor.
		*/
		GenericInput();

		/**
		* Pushes a key pressed event.
		*
		* NOTE: If a special key is pressed, like the F1 key,
		*       the corresponding Guichan key value found
		*       in the enum in Key should be pushed as the
		*       unicode value.
		*
		* @param unicode the unicode value of the key.
		*/
		void pushKeyPressed(int unicode);

		/**
		* Pushes a key released event.
		*
		* NOTE: If a special key is pressed, like the F1 key,
		*       the corresponding Guichan key value found
		*       in the enum in Key should be pushed as the
		*       unicode value.
		*
		* @param unicode the unicode value of the key.
		*/
		void pushKeyReleased(int unicode);

		/**
		* Pushes a mouse button pressed event.
		*
		* @param x the x coordinate of the mouse event.
		* @param y the y coordinate of the mouse event.
		* @param button the button of the mouse event.
		*/
		void pushMouseButtonPressed(int x, int y, int button);

		/**
		* Pushes a mouse button released event.
		*
		* @param x the x coordinate of the mouse event.
		* @param y the y coordinate of the mouse event.
		* @param button the button of the mouse event.
		*/
		void pushMouseButtonReleased(int x, int y, int button);

		/**
		* Pushes a mouse wheel moved up event.
		*
		* @param x the x coordinate of the mouse event.
		* @param y the y coordinate of the mouse event.
		*/
		void pushMouseWheelMovedUp(int x, int y);

		/**
		* Pushes a mouse wheel moved down event.
		*
		* @param x the x coordinate of the mouse event.
		* @param y the y coordinate of the mouse event.
		*/
		void pushMouseWheelMovedDown(int x, int y);

		/**
		* Pushes a mouse moved event.
		*
		* @param x the x coordinate of the mouse event.
		* @param y the y coordinate of the mouse event.
		*/
		void pushMouseMoved(int x, int y);


		// Inherited from Input

		virtual bool isKeyQueueEmpty();

		virtual KeyInput dequeueKeyInput();

		virtual bool isMouseQueueEmpty();

		virtual MouseInput dequeueMouseInput();

		virtual void _pollInput();

	protected:
		std::queue<KeyInput> mKeyInputQueue;
		std::queue<MouseInput> mMouseInputQueue;
	};
}