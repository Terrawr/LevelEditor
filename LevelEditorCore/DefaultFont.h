#pragma once

#include "Font.h"

namespace gui {

	/**
	* A font only capable of drawing rectangles. It is used by default
	* merely to show that no font have been set.
	*/
	class DefaultFont : public Font
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~DefaultFont() {}

		/**
		* Draws a glyph as a rectangle. The glyphs always be drawn as
		* rectangles no matter the glyph.
		*
		* NOTE: You normally won't use this function to draw text since
		*       the Graphics class contains better functions for drawing
		*       text.
		*
		* @param graphics a Graphics object to be used for drawing.
		* @param glyph a glyph to draw.
		* @param x the x coordinate where to draw the glyph.
		* @param y the y coordinate where to draw the glyph.
		* @return the width of the glyph in pixels.
		*/
		virtual int drawGlyph(Graphics* graphics, unsigned char glyph, int x, int y);


		// Inherited from Font

		virtual void drawString(Graphics* graphics, const std::string& text, int x, int y);

		virtual int getWidth(const std::string& text) const;

		virtual int getHeight() const;

		virtual int getStringIndexAt(const std::string& text, int x);
	};

}