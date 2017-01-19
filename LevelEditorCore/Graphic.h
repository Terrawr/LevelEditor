#pragma once
#include <stack>

#include "Rectangle.h"
#include "ClipRectangle.h"

namespace gui {

	class Color;
	class Font;
	class Image;

	/**
	*
	* In Graphics you can set clip areas to limit drawing to certain
	* areas of the screen. Clip areas are put on a stack, which means that you
	* can push smaller and smaller clip areas onto the stack. All coordinates
	* will be relative to the topmost clip area. In most cases you won't have
	* to worry about the clip areas, unless you want to implement some really
	* complex widget. Pushing and poping of clip areas are handled
	* automatically by container widgets when their child widgets are drawn.
	*
	* IMPORTANT: Remember to pop each clip area that you pushed on the stack
	* after you are done with it.
	*
	* If you feel that Graphics is to restrictive for your needs, there is
	* no one stopping you from using your own code for drawing in Widgets.
	* You could for instance use pure SDL in the drawing of Widgets bypassing
	* Graphics. This might however hurt portability of your application.
	*/
	class  Graphics
	{
	public:
		Graphics();
		//Graphics(SDL_Window*, SDL_Renderer*);

		virtual ~Graphics() { }

		/**
		* Initializes drawing. Called by the Gui when Gui::draw() is called.
		* It is needed by some implementations of Graphics to perform
		* preparations before drawing. An example of such an implementation
		* would be OpenGLGraphics.
		*
		* NOTE: You will never need to call this function yourself.
		*       Gui will do it for you.
		*
		* @see _endDraw, Gui::draw
		*/
		virtual void _beginDraw() { }

		/**
		* Deinitializes drawing. Called by the Gui when a Gui::draw() is done.
		* done. It should reset any state changes made by _beginDraw().
		*
		* NOTE: You will never need to call this function yourself.
		*       Gui will do it for you.
		*
		* @see _beginDraw, Gui::draw
		*/
		virtual void _endDraw() { }

		/**
		* Pushes a clip area onto the stack. The x and y coordinates in the
		* Rectangle will be relative to the last pushed clip area.
		* If the new area falls outside the current clip area, it will be
		* clipped as necessary.
		*
		* @param area the clip area to be pushed onto the stack.
		* @return false if the the new area lays totally outside the
		*         current clip area. Note that an empty clip area
		*         will be pused in this case.
		*/
		virtual bool pushClipArea(Rectangle area);

		/**
		* Removes the topmost clip area from the stack.
		*
		* @throws Exception if the stack is empty.
		*/
		virtual void popClipArea();

		/**
		* Gets the current clip area. Usefull if you want to do drawing
		* bypassing Graphics.
		*
		* @return the current clip area.
		*/
		virtual const ClipRectangle& getCurrentClipArea();

		/**
		* Draws a part of an Image.
		*
		* NOTE: Width and height arguments will not scale the Image but
		*       specifies the size of the part to be drawn. If you want
		*       to draw the whole Image there is a simplified version of
		*       this function.
		*
		* EXAMPLE: @code drawImage(myImage, 10, 10, 20, 20, 40, 40); @endcode
		*          Will draw a rectangular piece of myImage starting at
		*          coordinate (10, 10) in myImage, with width and height 40.
		*          The piece will be drawn with it's top left corner at
		*          coordinate (20, 20).
		*
		* @param image the Image to draw.
		* @param srcX source Image x coordinate.
		* @param srcY source Image y coordinate.
		* @param dstX destination x coordinate.
		* @param dstY destination y coordinate.
		* @param width the width of the piece.
		* @param height the height of the piece.
		*/
		virtual void drawImage(const Image* image, int srcX, int srcY,
			int dstX, int dstY, int width,
			int height) = 0;
		/**
		* Draws an image. A simplified version of the other drawImage.
		* It will draw a whole image at the coordinate you specify.
		* It is equivalent to calling:
		* @code drawImage(myImage, 0, 0, dstX, dstY, image->getWidth(), \
		image->getHeight()); @endcode
		*/
		virtual void drawImage(const Image* image, int dstX, int dstY);

		/**
		* Draws a single point/pixel.
		*
		* @param x the x coordinate.
		* @param y the y coordinate.
		*/
		virtual void drawPoint(int x, int y) = 0;

		/**
		* Ddraws a line.
		*
		* @param x1 the first x coordinate.
		* @param y1 the first y coordinate.
		* @param x2 the second x coordinate.
		* @param y2 the second y coordinate.
		*/
		virtual void drawLine(int x1, int y1, int x2, int y2) = 0;

		/**
		* Draws a simple, non-filled, Rectangle with one pixel width.
		*
		* @param rectangle the Rectangle to draw.
		*/
		virtual void drawRectangle(const Rectangle& rectangle) = 0;

		/**
		* Draws a filled Rectangle.
		*
		* @param rectangle the filled Rectangle to draw.
		*/
		virtual void fillRectangle(const Rectangle& rectangle) = 0;

		/**
		* Sets the Color to use when drawing.
		*
		* @param color a Color.
		*/
		virtual void setColor(const Color& color) = 0;

		/**
		* Gets the Color to use when drawing.
		*
		* @return the Color used when drawing.
		*/
		virtual const Color& getColor() = 0;

		/**
		* Sets the font to use when drawing text.
		*
		* @param font the Font to use when drawing.
		*/
		virtual void setFont(Font* font);

		/**
		* Draws text.
		*
		* @param text the text to draw.
		* @param x the x coordinate where to draw the text.
		* @param y the y coordinate where to draw the text.
		* @param alignment Graphics::LEFT, Graphics::CENTER or Graphics::RIGHT.
		* @throws Exception when no Font is set.
		*/
		virtual void drawText(const std::string& text, int x, int y,
			unsigned int alignment = LEFT);
		/**
		* Alignments for text drawing.
		*/
		enum
		{
			LEFT = 0,
			CENTER,
			RIGHT
		};

	protected:
		std::stack<ClipRectangle> mClipStack;
		Font* mFont;
	};
}