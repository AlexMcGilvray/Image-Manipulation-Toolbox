#include "exports.h"

LIBRARY_API void export_test()
{
	printf("EXPORT !! \n");
}


LIBRARY_API void export_test2(const char * someVal)
{
	printf("EXPORT %s !! \n", someVal);
}

//@TODO Determine output format by dest postfix EX image.png -> stbi_write_png 
LIBRARY_API void export_rotate_image_90_cw(const char * source, const char * dest)
{
	struct ImageData imageData = load_image(source);
	struct ImageData newImageData = rotate_image_90_cw(imageData);

	if (!stbi_write_png(dest, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

LIBRARY_API void export_rotate_image_90_ccw(const char * source, const char * dest)
{
	struct ImageData imageData = load_image(source);
	struct ImageData newImageData = rotate_image_90_ccw(imageData);

	if (!stbi_write_png(dest, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

LIBRARY_API void export_rotate_image_180(const char * source, const char * dest)
{
	struct ImageData imageData = load_image(source);
	struct ImageData newImageData = rotate_image_180(imageData);

	if (!stbi_write_png(dest, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

LIBRARY_API void export_rotate_image(const char * source, const char * dest, float degrees, int offsetX, int offsetY)
{
	struct ImageData imageData = load_image(source);
	struct ImageData newImageData = rotate_image(imageData,degrees,offsetX,offsetY);

	if (!stbi_write_png(dest, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

LIBRARY_API void export_rotate_image_shear(const char * source, const char * dest, float degrees, int offsetX, int offsetY)
{
	struct ImageData imageData = load_image(source);
	struct ImageData newImageData = rotate_image_shear(imageData, 45.0f, 0, 0);

	if (!stbi_write_png(*dest, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

//rotate_image(imageData, 45.0f,0,0);
