#pragma once
#include <iosfwd>
#include <string>
namespace gui {

	class Image;

	/**
	* ImageLoaders base class. Contains basic image loading functions every
	* image loader should have. Image loaders should inherit from this
	* class and impements it's functions.
	*/
	class ImageLoader
	{
	public:

		/**
		* Destructor.
		*/
		virtual ~ImageLoader() { }

		/**
		* Loads an image by calling the image's ImageLoader.
		*
		* NOTE: The functions getPixel and putPixel in Image are only guaranteed to
		*       work before an image has been converted to display format.
		*
		* @param filename the file to load.
		* @param convertToDisplayFormat true if the image should be converted
		*                               to display, false otherwise.
		*/
		virtual Image* load(const std::string& filename, bool convertToDisplayFormat = true) = 0;
	};

}