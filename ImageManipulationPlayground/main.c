#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#define IMP_ERROR_SUCCESS 0
#define IMP_ERROR_FAIL 1

#define COMPONENT_SIZE 3

struct ImageData
{
	int width;
	int height; 
	unsigned char *data;
};

//image data stuff
struct ImageData load_image(const char * const pathIn);
struct ImageData create_uninitialized_image(int width, int height);
void destroy_image(struct ImageData image);

//util
int getDataOffset(struct ImageData imageData, int x, int y);
void setPixel(struct ImageData source, struct ImageData target, int sx, int sy, int tx, int ty);

//image manipulations that are not in-place
struct ImageData rotate_image_90_cw(struct ImageData imageData);
//tests
void run_image_rotation_test();
void run_image_copy_test();
void run_library_tests();
int image_readwrite_test(const char * const pathIn, const char * const pathOut);

int main(int argc, char * argv[])
{
	//run_library_tests();
	//run_image_rotation_test();
	run_image_copy_test();
}

void run_image_rotation_test()
{
	const char * const inPath = "../TestData/square_compass_200.png";
	const char * const outPath = "../TestDataResults/square_compass_200_rotated.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);

	printf("Rotating image 90 degrees clockwise \n");

	//first test, just make sure we can copy the data over manually
	for (int y = 0; y < imageData.width; ++y)
	{
		for (int x = 0; x < imageData.height; ++x)
		{
			int targetX = imageData.width - y;
			
		}
	}

	if (stbi_write_bmp(outPath, newImageData.width, newImageData.height, 3, newImageData.data))
		printf("Rotating image 90 degrees clockwise \n");

	destroy_image(imageData);
	destroy_image(newImageData);
}

void run_image_copy_test()
{
	const char * const inPath = "../TestData/square_compass_200.png";
	const char * const outPath = "../TestDataResults/square_compass_200_rotated.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);

	printf("Manual image copy \n");

	//first test, just make sure we can copy the data over manually
	for (int y = 0; y < imageData.width; ++y)
	{
		for (int x = 0; x < imageData.height; ++x)
		{
			setPixel(imageData, newImageData, x, y, x, y);
		}
	}

	if (stbi_write_bmp(outPath, newImageData.width, newImageData.height, 3, newImageData.data))
		printf("Rotating image 90 degrees clockwise \n");

	destroy_image(imageData);
	destroy_image(newImageData);
}

struct ImageData load_image(const char * const pathIn)
{
	struct ImageData imageData;
	int w, h, n;
	unsigned char *data = stbi_load(pathIn, &w, &h, &n, 0);
	imageData.width = w;
	imageData.height = h;
	imageData.data = data;
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


int getDataOffset(struct ImageData imageData, int x, int y)
{
	return (x + y * imageData.width) * COMPONENT_SIZE;
}


void setPixel(struct ImageData source, struct ImageData target, int sx, int sy, int tx, int ty)
{
	target.data[getDataOffset(target, tx, ty)] = source.data[getDataOffset(source, sx, sy)];
	target.data[getDataOffset(target, tx, ty) + 1] = source.data[getDataOffset(source, sx, sy) + 1];
	target.data[getDataOffset(target, tx, ty) + 2] = source.data[getDataOffset(source, sx, sy) + 2];
}

void run_library_tests()
{
	printf("Hello \n");

	if (image_readwrite_test("../TestData/square_compass_200.png", "../TestDataResults/square_compass_200.png") == IMP_ERROR_SUCCESS)
		printf("Test passed successfully");
	else
		printf("Error");

	getchar();
}

int image_readwrite_test(const char * const pathIn, const char * const pathOut)
{
	int x, y, n;
	unsigned char *data = stbi_load(pathIn, &x, &y, &n, 0);

	if (!data)
		return 1;

	if (stbi_write_bmp(pathOut, x, y, n, data))
		return 0;

	return 1;
}