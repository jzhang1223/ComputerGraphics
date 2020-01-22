// Include our custom library
#include "PPM.h"

int main(){

    // PPM myPPM("./textures/test1.ppm");
    // myPPM.darken();
    // myPPM.savePPM("./textures/test1_darken.ppm");

    PPM myPPM("./textures/sample.ppm");
    myPPM.savePPM("./textures/sample_saved.ppm");

    return 0;
}
