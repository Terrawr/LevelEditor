#pragma once
#include "Key.h"

namespace gui {
	/**
	* Internal class representing keyboard input. Generally you won't have to
	* bother using this class.
	*/
	class  KeyInput
	{
	public:

		/**
		* Constructor.
		*/
		KeyInput() { };

		/**
		* Constructor.
		*
		* @param key the Key the input concerns.
		* @param type the type of input.
		*/
		KeyInput(const Key& key, int type);

		/**
		* Sets the input type.
		*
		* @param type the type of input.
		*/
		void setType(int type);

		/**
		* Gets the input type.
		*
		* @return the input type.
		*/
		int getType() const;

		/**
		* Sets the key the input concerns.
		*
		* @param key the Key the input concerns.
		*/
		void setKey(const Key& key);

		/**
		* Gets the key the input concerns.
		*
		* @return the Key the input concerns.
		*/
		const Key& getKey() const;

		/**
		* Checks whether shift is pressed.
		*
		* @return true if shift was pressed at the same time as the key.
		* 
		*/
		bool isShiftPressed() const;

		/**
		* Sets the shift pressed flag.
		*
		* @param pressed the shift flag value.
		*/
		void setShiftPressed(bool pressed);

		/**
		* Checks whether control is pressed.
		*
		* @return true if control was pressed at the same time as the key.
		* 
		*/
		bool isControlPressed() const;

		/**
		* Sets the control pressed flag.
		*
		* @param pressed the control flag value.
		*/
		void setControlPressed(bool pressed);

		/**
		* Checks whether alt is pressed.
		*
		* @return true if alt was pressed at the same time as the key.
		* 
		*/
		bool isAltPressed() const;

		/**
		* Sets the alt pressed flag.
		*
		* @param pressed the alt flag value.
		*/
		void setAltPressed(bool pressed);

		/**
		* Checks whether meta is pressed.
		*
		* @return true if meta was pressed at the same time as the key.
		*/
		bool isMetaPressed() const;

		/**
		* Sets the meta pressed flag.
		*
		* @param pressed the meta flag value.
		*/
		void setMetaPressed(bool pressed);

		/**
		* Checks whether the key was pressed at the numeric pad.
		*
		* @return true if key pressed at the numeric pad.
		*/
		bool isNumericPad() const;

		/**
		* Sets the numeric pad flag.
		*
		* @param numpad the numeric pad flag value.
		*/
		void setNumericPad(bool numpad);

		/**
		* Key input types. This enum corresponds to the enum with event
		* types on KeyEvent for easy mapping.
		*/
		enum
		{
			PRESSED = 0,
			RELEASED
		};

	protected:
		Key mKey;
		int mType;
		int mButton;
		bool mShiftPressed;
		bool mControlPressed;
		bool mAltPressed;
		bool mMetaPressed;
		bool mNumericPad;
	};
}