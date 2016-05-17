#include "image_data.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#define COMPONENT_SIZE 3
#define PI 3.1415926535897932384626433832795028841

struct ImageData load_image(const char * const pathIn)
{
	struct ImageData imageData;
	int w, h, n;
	unsigned char *data = stbi_load(pathIn, &w, &h, &n, 0);
	imageData.width = w;
	imageData.height = h;
	imageData.data = data;
	if (data == 0)
		printf("load_image error \n");
	return imageData;
}

struct ImageData create_uninitialized_image(int width, int height)
{
	struct ImageData imageData;
	imageData.width = width;
	imageData.height = height;
	imageData.data = malloc(sizeof(unsigned char) * width * height * COMPONENT_SIZE);
	return imageData;
}

void destroy_image(struct ImageData image)
{
	free(image.data);
}

int get_data_offset(struct ImageData imageData, int x, int y)
{
	return (x + y * imageData.width) * COMPONENT_SIZE;
}

void set_pixel_from_source(struct ImageData source, struct ImageData target, int sx, int sy, int tx, int ty)
{
	target.data[get_data_offset(target, tx, ty)] = source.data[get_data_offset(source, sx, sy)];
	target.data[get_data_offset(target, tx, ty) + 1] = source.data[get_data_offset(source, sx, sy) + 1];
	target.data[get_data_offset(target, tx, ty) + 2] = source.data[get_data_offset(source, sx, sy) + 2];
}

void set_pixel_rgb(struct ImageData target, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	target.data[get_data_offset(target, x, y)] = r;
	target.data[get_data_offset(target, x, y) + 1] = g;
	target.data[get_data_offset(target, x, y) + 2] = b;
}

void copy_range(struct ImageData source, struct ImageData target, int length, int sourceOffset, int targetOffset)
{ 
	unsigned int memLength = length * COMPONENT_SIZE;
	memcpy(target.data + sourceOffset, source.data + targetOffset, memLength);
}

int is_in_range(struct ImageData imageData, int x, int y)
{
	if (x < 0 || x >= imageData.width || y < 0 || y >= imageData.height)
		return 0;
	return 1;
}

#pragma region Naive implementation
#ifdef NAIVE_IMPLEMENTATION

struct ImageData rotate_image_90_cw(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.height, imageData.width);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int targetX = newImageData.width - 1 - y;
			const int targetY = x;
			set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

struct ImageData rotate_image_90_ccw(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.height, imageData.width);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int targetX = y;
			const int targetY = x;
			set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

struct ImageData rotate_image_180(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int targetX = imageData.width - 1 - x;
			const int targetY = imageData.height - 1 - y;
			set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}


struct ImageData rotate_image(struct ImageData imageData, float degrees, int offsetX, int offsetY)
{
	const float radians = degrees * (PI / 180.0f);
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int translatedX = x + offsetX;
			const int translatedY = y + offsetY;
			const int targetX = ((translatedX * cos(radians)) + (translatedY * sin(radians))) - offsetX;
			const int targetY = ((-translatedX * sin(radians)) + (translatedY * cos(radians))) - offsetY;
			if (is_in_range(newImageData,targetX,targetY))
				set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

struct ImageData rotate_image_shear(struct ImageData imageData, float degrees, int offsetX, int offsetY)
{
	const float radians = degrees * (PI / 180.0f);
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int translatedX = x + offsetX;
			const int translatedY = y + offsetY;
			int xPrime, yPrime;
			//step 1 first shear
			xPrime = translatedX + translatedY * -tan(radians / 2);
			yPrime = translatedY;
			//step 2 second shear
			xPrime = xPrime;
			yPrime = xPrime * sin(radians) + yPrime;
			//step 3 third shear
			xPrime = xPrime + yPrime * -tan(radians / 2);
			yPrime = yPrime;

			const int targetX = xPrime - offsetX;
			const int targetY = yPrime - offsetY;
			if (is_in_range(newImageData, targetX, targetY))
				set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

//This is my attempt to do a greyscale conversion before I look up the algorithm to see what my approach would be with no 
//prior knowledge.
struct ImageData convert_to_greyscale_average(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const unsigned char r = imageData.data[get_data_offset(imageData, x, y)];
			const unsigned char g = imageData.data[get_data_offset(imageData, x, y) + 1];
			const unsigned char b = imageData.data[get_data_offset(imageData, x, y) + 2];
			const int totalVal = r + g + b;
			const unsigned char finalVal = (totalVal / 3);
			set_pixel_rgb(newImageData, x, y, finalVal, finalVal, finalVal);
		}
	}
	return newImageData;
}

struct ImageData convert_to_greyscale_luminosity(struct ImageData imageData)
{
	const float rWeight = 0.21f;
	const float gWeight = 0.72f;
	const float bWeight = 0.07f;
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const unsigned char r = imageData.data[get_data_offset(imageData, x, y)];
			const unsigned char g = imageData.data[get_data_offset(imageData, x, y) + 1];
			const unsigned char b = imageData.data[get_data_offset(imageData, x, y) + 2];
			const int finalVal = (int)((r * rWeight) + (g * gWeight) + (b * bWeight));
			set_pixel_rgb(newImageData, x, y, finalVal, finalVal, finalVal);
		}
	}
	return newImageData;
}

struct ImageData flip_image_vertically(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int targetX = x;
			const int targetY = imageData.height - 1 - y;
			set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

struct ImageData flip_image_horizontally(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			const int targetX = imageData.width - 1 - x;
			const int targetY = y;
			set_pixel_from_source(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

#endif
#pragma endregion

#pragma region Memcopy batching implementation
#ifdef MEMCOPY_BATCH_OPERATION_IMPLEMENTATION
struct ImageData rotate_image_90_cw(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.height, imageData.width);
	// figure out which imagedata will have the longer row
	// for each row memcopy the 1d array contents over 
	return newImageData;
}

struct ImageData rotate_image_90_ccw(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.height, imageData.width);
	return newImageData;
}

struct ImageData rotate_image_180(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	return newImageData;
}

//This is my attempt to do a greyscale conversion before I look up the algorithm to see what my approach would be with no 
//prior knowledge.
struct ImageData convert_to_greyscale_average(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	return newImageData;
}

struct ImageData convert_to_greyscale_luminosity(struct ImageData imageData)
{
	const float rWeight = 0.21f;
	const float gWeight = 0.72f;
	const float bWeight = 0.07f;
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	return newImageData;
}

struct ImageData flip_image_vertically(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);
	for (int y = 0; y < imageData.height; ++y)
	{
		int length = imageData.width - 1;
		copy_range(imageData, newImageData, length, get_data_offset(imageData, 0, y), get_data_offset(newImageData, 0, newImageData.height - 1 - y));
	}
	return newImageData;
}

struct ImageData flip_image_horizontally(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);

	return newImageData;
}
#endif
#pragma endregion

