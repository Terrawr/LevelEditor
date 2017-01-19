#pragma once
#include "Event.h"
#include <string>

namespace gui {
	/**
	* Listener on events from a Widget. Whenever a widget changes it's
	* size or position the listener of a widget will get notified. To be able to
	* listen for events from a widget you must make a class which inherits
	* from this class and implements it's functions.
	*/
	class  WidgetListener
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~WidgetListener() { }

		/**
		* Invoked when a widget changes its size.
		*
		* @param event Describes the event.
		*/
		virtual void widgetResized(const Event& event) { }

		/**
		* Invoked when a widget is moved.
		*
		* @param event Describes the event.
		*/
		virtual void widgetMoved(const Event& event) { }

		/**
		* Invoked when a widget is hidden, i.e it's set to be
		* not visible.
		*
		* @param event Describes the event.
		*/
		virtual void widgetHidden(const Event& event) { }

		/**
		* Invoked when a widget is shown, i.e it's set to be
		* visible.
		*
		* @param event Describes the event.
		*/
		virtual void widgetShown(const Event& event) { }

	};
}