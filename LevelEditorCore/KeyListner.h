#pragma once
#include "KeyEvent.h"

namespace gui {
	class Key;

	/**
	* Key listeners base class. Inorder to use this class you must inherit
	* from it and implements it's functions. KeyListeners listen for key
	* events on a Widgets. When a Widget recives a key event, the
	* corresponding function in all it's key listeners will be called.
	* Only focused Widgets will generate key events.
	*
	* @see Widget::addKeyListener
	*/
	class KeyListener
	{
	public:

		/**
		* Destructor
		*/
		virtual ~KeyListener() { }

		/**
		* Called if a key is pressed when the widget has keyboard focus.
		* If a key is held down the widget will generate multiple key
		* presses.
		*
		* @param keyEvent discribes the event.
		*/
		virtual void keyPressed(KeyEvent& keyEvent) { }

		/**
		* Called if a key is released when the widget has keyboard focus.
		*
		* @param keyEvent discribes the event.
		*/
		virtual void keyReleased(KeyEvent& keyEvent) { }

	protected:
		/**
		* Constructor.
		*
		* You should not be able to make an instance of KeyListener,
		* therefore its constructor is protected. To use KeyListener
		* you must inherit from this class and implement it's
		* functions.
		*/
		KeyListener() { }
	};
}