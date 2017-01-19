#include "ImageFont.h"

#include <sstream>
#include "Color.h"
#include "Graphic.h"
#include "Image.h"

#include "Exception.h"

namespace gui {

	ImageFont::ImageFont(const std::string& filename, const std::string& glyphs)
	{
		mFilename = filename;
		mImage = Image::load(filename, false);

		//Color separator = mImage->getPixel(0, 0);

		int i = 0;
		/*for (i = 0;
			i < mImage->getWidth() && separator == mImage->getPixel(i, 0);
			++i)
		{
		}*/

		if (i >= mImage->getWidth())
		{
			throw GUI_EXCEPTION("Corrupt image.");
		}

		int j = 0;
		/*for (j = 0; j < mImage->getHeight(); ++j)
		{
			if (separator == mImage->getPixel(i, j))
			{
				break;
			}
		}*/

		mHeight = j;
		int x = 0, y = 0;
		unsigned char k;

		for (i = 0; i < (int)glyphs.size(); ++i)
		{
			k = glyphs.at(i);
			addGlyph(k, x, y, {0xff,0xff,0xff,0xff});
		}

		//int w = mImage->getWidth();
		//int h = mImage->getHeight();
		//mImage->convertToDisplayFormat();

		mRowSpacing = 0;
		mGlyphSpacing = 0;
	}

	ImageFont::ImageFont(const std::string& filename, unsigned char glyphsFrom,
		unsigned char glyphsTo)
	{
		mFilename = filename;
		mImage = Image::load(filename, false);

		//Color separator = mImage->getPixel(0, 0);

		int i = 0;
		/*for (i = 0; separator == mImage->getPixel(i, 0)
			&& i < mImage->getWidth(); ++i)
		{
		}*/

		if (i >= mImage->getWidth())
		{
			throw GUI_EXCEPTION("Corrupt image.");
		}

		int j = 0;
		/*for (j = 0; j < mImage->getHeight(); ++j)
		{
			if (separator == mImage->getPixel(i, j))
			{
				break;
			}
		}*/

		mHeight = j;
		int x = 0, y = 0;

		for (i = glyphsFrom; i<glyphsTo + 1; i++)
		{
			addGlyph(i, x, y, { 0xff,0xff,0xff,0xff });
		}

		//int w = mImage->getWidth();
		//int h = mImage->getHeight();
		//mImage->convertToDisplayFormat();

		mRowSpacing = 0;
		mGlyphSpacing = 0;
	}

	ImageFont::~ImageFont()
	{
		delete mImage;
	}

	int ImageFont::getWidth(unsigned char glyph) const
	{
		if (mGlyph[glyph].width == 0)
		{
			return mGlyph[(int)(' ')].width + mGlyphSpacing;
		}

		return mGlyph[glyph].width + mGlyphSpacing;
	}

	int ImageFont::getHeight() const
	{
		return mHeight + mRowSpacing;
	}

	int ImageFont::drawGlyph(Graphics* graphics, unsigned char glyph,
		int x, int y)
	{
		// This is needed for drawing the Glyph in the middle if we have spacing
		int yoffset = getRowSpacing() >> 1;

		if (mGlyph[glyph].width == 0)
		{
			graphics->drawRectangle(Rectangle(x, y + 1 + yoffset,
				mGlyph[(int)(' ')].width - 1,
				mGlyph[(int)(' ')].height - 2));

			return mGlyph[(int)(' ')].width + mGlyphSpacing;
		}

		graphics->drawImage(mImage, mGlyph[glyph].x, mGlyph[glyph].y, x,
			y + yoffset, mGlyph[glyph].width,
			mGlyph[glyph].height);

		return mGlyph[glyph].width + mGlyphSpacing;
	}

	void ImageFont::drawString(Graphics* graphics, const std::string& text,
		int x, int y)
	{
		unsigned int i;

		for (i = 0; i< text.size(); ++i)
		{
			drawGlyph(graphics, text.at(i), x, y);
			x += getWidth(text.at(i));
		}
	}

	void ImageFont::setRowSpacing(int spacing)
	{
		mRowSpacing = spacing;
	}

	int ImageFont::getRowSpacing()
	{
		return mRowSpacing;
	}

	void ImageFont::setGlyphSpacing(int spacing)
	{
		mGlyphSpacing = spacing;
	}

	int ImageFont::getGlyphSpacing()
	{
		return mGlyphSpacing;
	}

	void ImageFont::addGlyph(unsigned char c, int &x,
		int &y, const Color& separator)
	{
		//Color color;
		//do
		//{
		//	++x;

		//	if (x >= mImage->getWidth())
		//	{
		//		y += mHeight + 1;
		//		x = 0;

		//		if (y >= mImage->getHeight())
		//		{
		//			std::string str;
		//			std::ostringstream os(str);
		//			os << "Image ";
		//			os << mFilename;
		//			os << " with font is corrupt near character '";
		//			os << c;
		//			os << "'";
		//			throw GUI_EXCEPTION(os.str());
		//		}
		//	}

		//	//color = mImage->getPixel(x, y);

		//} while (color == separator);

		int w = 0;

		/*do
		{
			++w;

			if (x + w >= mImage->getWidth())
			{
				std::string str;
				std::ostringstream os(str);
				os << "Image ";
				os << mFilename;
				os << " with font is corrupt near character '";
				os << c;
				os << "'";
				throw GUI_EXCEPTION(os.str());
			}

			color = mImage->getPixel(x + w, y);

		} while (color != separator);*/

		mGlyph[c] = Rectangle(x, y, w, mHeight);

		x += w;
	}

	int ImageFont::getWidth(const std::string& text) const
	{
		unsigned int i;
		int size = 0;

		for (i = 0; i < text.size(); ++i)
		{
			size += getWidth(text.at(i));
		}

		return size - mGlyphSpacing;
	}

	int ImageFont::getStringIndexAt(const std::string& text, int x)
	{
		unsigned int i;
		int size = 0;

		for (i = 0; i < text.size(); ++i)
		{
			size += getWidth(text.at(i));

			if (size > x)
			{
				return i;
			}
		}

		return text.size();
	}


}