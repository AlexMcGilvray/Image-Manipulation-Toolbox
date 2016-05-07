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