#pragma once

namespace gui {
	/**
	* Internal class representing mouse input. Generally you won't have to
	* bother using this class as it will get translated into a MouseEvent.
	* The class should be seen as a bridge between the low layer backends
	* providing input and the higher lever parts of the Gui (such as widgets).

	*/
	class MouseInput
	{
	public:

		/**
		* Constructor.
		*/
		MouseInput() { };

		/**
		* Constructor.
		*
		* @param button the button pressed.
		* @param type the type of input.
		* @param x the mouse x coordinate.
		* @param y the mouse y coordinate.
		* @param timeStamp the mouse inputs time stamp.
		*/
		MouseInput(unsigned int button,
			unsigned int type,
			int x,
			int y,
			int timeStamp);

		/**
		* Sets the input type.
		*
		* @param type the type of input.
		*/
		void setType(unsigned int type);

		/**
		* Gets the input type.
		*
		* @return the input type.
		*/
		unsigned int getType() const;

		/**
		* Sets the button pressed.
		*
		* @param button the button pressed.
		*/
		void setButton(unsigned int button);

		/**
		* Gets the button pressed.
		*
		* @return the button pressed.
		*/
		unsigned int getButton() const;

		/**
		* Sets the timestamp for the input.
		*
		* @param timeStamp the timestamp of the input.
		*/
		void setTimeStamp(int timeStamp);

		/**
		* Gets the time stamp of the input.
		*
		* @return the time stamp of the input.
		*/
		int getTimeStamp() const;

		/**
		* Sets the x coordinate of the input.
		*
		* @param x the x coordinate of the input.
		*/
		void setX(int x);

		/**
		* Gets the x coordinate of the input.
		*
		* @return the x coordinate of the input.
		*/
		int getX() const;

		/**
		* Sets the y coordinate of the input.
		*
		* @param y the y coordinate of the input.
		*/
		void setY(int y);

		/**
		* Gets the y coordinate of the input.
		*/
		int getY() const;

		/**
		* Mouse input event types. This enum partially corresponds
		* to the enum with event types in MouseEvent for easy mapping.
		*/
		enum
		{
			MOVED = 0,
			PRESSED,
			RELEASED,
			WHEEL_MOVED_DOWN,
			WHEEL_MOVED_UP
		};

		/**
		* Mouse button types.
		*/
		enum
		{
			EMPTY = 0,
			LEFT,
			RIGHT,
			MIDDLE
		};

	protected:
		unsigned int mType;
		unsigned int mButton;
		int mTimeStamp;
		int mX;
		int mY;
	};
}