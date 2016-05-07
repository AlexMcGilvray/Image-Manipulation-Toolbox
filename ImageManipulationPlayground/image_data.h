#pragma once
#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

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



#endif