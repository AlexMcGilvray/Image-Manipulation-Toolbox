#pragma once
#include "image_data.h"

#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API //__declspec(dllimport) not sure why it was suggested I import w
#    endif
#elif
#    define LIBRARY_API
#endif

LIBRARY_API  void export_test();
LIBRARY_API  void export_test2(const char * someVal);

LIBRARY_API void export_rotate_image_90_cw(const char * source, const char * dest);
//LIBRARY_API void export_rotate_image_90_ccw(const char * source, const char * dest);
//LIBRARY_API void export_rotate_image_180(const char * source, const char * dest);
//LIBRARY_API void export_rotate_image(const char * source, const char * dest, float degrees, int offsetX, int offsetY);
//LIBRARY_API void export_rotate_image_shear(const char * source, const char * dest, float degrees, int offsetX, int offsetY);
//LIBRARY_API void export_convert_to_greyscale_average(const char * source, const char * dest);
//LIBRARY_API void export_convert_to_greyscale_luminosity(const char * source, const char * dest);
//LIBRARY_API void export_flip_image_vertically(const char * source, const char * dest);
//LIBRARY_API void export_flip_image_horizontally(const char * source, const char * dest);
//LIBRARY_API void export_draw_symmetry_lines(const char * source, const char * dest, int hLines, int vLines);