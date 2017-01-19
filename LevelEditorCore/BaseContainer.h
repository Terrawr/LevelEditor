#pragma once
#include "DeathListneer.h"
#include "Widget.h"

namespace gui {
	/**
	* Implements basic container behaviour. Most container will suffice by
	* inheriting from this class.
	*
	* @see Container
	*/
	class  BasicContainer : public Widget, public DeathListener
	{
	public:
		/**
		* Destructor
		*/
		virtual ~BasicContainer();


		// Inherited from Widget

		virtual void moveToTop(Widget* widget);

		virtual void moveToBottom(Widget* widget);

		virtual Rectangle getChildrenArea();

		virtual void focusNext();

		virtual void focusPrevious();

		virtual void logic();

		virtual void _setFocusHandler(FocusHandler* focusHandler);

		void setInternalFocusHandler(FocusHandler* focusHandler);

		virtual void showWidgetPart(Widget* widget, Rectangle area);

		virtual Widget *getWidgetAt(int x, int y);


		// Inherited from DeathListener

		virtual void death(const Event& event);

	protected:
		/**
		* Adds a widget to the basic container.
		*
		* @param widget the widget to add.
		*/
		void add(Widget* widget);

		/**
		* Removes a widget from the basic container.
		*
		* @param widget the widget to remove.
		*/
		virtual void remove(Widget* widget);

		/**
		* Clears the basic container from all widgets.
		*/
		virtual void clear();

		/**
		* Draws children widgets.
		*
		* @param graphics a Graphics object to draw with.
		*/
		virtual void drawChildren(Graphics* graphics);

		/**
		* Calls logic for children widgets.
		*/
		virtual void logicChildren();

		/**
		* Finds a widget given an id.
		*
		* @param id the id to find a widget by.
		* @return the widget with the corrosponding id,
		NULL of no widget is found.
		*/
		virtual Widget* findWidgetById(const std::string& id);

		typedef std::list<Widget *> WidgetList;
		typedef WidgetList::iterator WidgetListIterator;
		typedef WidgetList::reverse_iterator WidgetListReverseIterator;

		WidgetList mWidgets;
	};
}