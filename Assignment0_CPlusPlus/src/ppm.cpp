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

    int maxValue = -1;
    int pixelsFilled = 0;

    std::cout << "Loading PPM Named: " << fileName << "\n";

    if(inFile.is_open()) {
        std::string line;
        bool skipFirst = true;
        while(getline(inFile,line)) {
            if (skipFirst || line[0] == '#') {
                std::cout << "SKIPPING: " << line << "\n";
                skipFirst = false;
                continue;
            }
            // TODO do some word parsing here

            if (!m_width) {
                std::cout << "STORING m_width AS: " << line[0] << "\n";
                m_width = line[0] - '0';
                std::cout << "STORING m_height AS: " << line[2] << "\n";
                m_height = line[2] - '0';

                m_PixelData = new unsigned char[m_width * m_height * 3];
            } else if (maxValue == -1) {
                maxValue = std::stoi(line);
                std::cout << "maxValue: " << maxValue << "\n";

            } else {
                std::cout << "Filling Pixel #" << pixelsFilled << " : " << line << " ... ";
                m_PixelData[pixelsFilled] = std::stoi(line);
                // std::cout << m_PixelData[pixelsFilled] << "\n";

                // TODO scale the pixel if necessary
                printf("%i", m_PixelData[pixelsFilled]);

                // printf("%i: %i\n", i, pixelData[i]);

                pixelsFilled += 1;
                std::cout << "\n";
            }
        }
    }

    std::cout << "Finished Loading PPM\n";

    inFile.close();
    int max = m_width * m_height * 3;
    // for (int i = 0; this->m_PixelData[i] != '\0'; i++) {
    for (int i = 0; i < max; i++) {
        printf("%i", m_PixelData[i]);
        std::cout << " = " << m_PixelData[i] << "\n";


    }

    std::cout << "pixelsFilled: " << pixelsFilled << "\n\n";


}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
    delete m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    // TODO: Save a PPM image to disk
    std::ofstream outFile;
    outFile.open(outputFileName);

    std::cout << "Saving PPM named: " << outputFileName << "\n";

    outFile << "P3\n";
    outFile << "# CS4300 ASGN0\n";

    std::cout << "WRITING: " << m_width << " " << m_height << "\n";
    outFile << m_width << " " << m_height << "\n";
    // TODO replace this 
    outFile << "255\n";

    int max = m_width * m_height * 3;
    std::cout << "\n";
    for(int i = 0; i < max; i++) {
        printf("%i\n", m_PixelData[i]);
        outFile << int(this->m_PixelData[i]) << "\n";
    }

    std::cout << "\nFinished Saving PPM\n";

    outFile.close();

}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    int max = m_width * m_height * 3;
    for (int i = 0; i < max; i++) {
        if (m_PixelData[i] + 50 <= 100) {
            m_PixelData[i] = 0;
        }
        else {
            m_PixelData[i] -= 50;
        }
    }
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B){
    int red_index = (m_width * y * 3) + (3 * x);
    int green_index = red_index + 1;
    int blue_index = red_index + 2;

    m_PixelData[red_index] = R;
    m_PixelData[green_index] = G;
    m_PixelData[blue_index] = B;
}
