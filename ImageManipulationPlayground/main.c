#include <stdio.h>
#include "image_data.h"
#include "tests.h"

//set this to 1 to enable console error messages
#define DEBUG_CONSOLE 0

//TODO
// * update support for different component sizes rather than just hard coding 3
// * write some logging functions to dump test results to a text file

//BACKLOG

// * scaling functions
// * move image_data into it's own external lib/header 
// * make driver program so various tests can be run using command line params instead of altering main and re-compiling

int main(int argc, char * argv[])
{
	//run_library_tests();
	//run_image_rotation_tests();
	//run_image_color_conversion_tests(); 
	//run_image_flip_tests();
	run_image_arbitrary_rotation_tests();
	getchar();
}

//DONE
// * fix style for function names (underscores for spaces, all lowercase)
// * move image rotation code out of the test and into rotate_image_90_cw
// * make rotate_image_90_cw handle images with different width and height dimensions (done but the task above isn't done yet so I won't clear it until that is done)
// * flip image horizontally
// * flip image vertically
// * color space functions (convert to greyscale etc)