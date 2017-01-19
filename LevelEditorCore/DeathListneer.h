#pragma once
#include "Event.h"

namespace gui {

	/**
	* Listener of death events from Widgets. To be able to
	* listen for deaths you must make a class which inherits
	* from this class and implements the death function.
	*
	* @see Widget::addDeathListener
	* @author Olof Naessén
	* @since 0.6.0
	*/
	class DeathListener
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~DeathListener() { }

		/**
		* Called when a widget dies. It is used to be able to recieve
		* a notification when a death of a widget occurs.
		*
		* @param event the event of the death.
		*/
		virtual void death(const Event& event) = 0;

	};
}