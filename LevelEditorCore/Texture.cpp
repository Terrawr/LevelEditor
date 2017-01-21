#include "Texture.h"
#include <stdio.h>
#include <memory.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

//Initializes variables
//
void initilizeTexture(Texture* t, struct SDL_Renderer* render)
{
	//Initialize
	t->mRenderer = render;
	t->mTexture = NULL;
	t->mWidth = 0;
	t->mHeight = 0;
	t->mPixels = NULL;
	t->mPitch = 0;
}

//Deallocates memory
void destroyTexture(Texture* t)
{
	freeTexture(t);
}

//Loads image at specified path
bool loadFromFile(Texture* t, char* path)
{
	//Get rid of preexisting texture
	freeTexture(t);

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
		if (formattedSurface == NULL)
		{
			fprintf(stderr, "Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(t->mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				fprintf(stderr, "Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &t->mPixels, &t->mPitch);

				//Copy loaded/formatted surface pixels
				memcpy(t->mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				t->mWidth = formattedSurface->w;
				t->mHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)t->mPixels;
				int pixelCount = (t->mPitch / 4) * t->mHeight;

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
				t->mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	t->mTexture = newTexture;
	return (t->mTexture != NULL);
}

bool loadFromSurface(Texture* t, SDL_Surface* s) {
	t->mHeight = s->h;
	t->mWidth = s->w;
	t->mPitch = s->pitch;
	t->mPixels = NULL;
	t->mTexture = SDL_CreateTextureFromSurface(t->mRenderer, s);

	return (t->mTexture != NULL);
}

//#ifdef _SDL_TTF_H
//Creates image from font string
bool loadFromRenderedText(Texture* t,TTF_Font* font, char* textureText, SDL_Color textColor) {
	//Get rid of preexisting texture
	freeTexture(t);

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText, textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		t->mTexture = SDL_CreateTextureFromSurface(t->mRenderer, textSurface);
		if (t->mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			t->mWidth = textSurface->w;
			t->mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return (t->mTexture != NULL);
}
//#endif

//Creates blank texture
bool createBlank(Texture* t, int width, int height, SDL_TextureAccess access) {
	//Create uninitialized texture
	t->mTexture = SDL_CreateTexture(t->mRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
	if (t->mTexture == NULL)
	{
		fprintf(stderr, "Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		t->mWidth = width;
		t->mHeight = height;
	}

	return (t->mTexture != NULL);
}

//Deallocates texture
void freeTexture(Texture* t) {
	//Free texture if it exists
	if (t->mTexture != NULL)
	{
		SDL_DestroyTexture(t->mTexture);
		t->mTexture = NULL;
		t->mWidth = 0;
		t->mHeight = 0;
		t->mPixels = NULL;
		t->mPitch = 0;
	}
}

//Set color modulation
void setColor(Texture* t, Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(t->mTexture, red, green, blue);
}

//Set blending
void setBlendMode(Texture*t, SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(t->mTexture, blending);
}

//Set alpha modulation
void setAlpha(Texture* t, Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(t->mTexture, alpha);
}

//Renders texture at given point
void render(Texture* t, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, t->mWidth, t->mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (t->mTexture == NULL) {
		SDL_Log("Texture cannot be drawn, you idiot\n");
	}

	//Render to screen
	SDL_RenderCopyEx(t->mRenderer, t->mTexture, clip, &renderQuad, angle, center, flip);
}

//Set self as render target
void setAsRenderTarget(Texture* t) {
	//Make self render target
	SDL_SetRenderTarget(t->mRenderer, t->mTexture);
}

//Gets image dimensions
int getWidth(Texture* t) {
	return t->mWidth;
}
int getHeight(Texture* t) {
	return t->mHeight;
}

//Pixel manipulators
SDL_bool lockTexture(Texture* t) {
	SDL_bool success = SDL_TRUE;

	//Texture is already locked
	if (t->mPixels != NULL)
	{
		printf("Texture is already locked!\n");
		success = SDL_FALSE;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(t->mTexture, NULL, &t->mPixels, &t->mPitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = SDL_FALSE;
		}
	}

	return success;
}

SDL_bool unlockTexture(Texture* t)
{
	SDL_bool success = SDL_TRUE;

	//Texture is not locked
	if (t->mPixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = SDL_FALSE;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(t->mTexture);
		t->mPixels = NULL;
		t->mPitch = 0;
	}

	return success;
}
void* getPixels(Texture* t) {
	return t->mPixels;
}
void copyPixels(Texture* t, void* pixels) {
	//Texture is locked
	if (t->mPixels != NULL)
	{
		//Copy to locked pixels
		memcpy(t->mPixels, pixels, t->mPitch * t->mHeight);
	}
}

int getPitch(Texture* t)
{
	return t->mPitch;
}
Uint32 getPixel32(Texture* t, unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)t->mPixels;

	//Get the pixel requested
	return pixels[(y * (t->mPitch / 4)) + x];
}