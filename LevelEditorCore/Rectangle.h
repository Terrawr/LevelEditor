#pragma once

namespace gui {

	/**
	* Represents a rectangle.
	*/
	class Rectangle
	{
	public:

		/**
		* Constructor. Resets member variables.
		*/
		Rectangle();

		/**
		* Constructor.
		*
		* @param x the Rectangle x coordinate.
		* @param y the Rectangle y coordinate.
		* @param width the Rectangle width.
		* @param height the Rectangle height.
		*/
		Rectangle(int x, int y, int width, int height);

		/**
		* Sets the dimension of a rectangle.
		*
		* @param x the Rectangle x coordinate.
		* @param y the Rectangle y coordinate.
		* @param width the Rectangle width.
		* @param height the Rectangle height.
		*/
		void setAll(int x, int y, int width, int height);

		/**
		* Checks if another Rectangle intersects with the Rectangle.
		*
		* @param rectangle another Rectangle.
		*/
		bool intersect(const Rectangle& rectangle);

		/**
		* Checks if a point is inside the Rectangle.
		*
		* @param x the point x coordinate.
		* @param y the point y coordinate.
		*/
		bool isPointInRect(int x, int y) const;

		int x;
		int y;
		int width;
		int height;
	};

}