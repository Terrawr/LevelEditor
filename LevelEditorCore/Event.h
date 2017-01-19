#pragma once
namespace gui {
	class Widget;
	class Event
	{
	public:

		/**
		* Constructor.
		*
		* @param source the source widget of the event.
		*/
		Event(Widget* source);

		/**
		* Destructor.
		*/
		virtual ~Event();

		/**
		* Gets the source widget of the event.
		*
		* @return the source widget of the event.
		*/
		Widget* getSource() const;


	protected:
		Widget* mSource;
		unsigned int mType;
	};
}