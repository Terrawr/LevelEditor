#pragma once
#include <SDL.h>
#include <queue>

#include "InterfaceInput.h"
#include "KeyInput.h"
#include "MouseInput.h"

namespace gui {
	class Key;

	/**
	* SDL implementation of Input.
	*/
	class SDLInput : public InputInterface
	{
	public:

		/**
		* Constructor.
		*/
		SDLInput();

		/**
		* Pushes an SDL event. It should be called at least once per frame to
		* update input with user input.
		*
		* @param event an event from SDL.
		*/
		virtual void pushInput(SDL_Event event);

		/**
		* Polls all input. It exists for input driver compatibility. If you
		* only use SDL and plan sticking with SDL you can safely ignore this
		* function as it in the SDL case does nothing.
		*/
		virtual void _pollInput() { }


		// Inherited from Input

		virtual bool isKeyQueueEmpty();

		virtual KeyInput dequeueKeyInput();

		virtual bool isMouseQueueEmpty();

		virtual MouseInput dequeueMouseInput();

	protected:
		/**
		* Converts a mouse button from SDL to a Guichan mouse button
		* representation.
		*
		* @param button an SDL mouse button.
		* @return a Guichan mouse button.
		*/
		int convertMouseButton(int button);

		/**
		* Converts an SDL event key to a key value.
		*
		* @param event an SDL event with a key to convert.
		* @return a key value.
		* @see Key
		*/
		int convertKeyCharacter(SDL_Event event);

		std::queue<KeyInput> mKeyInputQueue;
		std::queue<MouseInput> mMouseInputQueue;

		bool mMouseDown;
		bool mMouseInWindow;
	};
}