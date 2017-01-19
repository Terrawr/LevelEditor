#include "Event.h"
namespace gui {
	Event::Event(Widget* source)
		:mSource(source)
	{

	}

	Event::~Event()
	{

	}

	Widget* Event::getSource() const
	{
		return mSource;
	}
}