#include "image_data.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#define COMPONENT_SIZE 3

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

void set_pixel(struct ImageData source, struct ImageData target, int sx, int sy, int tx, int ty)
{
	target.data[get_data_offset(target, tx, ty)] = source.data[get_data_offset(source, sx, sy)];
	target.data[get_data_offset(target, tx, ty) + 1] = source.data[get_data_offset(source, sx, sy) + 1];
	target.data[get_data_offset(target, tx, ty) + 2] = source.data[get_data_offset(source, sx, sy) + 2];
}

struct ImageData rotate_image_90_cw(struct ImageData imageData)
{
	struct ImageData newImageData = create_uninitialized_image(imageData.height, imageData.width);
	for (int y = 0; y < imageData.height; ++y)
	{
		for (int x = 0; x < imageData.width; ++x)
		{
			int targetX = newImageData.width - 1 - y;
			int targetY = x;
#ifdef DEBUG_CONSOLE
			if (targetX > newImageData.width)
				printf("targetx bigger than width \n");
			if (targetY > newImageData.height)
				printf("targety bigger than height \n");
#endif
			set_pixel(imageData, newImageData, x, y, targetX, targetY);
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
			int targetX = y;
			int targetY = x;
#ifdef DEBUG_CONSOLE
			if (targetX > newImageData.width)
				printf("targetx bigger than width \n");
			if (targetY > newImageData.height)
				printf("targety bigger than height \n");
#endif
			set_pixel(imageData, newImageData, x, y, targetX, targetY);
		}
	}
	return newImageData;
}

