#pragma once
#include "Event.h"

namespace gui {
	class Widget;

	/**
	* Represents a selection event.
	*/
	class  SelectionEvent : public Event
	{
	public:

		/**
		* Constructor.
		*
		* @param source the source widget of the event.
		*/
		SelectionEvent(Widget* source);

		/**
		* Destructor.
		*/
		virtual ~SelectionEvent();
	};
}