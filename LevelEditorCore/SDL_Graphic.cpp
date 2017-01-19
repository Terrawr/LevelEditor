#include "SDL_Graphic.h"

#include "Exception.h"
#include "Font.h"
#include "Image.h"
#include "SDL_IMAGE.h"

#include <SDL.h>

namespace gui {
	// For some reason an old version of MSVC did not like std::abs,
	// so we added this macro.
#ifndef ABS
#define ABS(x) ((x)<0?-(x):(x))
#endif


	SDLGraphics::SDLGraphics()
	{
		
		mAlpha = false;
	}

	/**
	* Constructor.
	*/
	SDLGraphics::SDLGraphics(SDL_Window* w, SDL_Renderer* r) : Display(w), Renderer(r)
	{
		SDL_QueryTexture(SDL_GetRenderTarget(this->Renderer), NULL, NULL, &this->w, &this->h);
		mAlpha = false;
	}


	void SDLGraphics::_beginDraw()
	{
		Rectangle area;
		area.x = 0;
		area.y = 0;
		area.width = w;
		area.height = h;

		SDL_RenderClear(this->Renderer);

		pushClipArea(area);
	}

	void SDLGraphics::_endDraw()
	{
		SDL_RenderPresent(this->Renderer);
		popClipArea();
	}

	void SDLGraphics::setTarget(SDL_Texture* target)
	{
		SDL_SetRenderTarget(this->Renderer,target);
		//mTarget = target;
	}

	bool SDLGraphics::pushClipArea(Rectangle area)
	{
		SDL_Rect rect;
		bool result = Graphics::pushClipArea(area);

		const ClipRectangle& carea = mClipStack.top();
		rect.x = carea.x;
		rect.y = carea.y;
		rect.w = carea.width;
		rect.h = carea.height;

		//SDL_SetClipRect(mTarget, &rect);

		SDL_RenderSetViewport(this->Renderer, &rect);

		return result;
	}

	void SDLGraphics::popClipArea()
	{
		Graphics::popClipArea();

		if (mClipStack.empty())
		{
			return;
		}

		const ClipRectangle& carea = mClipStack.top();
		SDL_Rect rect;
		rect.x = carea.x;
		rect.y = carea.y;
		rect.w = carea.width;
		rect.h = carea.height;

		//SDL_SetClipRect(mTarget, &rect);
		SDL_RenderSetViewport(this->Renderer, &rect);
	}

	SDL_Texture* SDLGraphics::getTarget() const
	{
		return SDL_GetRenderTarget(this->Renderer);
	}

	void SDLGraphics::drawImage(const Image* image, int srcX,
		int srcY, int dstX, int dstY,
		int width, int height)
	{
		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();
		SDL_Rect src;
		SDL_Rect dst;
		src.x = srcX;
		src.y = srcY;
		src.w = width;
		src.h = height;
		dst.x = dstX + top.xOffset;
		dst.y = dstY + top.yOffset;

		const SDLImage* srcImage = dynamic_cast<const SDLImage*>(image);

		if (srcImage == NULL)
		{
			throw GUI_EXCEPTION("Trying to draw an image of unknown format, must be an SDLImage.");
		}

		SDL_RenderCopy(this->Renderer,srcImage->getSurface(), &src, &dst);
	}

	void SDLGraphics::fillRectangle(const Rectangle& rectangle)
	{
		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		Rectangle area = rectangle;
		area.x += top.xOffset;
		area.y += top.yOffset;

		if (!area.intersect(top))
		{
			return;
		}

		if (mAlpha)
		{
			/*int x1 = area.x > top.x ? area.x : top.x;
			int y1 = area.y > top.y ? area.y : top.y;
			int x2 = area.x + area.width < top.x + top.width ? area.x + area.width : top.x + top.width;
			int y2 = area.y + area.height < top.y + top.height ? area.y + area.height : top.y + top.height;
			int x, y;

			SDL_LockSurface(mTarget);
			for (y = y1; y < y2; y++)
			{
				for (x = x1; x < x2; x++)
				{
					SDLputPixelAlpha(mTarget, x, y, mColor);
				}
			}
			SDL_UnlockSurface(mTarget);*/

		}
		else
		{
			SDL_Rect rect;
			rect.x = area.x;
			rect.y = area.y;
			rect.w = area.width;
			rect.h = area.height;

			//Uint32 color = SDL_MapRGBA(mTarget->format, mColor.r, mColor.g, mColor.b, mColor.a);
			SDL_SetRenderDrawColor(this->Renderer, mColor.r, mColor.g, mColor.b, mColor.a);
			SDL_RenderFillRect(this->Renderer, &rect);
			//SDL_FillRect(mTarget, &rect, color);
		}
	}

	void SDLGraphics::drawPoint(int x, int y)
	{
		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		x += top.xOffset;
		y += top.yOffset;

		if (!top.isPointInRect(x, y))
			return;

		if (mAlpha)
		{
			//SDLputPixelAlpha(mTarget, x, y, mColor);
			SDL_RenderDrawPoint(this->Renderer, x, y);
		}
		else
		{
			SDL_RenderDrawPoint(this->Renderer, x, y);
			//SDLputPixel(mTarget, x, y, mColor);
		}
	}

	void SDLGraphics::drawHLine(int x1, int y, int x2)
	{
		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}
		const ClipRectangle& top = mClipStack.top();

		x1 += top.xOffset;
		y += top.yOffset;
		x2 += top.xOffset;

		if (y < top.y || y >= top.y + top.height)
			return;

		if (x1 > x2)
		{
			x1 ^= x2;
			x2 ^= x1;
			x1 ^= x2;
		}

		if (top.x > x1)
		{
			if (top.x > x2)
			{
				return;
			}
			x1 = top.x;
		}

		if (top.x + top.width <= x2)
		{
			if (top.x + top.width <= x1)
			{
				return;
			}
			x2 = top.x + top.width - 1;
		}

		SDL_RenderDrawLine(this->Renderer, x1, y, x2, y);
	}

	void SDLGraphics::drawVLine(int x, int y1, int y2)
	{
		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}
		const ClipRectangle& top = mClipStack.top();

		x += top.xOffset;
		y1 += top.yOffset;
		y2 += top.yOffset;

		if (x < top.x || x >= top.x + top.width)
			return;

		if (y1 > y2)
		{
			y1 ^= y2;
			y2 ^= y1;
			y1 ^= y2;
		}

		if (top.y > y1)
		{
			if (top.y > y2)
			{
				return;
			}
			y1 = top.y;
		}

		if (top.y + top.height <= y2)
		{
			if (top.y + top.height <= y1)
			{
				return;
			}
			y2 = top.y + top.height - 1;
		}

		SDL_RenderDrawLine(this->Renderer, x, y1, x, y2);
	}

	void SDLGraphics::drawRectangle(const Rectangle& rectangle)
	{
		int x1 = rectangle.x;
		int x2 = rectangle.x + rectangle.width - 1;
		int y1 = rectangle.y;
		int y2 = rectangle.y + rectangle.height - 1;

		drawHLine(x1, y1, x2);
		drawHLine(x1, y2, x2);

		drawVLine(x1, y1, y2);
		drawVLine(x2, y1, y2);
	}

	void SDLGraphics::drawLine(int x1, int y1, int x2, int y2)
	{
		if (x1 == x2)
		{
			drawVLine(x1, y1, y2);
			return;
		}
		if (y1 == y2)
		{
			drawHLine(x1, y1, x2);
			return;
		}

		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}
		const ClipRectangle& top = mClipStack.top();

		x1 += top.xOffset;
		y1 += top.yOffset;
		x2 += top.xOffset;
		y2 += top.yOffset;

		SDL_RenderDrawLine(this->Renderer, x1, y1, x2, y2);
	}

	void SDLGraphics::setColor(const Color& color)
	{
		mColor = color;

		mAlpha = color.a != 255;
	}

	const Color& SDLGraphics::getColor()
	{
		return mColor;
	}

	void SDLGraphics::drawSDLSurface(SDL_Texture* surface, SDL_Rect source,
		SDL_Rect destination)
	{
		if (mClipStack.empty()) {
			throw GUI_EXCEPTION("Clip stack is empty, perhaps you"
				"called a draw funtion outside of _beginDraw() and _endDraw()?");
		}
		const ClipRectangle& top = mClipStack.top();

		destination.x += top.xOffset;
		destination.y += top.yOffset;

		SDL_RenderCopy(this->Renderer,surface, &source, &destination);
	}
}