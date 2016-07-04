#pragma once
#ifndef TESTS_H
#define TESTS_H

//timed test groups
void run_image_rotation_tests();
void run_image_color_conversion_tests();
void run_image_flip_tests();
void run_image_arbitrary_rotation_tests();
void run_draw_symmetry_lines_tests();
void run_image_resize_tests();

//individual tests
void run_image_rotation_cw90_test();
void run_image_rotation_ccw90_test();
void run_image_rotation_180_test();
void run_image_rotation_test_45();
void run_image_rotation_test_45_center_offset();
void run_image_rotation_shear_test_45();
void run_image_rotation_shear_test_45_center_offset();
void run_convert_to_greyscale_average_test();
void run_convert_to_greyscale_luminosity_test();
void run_flip_image_vertically_test();
void run_flip_image_horizontally_test();
void run_draw_symmetry_lines_test_01();
void run_draw_symmetry_lines_test_02();
void run_draw_symmetry_lines_test_03();
void run_resize_image_test_01();
void run_resize_image_test_02();

void run_image_copy_test();
void run_library_tests();
int image_readwrite_test(const char * const pathIn, const char * const pathOut);
#endif