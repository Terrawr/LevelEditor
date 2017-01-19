#include "DefaultFont.h"

#include <string>

#include "Graphic.h"
#include "Rectangle.h"

namespace gui {


	int DefaultFont::getHeight() const
	{
		return 8;
	}

	int DefaultFont::getWidth(const std::string& text) const
	{
		return 8 * text.size();
	}

	int DefaultFont::drawGlyph(Graphics* graphics, unsigned char glyph, int x, int y)
	{
		graphics->drawRectangle(Rectangle(x, y, 8, 8));

		return 8;
	}

	void DefaultFont::drawString(Graphics* graphics, const std::string& text, int x, int y)
	{
		unsigned int i;

		for (i = 0; i< text.size(); ++i)
		{
			drawGlyph(graphics, text.at(i), x, y);
			x += getWidth(text);
		}
	}

	int DefaultFont::getStringIndexAt(const std::string& text, int x)
	{
		if (x >(int)text.size() * 8)
		{
			return text.size();
		}

		return x / 8;
	}

}