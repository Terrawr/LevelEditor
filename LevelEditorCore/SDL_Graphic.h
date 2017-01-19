#pragma once
#include "Color.h"
#include "Graphic.h"
#include "SDL.h"

namespace gui {

	class Image;
	class Rectangle;

	/**
	* SDL implementation of the Graphics.
	*/
	class SDLGraphics : public Graphics
	{
	public:

		// Needed so that drawImage(gcn::Image *, int, int) is visible.
		using Graphics::drawImage;

		/**
		* Constructor.
		*/
		SDLGraphics();

		/**
		* Constructor.
		*/
		SDLGraphics(SDL_Window*,SDL_Renderer*);

		/**
		* Sets the target SDL_Surface to draw to. The target can be any
		* SDL_Surface. This funtion also pushes a clip areas corresponding to
		* the dimension of the target.
		*
		* @param target the target to draw to.
		*/
		virtual void setTarget(SDL_Texture* target);

		/**
		* Gets the target SDL_Surface.
		*
		* @return the target SDL_Surface.
		*/
		virtual SDL_Texture* getTarget() const;

		/**
		* Draws an SDL_Surface on the target surface. Normaly you'll
		* use drawImage, but if you want to write SDL specific code
		* this function might come in handy.
		*
		* NOTE: The clip areas will be taken into account.
		*/
		virtual void drawSDLSurface(SDL_Texture* surface, SDL_Rect source,
			SDL_Rect destination);


		// Inherited from Graphics

		virtual void _beginDraw();

		virtual void _endDraw();

		virtual bool pushClipArea(Rectangle area);

		virtual void popClipArea();

		virtual void drawImage(const Image* image, int srcX, int srcY,
			int dstX, int dstY, int width,
			int height);

		virtual void drawPoint(int x, int y);

		virtual void drawLine(int x1, int y1, int x2, int y2);

		virtual void drawRectangle(const Rectangle& rectangle);

		virtual void fillRectangle(const Rectangle& rectangle);

		virtual void setColor(const Color& color);

		virtual const Color& getColor();

	protected:
		/**
		* Draws a horizontal line.
		*
		* @param x1 the start coordinate of the line.
		* @param y the y coordinate of the line.
		* @param x2 the end coordinate of the line.
		*/
		virtual void drawHLine(int x1, int y, int x2);

		/**
		* Draws a vertical line.
		*
		* @param x the x coordinate of the line.
		* @param y1 the start coordinate of the line.
		* @param y2 the end coordinate of the line.
		*/
		virtual void drawVLine(int x, int y1, int y2);

		SDL_Window* Display;
		SDL_Renderer* Renderer;
		int w,  h;
		Color mColor;
		bool mAlpha;
	};


}