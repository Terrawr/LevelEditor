#pragma once
#include <vector>
#include "Event.h"

namespace gui {
	class Widget;

	/**
	* Used to keep track of widget focus. You will probably not have
	* to use the FocusHandler directly to handle focus. Widget has
	* functions for handling focus which uses a FocusHandler. Use them
	* instead.
	*
	* @see Widget::isFocused
	* @see Widget::requestFocus
	* @see Widget::setFocusable
	* @see Widget::isFocusable
	* @see FocusListener
	*/
	class FocusHandler
	{
	public:

		/**
		* Constructor.
		*/
		FocusHandler();

		/**
		* Destructor.
		*/
		virtual ~FocusHandler() { };

		/**
		* Sets focus to a widget. A focus event will also be sent to the widget's
		* focus listeners.
		*
		* @param widget the widget to focus.
		*/
		virtual void requestFocus(Widget* widget);

		/**
		* Sets modal focus to a widget.
		*
		* @param widget the Widget to focus modal.
		* @throws Exception when another widget already has modal focus.
		*/
		virtual void requestModalFocus(Widget* widget);

		/**
		* Releases modal focus if the widget has modal focus.
		* Otherwise nothing will be done.
		*
		* @param widget the Widget to release modal focus for.
		*/
		virtual void releaseModalFocus(Widget* widget);

		/**
		* Sets modal mouse input focus to a widget. Modal mouse input focus means
		* no other widget then the widget with modal mouse input focus will
		* receive mouse input..
		* The widget with modal mouse input focus will also receive mouse input no
		* matter what the mouse input is or where the mouse input occurs.
		*
		* @param widget the widget to focus for modal mouse input focus.
		* @throws Exception when another widget already has modal mouse input focus.
		*/
		virtual void requestModalMouseInputFocus(Widget* widget);

		/**
		* Releases modal mouse input focus if the widget has modal mouse input
		* focus. Otherwise nothing will be done.
		*
		* @param widget the widget to release modal mouse input focus for.
		*/
		virtual void releaseModalMouseInputFocus(Widget* widget);

		/**
		* Gets the widget with focus.
		*
		* @return the Widget with focus. NULL will be returned if
		*         no Widget has focus.
		*/
		virtual Widget* getFocused() const;

		/**
		* Gets the widget with modal focus.
		*
		* @return the Widget with modal focus. NULL will be returned
		*         if no Widget has modal focus.
		*/
		virtual Widget* getModalFocused() const;

		/**
		* Gets the widget with modal mouse input focus.
		*
		* @return the widget with modal mouse input focus. NULL will be returned
		*         if no widget has modal mouse input focus.
		*/
		virtual Widget* getModalMouseInputFocused() const;

		/**
		* Focuses the next Widget. If no Widget has focus the first
		* Widget gets focus. The order in which the Widgets are focused
		* depends on the order you add them to the GUI.
		*/
		virtual void focusNext();

		/**
		* Focuses the previous Widget. If no Widget has focus the first
		* Widget gets focus. The order in which the widgets are focused
		* depends on the order you add them to the GUI.
		*/
		virtual void focusPrevious();

		/**
		* Checks if a Widget is focused.
		*
		* @param widget widget to check if it is focused.
		* @return true if the widget is focused.
		*/
		virtual bool isFocused(const Widget* widget) const;

		/**
		* Adds a widget to the FocusHandler.
		*
		* @param widget the widget to add.
		*/
		virtual void add(Widget* widget);

		/**
		* Removes a widget from the FocusHandler.
		*
		* @param widget the widget to remove.
		*/
		virtual void remove(Widget* widget);

		/**
		* Focuses nothing. A focus event will also be sent to the focused widget's
		* focus listeners if a widget has focus.
		*/
		virtual void focusNone();

		/**
		* Focuses the next Widget which allows tab in unless current focused
		* Widget disallows tab out.
		*/
		virtual void tabNext();

		/**
		* Focuses the previous Widget which allows tab in unless current focused
		* Widget disallows tab out.
		*/
		virtual void tabPrevious();

		/**
		* Gets the widget being dragged.
		*
		* @return the widget being dragged.
		*/
		virtual Widget* getDraggedWidget();

		/**
		* Sets the widget being dragged.
		*
		* @param draggedWidget the widget being dragged.
		*/
		virtual void setDraggedWidget(Widget* draggedWidget);

		/**
		* Gets the last widget with the mouse.
		*
		* @return the last widget with the mouse.
		*/
		virtual Widget* getLastWidgetWithMouse();

		/**
		* Sets the last widget with the mouse.
		*
		* @param lastWidgetWithMouse the last widget with the mouse.
		*/
		virtual void setLastWidgetWithMouse(Widget* lastWidgetWithMouse);

		/**
		* Gets the last widget with modal focus.
		*
		* @return the last widget with modal focus.
		*/
		virtual Widget* getLastWidgetWithModalFocus();

		/**
		* Sets the last widget with modal focus.
		*
		* @param lastWidgetWithModalFocus the last widget with modal focus.
		*/
		virtual void setLastWidgetWithModalFocus(Widget* lastWidgetWithModalFocus);

		/**
		* Gets the last widget with modal mouse input focus.
		*
		* @return the last widget with modal mouse input focus.
		*/
		virtual Widget* getLastWidgetWithModalMouseInputFocus();

		/**
		* Sets the last widget with modal mouse input focus.
		*
		* @param lastMouseWithModalMouseInputFocus  the last widget with modal mouse input focus.
		*/
		virtual void setLastWidgetWithModalMouseInputFocus(Widget* lastWidgetWithModalMouseInputFocus);

		/**
		* Gets the last widget pressed.
		*
		* @return the last widget pressed.
		*/
		virtual Widget* getLastWidgetPressed();

		/**
		* Sets the last widget pressed.
		*
		* @param lastWidgetPressed the last widget pressed.
		*/
		virtual void setLastWidgetPressed(Widget* lastWidgetPressed);

	protected:
		/**
		* Distributes a focus lost event.
		*
		* @param focusEvent the event to distribute.
		* @author Olof Naessén
		* @since 0.7.0
		*/
		virtual void distributeFocusLostEvent(const Event& focusEvent);

		/**
		* Distributes a focus gained event.
		*
		* @param focusEvent the event to distribute.
		* @author Olof Naessén
		* @since 0.7.0
		*/
		virtual void distributeFocusGainedEvent(const Event& focusEvent);

		typedef std::vector<Widget*> WidgetVector;
		typedef WidgetVector::iterator WidgetIterator;
		WidgetVector mWidgets;

		Widget* mFocusedWidget;
		Widget* mModalFocusedWidget;
		Widget* mModalMouseInputFocusedWidget;

		Widget* mDraggedWidget;
		Widget* mLastWidgetWithMouse;
		Widget* mLastWidgetWithModalFocus;
		Widget* mLastWidgetWithModalMouseInputFocus;
		Widget* mLastWidgetPressed;
	};
}