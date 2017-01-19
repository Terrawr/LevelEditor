#include "Graphic.h"
#include "Exception.h"
#include "Font.h"
#include "Image.h"

namespace gui {

	Graphics::Graphics()
	{
		mFont = NULL;
	}

	bool Graphics::pushClipArea(Rectangle area)
	{
		if (mClipStack.empty())
		{
			ClipRectangle carea;
			carea.x = area.x;
			carea.y = area.y;
			carea.width = area.width;
			carea.height = area.height;
			mClipStack.push(carea);
			return true;
		}

		ClipRectangle top = mClipStack.top();
		ClipRectangle carea;
		carea = area;
		carea.xOffset = top.xOffset + carea.x;
		carea.yOffset = top.yOffset + carea.y;
		carea.x += top.xOffset;
		carea.y += top.yOffset;

		// Clamp the pushed clip rectangle.
		if (carea.x < top.x)
		{
			carea.x = top.x;
		}

		if (carea.y < top.y)
		{
			carea.y = top.y;
		}

		if (carea.width > top.width)
		{
			carea.width = top.width;
		}

		if (carea.height > top.height)
		{
			carea.height = top.height;
		}

		bool result = carea.intersect(top);

		mClipStack.push(carea);

		return result;
	}

	void Graphics::popClipArea()
	{

		if (mClipStack.empty())
		{
			throw GUI_EXCEPTION("Tried to pop clip area from empty stack.");
		}

		mClipStack.pop();
	}

	const ClipRectangle& Graphics::getCurrentClipArea()
	{
		if (mClipStack.empty())
		{
			throw GUI_EXCEPTION("The clip area stack is empty.");
		}

		return mClipStack.top();
	}

	void Graphics::drawImage(const Image* image, int dstX, int dstY)
	{
		drawImage(image, 0, 0, dstX, dstY, image->getWidth(), image->getHeight());
	}

	void Graphics::setFont(Font* font)
	{
		mFont = font;
	}

	void Graphics::drawText(const std::string& text, int x, int y,
		unsigned int alignment)
	{
		if (mFont == NULL)
		{
			throw GUI_EXCEPTION("No font set.");
		}

		switch (alignment)
		{
		case LEFT:
			mFont->drawString(this, text, x, y);
			break;
		case CENTER:
			mFont->drawString(this, text, x - mFont->getWidth(text) / 2, y);
			break;
		case RIGHT:
			mFont->drawString(this, text, x - mFont->getWidth(text), y);
			break;
		default:
			throw GUI_EXCEPTION("Unknown alignment.");
		}
	}

}