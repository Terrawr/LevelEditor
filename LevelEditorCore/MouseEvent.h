#pragma once
#include "Input.h"

namespace gui {
	class Gui;
	class Widget;

	/**
	* Represents a mouse event.
	*/
	class  MouseEvent : public Input
	{
	public:

		/**
		* Constructor.
		*
		* @param source the source widget of the event.
		* @param isShiftPressed true if shift is pressed, false otherwise.
		* @param isControlPressed true if control is pressed, false otherwise.
		* @param isAltPressed true if alt is pressed, false otherwise.
		* @param isMetaPressed true if meta is pressed, false otherwise.
		* @param the type of the event.
		* @param button the button of the event.
		* @param the x coordinate of the event relative to the source widget.
		* @param the y coordinate of the event relative the source widget.
		*/
		MouseEvent(Widget* source,
			bool isShiftPressed,
			bool isControlPressed,
			bool isAltPressed,
			bool isMetaPressed,
			unsigned int type,
			unsigned int button,
			int x,
			int y,
			int clickCount);

		/**
		* Gets the button of the mouse event.
		*
		* @return the button of the mouse event.
		*/
		unsigned int getButton() const;

		/**
		* Gets the x coordinate of the mouse event. The coordinate is relative to
		* the source Widget.
		*
		* @return the x coordinate of the mouse event.
		*/
		int getX() const;

		/**
		* Gets the y coordinate of the mouse event. The coordinate is relative to
		* the source Widget.
		*
		* @return the y coordinate of the mouse event.
		*/
		int getY() const;

		/**
		* Gets the click count.
		*
		* @return the click count of the mouse event.
		*/
		int getClickCount() const;

		/**
		* Gets the type of the event.
		*
		* @return the type of the event.
		*/
		unsigned int getType() const;

		/**
		* Mouse event types.
		*/
		enum
		{
			MOVED = 0,
			PRESSED,
			RELEASED,
			WHEEL_MOVED_DOWN,
			WHEEL_MOVED_UP,
			CLICKED,
			ENTERED,
			EXITED,
			DRAGGED

		};

		/**
		* Mouse button types.
		*/
		enum
		{
			EMPTY = 0,
			LEFT,
			RIGHT,
			MIDDLE
		};

	protected:
		unsigned int mType;
		unsigned int mButton;
		int mX;
		int mY;
		int mClickCount;

		friend class Gui;
	};
}