#pragma once
#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct GPU_TEXTURE {

		struct SDL_Texture* mTexture;
		struct SDL_Renderer* mRenderer;

		//Raw image data
		void* mPixels;
		int mPitch;

		int mWidth;
		int mHeight;
	}texture;

	//Initializes variables
	void initilizeTexture(texture*t, SDL_Renderer* render);

	//Deallocates memory
	void destroyTexture(texture*);

	//Loads image at specified path
	bool loadFromFile(texture* t, char* path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Creates blank texture
	bool createBlank(texture* t, int width, int height, SDL_TextureAccess);

	//Deallocates texture
	void freeTexture(texture* t);

	//Set color modulation
	void setColor(texture* t, Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(texture*t, SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(texture* t, Uint8 alpha);

	//Renders texture at given point
	//struct texture* t, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
	void render(texture* t, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	//Set self as render target
	void setAsRenderTarget(texture* t);

	//Gets image dimensions
	int getWidth(texture* t);
	int getHeight(texture* t);

	//Pixel manipulators
	SDL_bool lockTexture(texture* t);
	SDL_bool unlockTexture(texture* t);
	void* getPixels(texture* t);
	void copyPixels(texture* t, void* pixels);
	int getPitch(texture* t);
	Uint32 getPixel32(texture* t, unsigned int x, unsigned int y);

#ifdef __cplusplus
}
#endif