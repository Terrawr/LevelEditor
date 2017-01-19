#pragma once
#include <string>

namespace gui {

	class Color;
	class ImageLoader;

	/**
	* Holds an image. To be able to use this class you must first set an
	* ImageLoader in Image by calling
	* @code Image::setImageLoader(myImageLoader) @endcode
	* The function is static. If this is not done, the constructor taking a
	* filename will throw an exception. The ImageLoader you use must be
	* compatible with the Graphics object you use.
	*
	* EXAMPLE: If you use SDLGraphics you should use SDLImageLoader.
	*          Otherwise your program will crash in a most bizarre way.
	*/
	class Image
	{
	public:

		/**
		* Constructor.
		*/
		Image();

		/**
		* Destructor.
		*/
		virtual ~Image();

		/**
		* Loads an image by calling the Image class' ImageLoader.
		*
		* NOTE: The functions getPixel and putPixel are only guaranteed to work
		*       before an image has been converted to display format.
		*
		* @param filename the file to load.
		* @param convertToDisplayFormat true if the image should be converted
		*                               to display, false otherwise.
		*/
		static Image* load(const std::string& filename, bool convertToDisplayFormat = true);

		/**
		* Gets the ImageLoader used for loading Images.
		*
		* @return the ImageLoader used for loading Images.
		* @see SDLImageLoader, AllegroImageLoader
		*/
		static ImageLoader* getImageLoader();

		/**
		* Sets the ImageLoader to be used for loading images.
		*
		* IMPORTANT: The ImageLoader is static and MUST be set before loading
		*            images!
		*
		* @param imageLoader the ImageLoader to be used for loading images.
		* @see SDLImageLoader, AllegroImageLoader
		*/
		static void setImageLoader(ImageLoader* imageLoader);

		/**
		* Frees an image.
		*/
		virtual void free() = 0;

		/**
		* Gets the width of the Image.
		*
		* @return the image width
		*/
		virtual int getWidth() const = 0;

		/**
		* Gets the height of the Image.
		*
		* @return the image height
		*/
		virtual int getHeight() const = 0;

		/**
		* Gets the color of a pixel at coordinate (x, y) in the image.
		*
		* IMPORTANT: Only guaranteed to work before the image has been
		*            converted to display format.
		*
		* @param x the x coordinate.
		* @param y the y coordinate.
		* @return the color of the pixel.
		*/
		//virtual Color getPixel(int x, int y) = 0;

		/**
		* Puts a pixel with a certain color at coordinate (x, y).
		*
		* @param x the x coordinate.
		* @param y the y coordinate.
		* @param color the color of the pixel to put.
		*/
		//virtual void putPixel(int x, int y, const Color& color) = 0;

		/**
		* Converts the image, if possible, to display format.
		*
		* IMPORTANT: Only guaranteed to work before the image has been
		*            converted to display format.
		*/
		//virtual void convertToDisplayFormat() = 0;

	protected:
		static ImageLoader* mImageLoader;
	};

}