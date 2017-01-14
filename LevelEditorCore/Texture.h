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

	///
	/// \fn    initilizeTexture(Texture*t, SDL_Renderer* render)
	/// \brief Initialize a texture of type GPU_TEXTURE.
	///
	///
	/// 
	/// \param T Is of type GPU_TEXTURE aka Texture
	/// \param renderer	 Takes an Initlized Adress of an SDL Renderer(SDL_Renderer* )	
	///
	/// This Functions takes an pointer to an
	/// GPU_TEXTURE and an pointer to an SDL_Renderer.
	///
	/// What it does, it initilizes the values of the 
	/// GPU_TEXTURE struct and with the SDL_Renderer
	/// and some default values.
	///
	/// This function \bDOES NOT\b load any Content!!!
	///
	void initilizeTexture(Texture*t, SDL_Renderer* render);

	///\fn destroyTexture(Texture* t)
	/// \brief Destroys aka remove an loaded texture from memory
	///  \param t is an pointer to a Texture
	/// This function frees a Texture in case an image was loaded on it.
	/// If this was not the case this function does simply nothing at all.
	void destroyTexture(Texture* t);

	//Loads image at specified path
	///\fn loadFromFile(Texture* t, char* path)
	/// \brief Load an Image from the disk into the GraphicCards memory
	///  \param t is an pointer to a texture where the image should end after loading
	///  \param path the location on the disk of the picture.
	///   \returns TRUE on Sucess
	/// This Function loads any image given and tries to perform optimation on the image
	/// to ensure it fits the resulotion of the screen the best.
	bool loadFromFile(Texture* t, char* path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(Texture* t, TTF_Font* font, std::string textureText, SDL_Color textColor);
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