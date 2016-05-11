#pragma once
#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#define IMP_ERROR_SUCCESS 0
#define IMP_ERROR_FAIL 1

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
int get_data_offset(struct ImageData imageData, int x, int y);
void set_pixel_from_source(struct ImageData source, struct ImageData target, int sx, int sy, int tx, int ty);
void set_pixel_rgb(struct ImageData target, int x, int y, unsigned char r, unsigned char g, unsigned char b);

//image manipulations that are not in-place
struct ImageData rotate_image_90_cw(struct ImageData imageData);
struct ImageData rotate_image_90_ccw(struct ImageData imageData);
struct ImageData rotate_image_180(struct ImageData imageData);
struct ImageData convert_to_greyscale_average(struct ImageData imageData);
struct ImageData convert_to_greyscale_luminosity(struct ImageData imageData);

#endif