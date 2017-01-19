#include "ActionEvent.h"
namespace gui {

	ActionEvent::ActionEvent(Widget* source, const std::string& id)
		:Event(source),
		mId(id)
	{

	}

	ActionEvent::~ActionEvent()
	{

	}

	const std::string& ActionEvent::getId() const
	{
		return mId;
	}
}