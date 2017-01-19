#pragma once
#include "SelectEvent.h"

namespae gui{

	/**
	* Listener of value change events from Widgets. To be able to
	* listen for value changes you must make a class which inherits
	* from this class and implements the valueChanged function.
	*
	* @see ListBox::addSelectionListener
	* @author Olof Naessén
	* @since 0.8.0
	*/
	class  SelectionListener
{
public:

	/**
	* Destructor.
	*/
	virtual ~SelectionListener() { }

	/**
	* Called when a value has been changed in a Widget. It is used
	* to be able to recieve a notification that a value has been changed.
	*
	* @param event the event of the value change.
	* @since 0.8.0
	*/
	virtual void valueChanged(const SelectionEvent& event) { };

};

}