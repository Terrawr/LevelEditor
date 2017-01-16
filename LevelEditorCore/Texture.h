#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
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

//#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(Texture* t, TTF_Font* font, char* textureText, SDL_Color textColor);
//#endif

	//Creates blank texture
	/** Creates a blank Texture with current RenderDrawColor as background color.
	* \param *t saves the result. Must be initialised BEFORE calling this function.
	* \param width is the ´width of the texture you want to create
	* \param height is the height of the texture you want to create
	* \param SDL_TextureAccess See SDL Documentation!!!!
	*
	* \returns true on success
	*/
	bool createBlank(Texture* t, int width, int height, SDL_TextureAccess);

	//Deallocates texture
	/** Clears the content of an texture by deleting it from the renderer
	* \param *t texture you want to delete
	*
	* Frees memory by deleting the SDL_Texture* stored in Texture*.
	*/
	void freeTexture(Texture* t);

	//Set color modulation
	/**
	*  \brief Set an additional color value used in render copy operations.
	*
	*  \param texture The texture to update.
	*  \param r       The red color value multiplied into copy operations.
	*  \param g       The green color value multiplied into copy operations.
	*  \param b       The blue color value multiplied into copy operations.
	*
	*  \note This is Wrapperfunction!
	*
	*  \sa SDL_GetTextureColorMod()
	*/
	void setColor(Texture* t, Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	/**
	*  \brief Set the blend mode used for texture copy operations.
	*
	*  \param t The texture to update.
	*  \param blendMode ::SDL_BlendMode to use for texture blending.
	*
	*  \note If the blend mode is not supported, the closest supported mode is
	*        chosen. This is Wrapperfunction!
	*
	*  \sa SDL_GetTextureBlendMode()
	*/
	void setBlendMode(Texture*t, SDL_BlendMode blending);

	//Set alpha modulation
	/**
	*  \brief Set an additional alpha value used in render copy operations.
	*
	*  \param texture The texture to update.
	*  \param alpha     The alpha value multiplied into copy operations.
	*
	*  \note This is a Wrapperfunction!
	*
	*  \sa SDL_GetTextureAlphaMod()
	*/
	void setAlpha(Texture* t, Uint8 alpha);

	//Renders texture at given point
	//struct texture* t, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
	/**
	*  \brief Copy a portion of the source texture to the current rendering target, rotating it by angle around the given center
	*
	*  \param renderer The renderer which should copy parts of a texture.
	*  \param texture  The source texture.
	*  \param clip     A pointer to the source rectangle, or NULL for the entire
	*                   texture.
	*  \param angle    An angle in degrees that indicates the rotation that will be applied to dstrect
	*  \param center   A pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w/2, dstrect.h/2).
	*  \param flip     An SDL_RendererFlip value stating which flipping actions should be performed on the texture
	*
	*  \note  This is a Wrapperfunction!
	*/
	void render(Texture* t, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	//Set t as render target
	/**
	* \brief Set a texture as the current rendering target.
	*
	* \param renderer The renderer.
	* \param texture The targeted texture, which must be created with the SDL_TEXTUREACCESS_TARGET flag, or NULL for the default render target
	*
	* \note This is a Wrapperfunction
	*
	*  \sa SDL_GetRenderTarget()
	*/
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