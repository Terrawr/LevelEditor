#include "SDL_IMAGE.h"
#include "Exception.h"

namespace gui {


	SDLImage::SDLImage(SDL_Texture* surface, bool autoFree)
	{
		mAutoFree = autoFree;
		mSurface = surface;

		if (surface != NULL) {
			SDL_QueryTexture(surface, NULL, NULL, &this->w, &this->h);
		}
	}

	SDLImage::~SDLImage()
	{
		if (mAutoFree)
		{
			free();
		}
	}

	SDL_Texture* SDLImage::getSurface() const
	{
		return mSurface;
	}

	int SDLImage::getWidth() const
	{
		if (mSurface == NULL)
		{
			throw GUI_EXCEPTION("Trying to get the width of a non loaded image.");
		}

		return w;
	}

	int SDLImage::getHeight() const
	{
		if (mSurface == NULL)
		{
			throw GUI_EXCEPTION("Trying to get the height of a non loaded image.");
		}

		return h;
	}

	/*Color SDLImage::getPixel(int x, int y)
	{
		if (mSurface == NULL)
		{
			throw GUI_EXCEPTION("Trying to get a pixel from a non loaded image.");
		}

		
		return SDLgetPixel(mSurface, x, y);
	}*/

	/*void SDLImage::putPixel(int x, int y, const Color& color)
	{
		if (mSurface == NULL)
		{
			throw GUI_EXCEPTION("Trying to put a pixel in a non loaded image.");
		}

		SDLputPixel(mSurface, x, y, color);
	}*/

	

	void SDLImage::free()
	{
		SDL_DestroyTexture(this->mSurface);
	}

}