#pragma once
#include "Rectangle.h"

namespace gui {


	/**
	* A rectangle used when dealing with clipping. It is a regular
	* Rectangle extended with variables for x offsets and y offsets.
	*/
	class ClipRectangle : public Rectangle
	{
	public:

		/**
		* Constructor.
		*/
		ClipRectangle();

		/**
		* Constructor.
		*
		* @param x the rectangle x coordinate.
		* @param y the rectangle y coordinate.
		* @param width the rectangle width.
		* @param height the rectangle height.
		* @param xOffset origin of drawing (used by Graphics).
		* @param yOffset origin of drawing (used by Graphics) .
		*/
		ClipRectangle(int x, int y, int width, int height,
			int xOffset, int yOffset);

		/**
		* Copies x, y, width and height field from a Rectangle.
		*
		* @param other the Rectangle to copy from.
		* @returns a ClipRectangle.
		*/
		const ClipRectangle& operator=(const Rectangle& other);

		/**
		* x-origin of drawing (used by Graphics).
		*/
		int xOffset;

		/**
		* y-origin of drawing (used by Graphics).
		*/
		int yOffset;
	};


}