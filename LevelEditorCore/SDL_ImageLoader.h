#pragma once
#include "ImageLoader.h"
#include <SDL.h>

namespace gui {


	class Image;

	/**
	* SDL implementation of ImageLoader.
	*/
	class SDLImageLoader : public ImageLoader
	{
	public:

		// Inherited from ImageLoader

		virtual Image* load(const std::string& filename, bool convertToDisplayFormat = true);
		virtual void setRenderer(SDL_Renderer* ren) { this->mRenderer = ren; }
	protected:
		virtual SDL_Surface* loadSDLSurface(const std::string& filename);
		virtual SDL_Surface* convertToStandardFormat(SDL_Surface* surface);
	
	
		SDL_Renderer* mRenderer;
	};

}