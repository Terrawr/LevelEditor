#pragma once
#include <string>

#include "ActionEvent.h"

namespace gui {
	/**
	* Listener of action events from Widgets. To be able to
	* listen for actions you must make a class which inherits
	* from this class and implements the action function.
	*
	* @see Widget::addActionListener
	* @author Olof Naessén
	* @author Per Larsson
	*/
	class ActionListener
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~ActionListener() { }

		/**
		* Called when an action is recieved from a Widget. It is used
		* to be able to recieve a notification that an action has
		* occured.
		*
		* @param actionEvent the event of the action.
		* @since 0.6.0
		*/
		virtual void action(const ActionEvent& actionEvent) = 0;

	};
}