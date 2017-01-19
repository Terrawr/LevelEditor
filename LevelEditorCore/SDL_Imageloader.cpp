#include "SDL_ImageLoader.h"
#include "SDL_IMAGE.h"
#include "Exception.h"

#include <SDL_image.h>


namespace gui {
	Image* SDLImageLoader::load(const std::string& filename, bool convertToDisplayFormat)
	{
		SDL_Surface *loadedSurface = loadSDLSurface(filename);
		SDL_Texture* newTexture = NULL;
		int w = 0, h = 0, pitch = 0;
		void* pix;

		if (loadedSurface == NULL)
		{
			throw GUI_EXCEPTION(
				std::string("Unable to load image file: ") + filename);
		}

		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
		if (formattedSurface == NULL)
		{
			fprintf(stderr, "Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(this->mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				fprintf(stderr, "Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &pix, &pitch);

				//Copy loaded/formatted surface pixels
				memcpy(pix, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				w = formattedSurface->w;
				h = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)pix;
				int pixelCount = (pitch / 4) * h;

				//Map colors				
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				//t->mPixels = NULL;
			}

			if (convertToDisplayFormat)
			{
				//image->convertToDisplayFormat();
			}

			SDL_Texture* tex = SDL_CreateTextureFromSurface(this->mRenderer, formattedSurface);
			Image *image = new SDLImage(tex, true);

			if (tex == NULL)
			{
				throw GUI_EXCEPTION(
					std::string("Not enough memory to load: ") + filename);
			}


			SDL_FreeSurface(formattedSurface);
			SDL_FreeSurface(loadedSurface);
			return image;
		}
	}

	SDL_Surface* SDLImageLoader::loadSDLSurface(const std::string& filename)
	{
		return IMG_Load(filename.c_str());
	}

	SDL_Surface* SDLImageLoader::convertToStandardFormat(SDL_Surface* surface)
	{
		Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
#endif

		SDL_Surface *colorSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
			0, 0, 32,
			rmask, gmask, bmask, amask);

		SDL_Surface *tmp = NULL;

		if (colorSurface != NULL)
		{
			tmp = SDL_ConvertSurface(surface, colorSurface->format,
				SDL_SWSURFACE);
			SDL_FreeSurface(colorSurface);
		}

		return tmp;
	}
}