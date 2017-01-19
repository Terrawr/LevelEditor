#pragma once
#include "Input.h"
#include "Key.h"

namespace gui {


	class Widget;
	class  KeyEvent : public Input
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
		* @param type the type of the event.
		* @param isNumericPad true if the event occured on the numeric pad,
		*                     false otherwise.
		* @param key represents the key of the event.
		*/
		KeyEvent(Widget* source,
			bool isShiftPressed,
			bool isControlPressed,
			bool isAltPressed,
			bool isMetaPressed,
			unsigned int type,
			bool isNumericPad,
			const Key& key);

		/**
		* Destructor.
		*/
		virtual ~KeyEvent();

		/**
		* Gets the type of the event.
		*
		* @return the type of the event.
		*/
		unsigned int getType() const;

		/**
		* Checks whether the key event occured on the numeric pad.
		*
		* @return true if key event occured on the numeric pad.
		*/
		bool isNumericPad() const;

		/**
		* Gets the key of the event.
		*
		* @return the key of the event.
		*/
		const Key& getKey() const;

		/**
		* Key event types.
		*/
		enum
		{
			PRESSED = 0,
			RELEASED
		};

	protected:
		unsigned int mType;
		bool mIsNumericPad;
		Key mKey;
	};

}