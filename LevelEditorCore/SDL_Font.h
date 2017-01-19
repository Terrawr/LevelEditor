#pragma once

#include <map>
#include <string>
#include <SDL_ttf.h>

#include "Font.h"

namespace gui {

	class Graphics;

	/**
	* SDL True Type Font implementation of Font. It uses the SDL_ttf library
	* to display True Type Fonts with SDL.
	*
	* NOTE: You must initialize the SDL_ttf library before using this
	*       class. Also, remember to call the SDL_ttf libraries quit
	*       function.
	*
	* @author Walluce Pinkham
	* @author Olof Naessén
	*/
	class SDLTrueTypeFont : public Font
	{
	public:

		/**
		* Constructor.
		*
		* @param filename the filename of the True Type Font.
		* @param size the size the font should be in.
		*/
		SDLTrueTypeFont(const std::string& filename, int size);

		/**
		* Destructor.
		*/
		virtual ~SDLTrueTypeFont();

		/**
		* Sets the spacing between rows in pixels. Default is 0 pixels.
		* The spacing can be negative.
		*
		* @param spacing the spacing in pixels.
		*/
		virtual void setRowSpacing(int spacing);

		/**
		* Gets the spacing between rows in pixels.
		*
		* @return the spacing.
		*/
		virtual int getRowSpacing();

		/**
		* Sets the spacing between letters in pixels. Default is 0 pixels.
		* The spacing can be negative.
		*
		* @param spacing the spacing in pixels.
		*/
		virtual void setGlyphSpacing(int spacing);

		/**
		* Gets the spacing between letters in pixels.
		*
		* @return the spacing.
		*/
		virtual int getGlyphSpacing();

		/**
		* Sets the use of anti aliasing..
		*
		* @param antaAlias true for use of antia aliasing.
		*/
		virtual void setAntiAlias(bool antiAlias);

		/**
		* Checks if anti aliasing is used.
		*
		* @return true if anti aliasing is used.
		*/
		virtual bool isAntiAlias();


		// Inherited from Font

		virtual int getWidth(const std::string& text) const;

		virtual int getHeight() const;

		virtual void drawString(Graphics* graphics, const std::string& text, int x, int y);

	protected:
		TTF_Font *mFont;

		int mHeight;
		int mGlyphSpacing;
		int mRowSpacing;

		std::string mFilename;
		bool mAntiAlias;
	};

}