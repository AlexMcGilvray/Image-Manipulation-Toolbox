#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

int image_readwrite_test(char * const pathIn, char * const pathOut);

int main(int argc, char * argv[])
{

	printf("Hello \n");

	if (image_readwrite_test("../TestData/square_compass_200.png", "../TestDataResults/square_compass_200.png") == 0)
		printf("Test passed successfully");
	else
		printf("Error");

	getchar();
}

int image_readwrite_test(char * const pathIn, char * const pathOut)
{
	int x, y, n;
	unsigned char *data = stbi_load(pathIn, &x, &y, &n, 0);

	if (!data)
		return 1;

	if (stbi_write_bmp(pathOut, x, y, n, data))
		return 0;

	return 1;
}