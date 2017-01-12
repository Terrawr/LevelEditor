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
	}Texture;

	//Initializes variables
	void initilizeTexture(Texture*t, SDL_Renderer* render);

	//Deallocates memory
	void destroyTexture(Texture*);

	//Loads image at specified path
	bool loadFromFile(Texture* t, char* path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Creates blank texture
	bool createBlank(Texture* t, int width, int height, SDL_TextureAccess);

	//Deallocates texture
	void freeTexture(Texture* t);

	//Set color modulation
	void setColor(Texture* t, Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(Texture*t, SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Texture* t, Uint8 alpha);

	//Renders texture at given point
	//struct texture* t, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
	void render(Texture* t, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	//Set self as render target
	void setAsRenderTarget(Texture* t);

	//Gets image dimensions
	int getWidth(Texture* t);
	int getHeight(Texture* t);

	//Pixel manipulators
	SDL_bool lockTexture(Texture* t);
	SDL_bool unlockTexture(Texture* t);
	void* getPixels(Texture* t);
	void copyPixels(Texture* t, void* pixels);
	int getPitch(Texture* t);
	Uint32 getPixel32(Texture* t, unsigned int x, unsigned int y);

#ifdef __cplusplus
}
#endif