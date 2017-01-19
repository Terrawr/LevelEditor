#pragma once
namespace gui
{
	class KeyInput;
	class MouseInput;

	class  InputInterface
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~InputInterface() { }

		/**
		* Checks whether the key queue is empty or not.
		*
		* @return true if the key queue is empty.
		*/
		virtual bool isKeyQueueEmpty() = 0;

		/**
		* Dequeues the key input queue.
		*
		* @return key input.
		*/
		virtual KeyInput dequeueKeyInput() = 0;

		/**
		* Checks whether the mouse queue is empyt or not.
		*
		* @return true if the mouse queue is empty.
		*/
		virtual bool isMouseQueueEmpty() = 0;

		/**
		* Dequeues the mouse input queue.
		*
		* @return mouse input.
		*/
		virtual MouseInput dequeueMouseInput() = 0;

		/**
		* Polls all exsisting input. It exists for Input implementation
		* compatibility. It is used internally by the library.
		*/
		virtual void _pollInput() = 0;
	};
}