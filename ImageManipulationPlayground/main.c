#include <stdio.h>
#include "image_data.h"

#define IMP_ERROR_SUCCESS 0
#define IMP_ERROR_FAIL 1

//set this to 1 to enable console error messages
#define DEBUG_CONSOLE 0

//TODO
// * move image rotation code out of the test and into rotate_image_90_cw
// * make rotate_image_90_cw handle images with different width and height dimensions (done but the task above isn't done yet so I won't clear it until that is done)
// * fix style for function names (underscores for spaces, all lowercase)
// * update support for different component sizes rather than just hard coding 3

//BACKLOG
// * flip image horizontally
// * flip image vertically
// * scaling functions
// * color space functions (convert to greyscale etc)

//tests
void run_image_rotation_test();
void run_image_copy_test();
void run_library_tests();
int image_readwrite_test(const char * const pathIn, const char * const pathOut);

int main(int argc, char * argv[])
{
	//run_library_tests();
	run_image_rotation_test();
	//run_image_copy_test();
}

void run_image_rotation_test()
{
	printf("Rotating image 90 degrees clockwise \n");

	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_rotated.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = rotate_image_90_cw(imageData);

	if (!stbi_write_bmp(outPath, newImageData.width, newImageData.height, 3, newImageData.data))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData); 
}

void run_image_copy_test()
{
	const char * const inPath = "../TestData/square_compass_200.png";
	const char * const outPath = "../TestDataResults/square_compass_200_copied.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = create_uninitialized_image(imageData.width, imageData.height);

	printf("Manual image copy \n");

	//first test, just make sure we can copy the data over manually
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			setPixel(imageData, newImageData, x, y, x, y);
		}
	}

	if (stbi_write_bmp(outPath, newImageData.width, newImageData.height, 3, newImageData.data))
		printf("Error \n");

	destroy_image(imageData);
	destroy_image(newImageData);
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