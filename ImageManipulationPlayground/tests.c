#include "tests.h"
#include <stdio.h>
#include "image_data.h"

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

	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			set_pixel(imageData, newImageData, x, y, x, y);
		}
	}

	if (stbi_write_bmp(outPath, newImageData.width, newImageData.height, 3, newImageData.data))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
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
		return IMP_ERROR_FAIL;

	if (stbi_write_bmp(pathOut, x, y, n, data))
		return IMP_ERROR_SUCCESS;

	return IMP_ERROR_FAIL;
}