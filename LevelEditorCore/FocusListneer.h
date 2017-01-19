#pragma once

#include "Event.h"
namespace gui {
	/**
	* Listener of focus events from Widgets. To be able to listen for
	* focus events you must make a class which inherits from this class
	* and implements it's functions.
	*/
	class  FocusListener
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~FocusListener() { }

		/**
		* Called when a widget gains focus.
		*
		* @param event discribes the event.
		*/
		virtual void focusGained(const Event& event) { };

		/**
		* Called when a widget loses focus.
		*
		* @param event discribes the event.
		*/
		virtual void focusLost(const Event& event) { };
	};
}