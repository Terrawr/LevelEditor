#pragma once

namespace gui {
	class Key
	{
	public:

		/**
		* Constructor.
		*
		* @param value the ascii or enum value for the key.
		*/
		Key(int value = 0);

		/**
		* Checks whether a key is a character.
		*
		* @return true if the key is a letter, number or whitespace.
		*/
		bool isCharacter() const;

		/**
		* Checks whether a key is a number.
		*
		* @return true if the key is a number (0-9).
		*/
		bool isNumber() const;

		/**
		* Checks whether a key is a letter.
		*
		* @return true if the key is a letter (a-z,A-Z).
		*/
		bool isLetter() const;

		/**
		* Gets the value of the key. If an ascii value exists it will be
		* returned. Otherwise an enum value will be returned.
		*
		* @return the value of the key.
		*/
		int getValue() const;

		/**
		* An enum with key values.
		*/
		enum
		{
			SPACE = ' ',
			TAB = '\t',
			ENTER = '\n',
			LEFT_ALT = 1000,
			RIGHT_ALT,
			LEFT_SHIFT,
			RIGHT_SHIFT,
			LEFT_CONTROL,
			RIGHT_CONTROL,
			LEFT_META,
			RIGHT_META,
			LEFT_SUPER,
			RIGHT_SUPER,
			INSERT,
			HOME,
			PAGE_UP,
			DELETE,
			END,
			PAGE_DOWN,
			ESCAPE,
			CAPS_LOCK,
			BACKSPACE,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			PRINT_SCREEN,
			SCROLL_LOCK,
			PAUSE,
			NUM_LOCK,
			ALT_GR,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

	protected:
		int mValue;
	};
}