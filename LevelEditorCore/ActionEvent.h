#pragma once
#include <string>
#include "Event.h"

namespace gui {
	class Widget;

	/**
	* Represents an action event.
	*
	* @author Olof Naessén
	* @since 0.6.0
	*/
	class ActionEvent : public Event
	{
	public:

		/**
		* Constructor.
		*
		* @param source the source widget of the event.
		* @param id the identifier of the event.
		*/
		ActionEvent(Widget* source, const std::string& id);

		/**
		* Destructor.
		*/
		virtual ~ActionEvent();

		/**
		* Gets the id of the event.
		*
		* @return the id of the event.
		*/
		const std::string& getId() const;

	protected:
		std::string mId;
	};
}