#include "Input.h"

namespace gui {
	Input::Input(Widget* source,
		bool isShiftPressed,
		bool isControlPressed,
		bool isAltPressed,
		bool isMetaPressed)
		:Event(source),
		mShiftPressed(isShiftPressed),
		mControlPressed(isControlPressed),
		mAltPressed(isAltPressed),
		mMetaPressed(isMetaPressed),
		mIsConsumed(false)
	{

	}

	bool Input::isShiftPressed() const
	{
		return mShiftPressed;
	}

	bool Input::isControlPressed() const
	{
		return mControlPressed;
	}

	bool Input::isAltPressed() const
	{
		return mAltPressed;
	}

	bool Input::isMetaPressed() const
	{
		return mMetaPressed;
	}

	void Input::consume()
	{
		mIsConsumed = true;
	}

	bool Input::isConsumed() const
	{
		return mIsConsumed;
	}
}