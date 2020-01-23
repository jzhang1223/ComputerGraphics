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

    // unsigned char maxValue;
    int pixelsFilled = 0;

    std::cout << "Loading PPM Named: " << fileName << "\n";

    if(inFile.is_open()) {
        std::string line;
        bool skipFirst = true;
        while(getline(inFile,line)) {
            // do something to the line
            if (skipFirst || line[0] == '#') {
                std::cout << "SKIPPING: " << line << "\n";
                skipFirst = false;
                continue;
            }

            std::cout << line << "\n";

            if (!m_width) {
                std::cout << "STORING m_width AS: " << line[0] << "\n";
                // if (line[0] == "1") {
                //     std::cout << "STRING-STRING-STRING\n";
                // }
                // if (line[0] == '1') {
                //     std::cout << "CHAR-CHAR-CHAR\n";
                // }
                m_width = line[0] - '0';
                std::cout << "STORING m_height AS: " << line[2] << "\n";
                m_height = line[2] - '0';
            }
            //     m_PixelData = new unsigned char[m_width * m_height * 3];
            // } else if (!maxValue) {
            //     maxValue = line[0];
            // } else {
            //     m_PixelData[pixelsFilled] = line[0];
            //     pixelsFilled += 1;
            // }
        }
    }

    std::cout << "Finished Loading PPM\n";

    inFile.close();

}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    // TODO: Save a PPM image to disk
    std::ofstream outFile;
    outFile.open(outputFileName);

    std::cout << "Saving PPM named: " << outputFileName << "\n";

    outFile << "P3\n";
    outFile << "# Comment\n";

    std::cout << "WRITING: " << m_width << " " << m_height << "\n";
    outFile << m_width << " " << m_height << "\n";
    // TODO replace this 
    outFile << "MAX VALUE\n";

    // for(int i = 0; this->m_PixelData[i] != '\0'; i++) {

    // for(int i = 0; i < sizeof(m_PixelData) / sizeof(m_PixelData[0]); i++) {

    // for(int i = 0; i < 6; i++) {
    //     std::cout << i;
    //     outFile << this->m_PixelData[i] << "\n";
    // }

    std::cout << "Finished Saving PPM\n";

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
