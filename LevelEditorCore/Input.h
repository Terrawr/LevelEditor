#pragma once
#include "Event.h"

namespace gui {
	class Input : public Event
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
		*/
		Input(Widget* source,
			bool isShiftPressed,
			bool isControlPressed,
			bool isAltPressed,
			bool isMetaPressed);

		/**
		* Checks whether shift is pressed.
		*
		* @return true if shift was pressed at the same time as the key.
		*/
		bool isShiftPressed() const;

		/**
		* Checks whether control is pressed.
		*
		* @return true if control was pressed at the same time as the key.
		*/
		bool isControlPressed() const;

		/**
		* Checks whether alt is pressed.
		*
		* @return true if alt was pressed at the same time as the key.
		*/
		bool isAltPressed() const;

		/**
		* Checks whether meta is pressed.
		*
		* @return true if meta was pressed at the same time as the key.
		*/
		bool isMetaPressed() const;

		/**
		* Marks the event as consumed. How widgets should act on consumed
		* events are up to the widgets themselves.
		*/
		void consume();

		/**
		* Checks if the input event is consumed.
		*
		* @return true if the input event is consumed, false otherwise.
		*/
		bool isConsumed() const;

	protected:
		bool mShiftPressed;
		bool mControlPressed;
		bool mAltPressed;
		bool mMetaPressed;
		bool mIsConsumed;
	};
}