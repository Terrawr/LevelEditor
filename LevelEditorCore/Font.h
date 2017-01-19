#pragma once
#include <string>

namespace gui {

	class Graphics;

	/**
	* Holder of a font. Fonts should inherit from this class and
	* implements it's functions.
	*
	* @see ImageFont
	*/
	class Font
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~Font() { }

		/**
		* Gets the width of a string. The width of a string is not necesserily
		* the sum of all the widths of it's glyphs.
		*
		* @param text the string to return the width of.
		* @return the width of a string.
		*/
		virtual int getWidth(const std::string& text) const = 0;

		/**
		* Gets the height of the glyphs in the font.
		*
		* @return the height of the glyphs int the font.
		*/
		virtual int getHeight() const = 0;

		/**
		* Gets a string index in a string providing an x coordinate.
		* Used to retrive a string index (for a character in a
		* string) at a certain x position. It is especially useful
		* when a mouse clicks in a TextField and you want to know which
		* character was clicked.
		*
		* @return a string index in a string providing an x coordinate.
		*/
		virtual int getStringIndexAt(const std::string& text, int x);

		/**
		* Draws a string.
		*
		* NOTE: You normally won't use this function to draw text since
		*       Graphics contains better functions for drawing text.
		*
		* @param graphics a Graphics object to use for drawing.
		* @param text the string to draw.
		* @param x the x coordinate where to draw the string.
		* @param y the y coordinate where to draw the string.
		*/
		virtual void drawString(Graphics* graphics, const std::string& text,
			int x, int y) = 0;
	};

}