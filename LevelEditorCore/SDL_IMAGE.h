#pragma once
#include "Color.h"
#include "Image.h"
#include <SDL.h>
#include <string>


namespace gui {

	/**
	* SDL implementation of Image.
	*/
	class SDLImage : public Image
	{
	public:
		/**
		* Constructor. Load an image from an SDL surface.
		*
		* NOTE: The functions getPixel and putPixel are only guaranteed to work
		*       before an image has been converted to display format.
		*
		* @param surface the surface from which to load.
		* @param autoFree true if the surface should automatically be deleted.
		*/
		SDLImage(SDL_Texture* surface, bool autoFree);

		/**
		* Destructor.
		*/
		virtual ~SDLImage();

		/**
		* Gets the SDL surface for the image.
		*
		* @return the SDL surface for the image.
		*/
		virtual SDL_Texture* getSurface() const;


		// Inherited from Image

		virtual void free();

		virtual int getWidth() const;

		virtual int getHeight() const;

		/*virtual Color getPixel(int x, int y);

		virtual void putPixel(int x, int y, const Color& color);
*/
		

	protected:
		SDL_Texture* mSurface;
		int w, h;
		bool mAutoFree;
	};

}