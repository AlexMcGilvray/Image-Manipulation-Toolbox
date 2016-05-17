#include "tests.h"
//imp
#include "image_data.h"
//stb
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"
//std
#include <stdio.h>
#include <time.h>

#define prep_running_time() clock_t start; clock_t diff; int msec;
#define get_running_time(a) start=clock(); a(); diff = clock() - start; msec = diff * 1000 / CLOCKS_PER_SEC; printf("msecs: %d\n",msec);

void run_image_rotation_tests()
{
	prep_running_time();
	printf("run_image_cw90_rotation_test : ");
	get_running_time(run_image_rotation_cw90_test);
	printf("run_image_ccw90_rotation_test : ");
	get_running_time(run_image_rotation_ccw90_test);
	printf("run_image_rotation_180_test : ");
	get_running_time(run_image_rotation_180_test);
}

void run_image_color_conversion_tests()
{
	prep_running_time();
	printf("run_convert_to_greyscale_test : ");
	get_running_time(run_convert_to_greyscale_average_test);
	printf("run_convert_to_greyscale_luminosity_test : ");
	get_running_time(run_convert_to_greyscale_luminosity_test);
}

void run_image_flip_tests()
{
	prep_running_time();
	printf("run_image_flip_vertically_test : ");
	get_running_time(run_flip_image_vertically_test);
	printf("run_flip_image_horizontally_test : ");
	get_running_time(run_flip_image_horizontally_test);
}

void run_image_arbitrary_rotation_tests()
{
	prep_running_time();
	//printf("run_image_rotation_test (45.0f) : ");
	//get_running_time(run_image_rotation_test_45);
	printf("run_image_rotation_test_45_center_offset (45.0f, center pivot) : ");
	get_running_time(run_image_rotation_test_45_center_offset);
}

void run_image_rotation_cw90_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_rotated_90_cw.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = rotate_image_90_cw(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data,0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_image_rotation_ccw90_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_rotated_90_ccw.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = rotate_image_90_ccw(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data,0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_image_rotation_180_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_rotated_180.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = rotate_image_180(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_image_rotation_test_45()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_rotated_45.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = rotate_image(imageData, 45.0f,0,0);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_image_rotation_test_45_center_offset()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_rotated_45_offset_center.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = rotate_image(imageData, 45.0f,-imageData.width / 2, -imageData.height / 2);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_convert_to_greyscale_average_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_greyscale_average.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = convert_to_greyscale_average(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_convert_to_greyscale_luminosity_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_greyscale_luminosity.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = convert_to_greyscale_luminosity(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_flip_image_vertically_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_flip_vertically.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = flip_image_vertically(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_flip_image_horizontally_test()
{
	const char * const inPath = "../TestData/noodles_yawn.jpg";
	const char * const outPath = "../TestDataResults/noodles_yawn_flip_horizontally.png";

	struct ImageData imageData = load_image(inPath);
	struct ImageData newImageData = flip_image_horizontally(imageData);

	if (!stbi_write_png(outPath, newImageData.width, newImageData.height, 3, newImageData.data, 0))
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
			set_pixel_from_source(imageData, newImageData, x, y, x, y);
		}
	}

	if (stbi_write_bmp(outPath, newImageData.width, newImageData.height, 3, newImageData.data))
		printf("Error \n");

	destroy_image(newImageData);
	destroy_image(imageData);
}

void run_library_tests()
{
	printf("Running library tests \n");

	if (image_readwrite_test("../TestData/square_compass_200.png", "../TestDataResults/square_compass_200.png") == IMP_ERROR_SUCCESS)
		printf("Test passed successfully");
	else
		printf("Error");
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