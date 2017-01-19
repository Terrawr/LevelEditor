#pragma once

#include "MouseEvent.h"

namespace gui {
	/**
	* Mouse listeners base class. Inorder to use this class you must inherit
	* from it and implements it's functions. MouseListeners listen for mouse
	* events on a Widgets. When a Widget recives a mouse event, the
	* corresponding function in all it's mouse listeners will be called.
	*
	* @see Widget::addMouseListener
	*/
	class MouseListener
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~MouseListener() { }

		/**
		* Called when the mouse has entered into the widget area.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseEntered(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when the mouse has exited the widget area.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseExited(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when a mouse button has been pressed on the widget area.
		*
		* NOTE: A mouse press is NOT equal to a mouse click.
		*       Use mouseClickMessage to check for mouse clicks.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mousePressed(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when a mouse button has been released on the widget area.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseReleased(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when a mouse button is pressed and released (clicked) on
		* the widget area.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseClicked(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when the mouse wheel has moved up on the widget area.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseWheelMovedUp(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when the mouse wheel has moved down on the widget area.
		*
		* @param mousEvent describes the event.
		*/
		virtual void mouseWheelMovedDown(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when the mouse has moved in the widget area and no mouse button
		* has been pressed (i.e no widget is being dragged).
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseMoved(MouseEvent& mouseEvent)
		{

		}

		/**
		* Called when the mouse has moved and the mouse has previously been
		* pressed on the widget.
		*
		* @param mouseEvent describes the event.
		*/
		virtual void mouseDragged(MouseEvent& mouseEvent)
		{

		}

	protected:
		/**
		* Constructor.
		*
		* You should not be able to make an instance of MouseListener,
		* therefore its constructor is protected. To use MouseListener
		* you must inherit from this class and implement it's
		* functions.
		*/
		MouseListener() { }
	};
}