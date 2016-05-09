#pragma once
#ifndef TESTS_H
#define TESTS_H

//tests
void run_image_cw90_rotation_test();
void run_image_ccw90_rotation_test();
void run_image_copy_test();
void run_library_tests();
int image_readwrite_test(const char * const pathIn, const char * const pathOut);
#endif