#include <stdio.h>
#include "image_data.h"



//set this to 1 to enable console error messages
#define DEBUG_CONSOLE 0

//TODO
// * move image rotation code out of the test and into rotate_image_90_cw
// * make rotate_image_90_cw handle images with different width and height dimensions (done but the task above isn't done yet so I won't clear it until that is done)
// * fix style for function names (underscores for spaces, all lowercase)
// * update support for different component sizes rather than just hard coding 3

//BACKLOG
// * flip image horizontally
// * flip image vertically
// * scaling functions
// * color space functions (convert to greyscale etc)



int main(int argc, char * argv[])
{
	//run_library_tests();
	run_image_rotation_test();
	//run_image_copy_test();
}

