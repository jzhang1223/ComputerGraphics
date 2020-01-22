#include "PPM.h"
#include <iostream>
#include <fstream>
#pragma once



// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName){
    // TODO:    Load and parse a ppm to get its pixel
    //          data stored properly.

    std::ifstream inFile;

    inFile.open(fileName);

    unsigned char maxValue;
    int pixelsFilled = 0;

    if(inFile.is_open()) {
        std::string line;
        bool skipFirst = true;
        while(getline(inFile,line)) {
            // do something to the line
            if (skipFirst || line[0] == '#') {
                skipFirst = false;
                continue;
            }

            if (!m_width) {
                m_width = line[0];
                m_height = line[2];
                m_PixelData = new unsigned char[m_width * m_height * 3];
            } else if (!maxValue) {
                maxValue = line[0];
            } else {
                m_PixelData[pixelsFilled] = line[0];
                pixelsFilled += 1;
            }
        }
    }
}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    // TODO: Save a PPM image to disk
    std::ofstream outFile;
    outFile.open(outputFileName);

    outFile << "P3" << std::endl;
    outFile << "# Comment" << std::endl;
    outFile << m_width << " " << m_height << std::endl;
    // TODO replace this 
    outFile << "MAX VALUE" << std::endl;

    // for(int i = 0; this->m_PixelData[i] != '\0'; i++) {

    // for(int i = 0; i < sizeof(m_PixelData) / sizeof(m_PixelData[0]); i++) {
    
    // for(int i = 0; i < 6; i++) {
    //     std::cout << i;
    //     outFile << this->m_PixelData[i] << "\n";
    // }

    outFile.close();

}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    // TODO: Output a 'filtered' PPM image.
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B){
    // TODO: Implement
}
