// Include our custom library
#include "PPM.h"

int main(){

    PPM myPPM("../textures/test1.ppm");
    myPPM.darken();
    myPPM.savePPM("../textures/test1_darken.ppm");

    // PPM myPPM("../textures/test.ppm");
    // myPPM.darken();
    // myPPM.savePPM("../textures/test_darken.ppm");

    // PPM myPPM("../textures/sample.ppm");
    // myPPM.darken();
    // myPPM.setPixel(0, 1, 12, 34, 56);
    // myPPM.savePPM("../textures/sample_saved.ppm");

    return 0;
}
