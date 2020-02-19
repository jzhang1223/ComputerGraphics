#pragma once
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QtCore/QtMath>


class OBJ {

private:


public:

    std::vector<float> out_vertices;
    std::vector<float> out_normals;
    std::vector<uint> out_indices;

    OBJ() {}

    void parse(std::string path) {
        std::ifstream inFile;
        inFile.open(path);

        std::cout << "Loading: " << path << "\n";

        if(inFile.is_open()) {
            std::string line;
            while(getline(inFile, line)) {
                if(line[0] == '#') {
                    continue;
                }
                std::istringstream iss(line);
                std::string lineHeader;
                iss >> lineHeader;

                if(lineHeader == "v") {
                    float x, y, z;
                    iss >> x >> y >> z;
                    out_vertices.push_back(x);
                    out_vertices.push_back(y);
                    out_vertices.push_back(z);
                    // printf("v: %f %f %f\n", x, y, z);
                }

                else if(lineHeader == "vn") {
                    float x, y, z;
                    iss >> x >> y >> z;
                    out_normals.push_back(x);
                    out_normals.push_back(y);
                    out_normals.push_back(z);

                }

                else if(lineHeader == "f") {
                    // Setup for parsing vertices and normals
                    uint v1, n1, v2, n2, v3, n3;
                    sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);

                    // add vertices to indices
                    out_indices.push_back(v1-1);
                    out_indices.push_back(v2-1);
                    out_indices.push_back(v3-1);

                }
            }
            printf("Done parsing!\n");

            // printf("\nPrinted vertices:\n");
            // for(int i = 0; i < out_vertices.size(); i++) {
            //     printf("%f ", out_vertices[i]);
            //     if (i % 3 == 2) {
            //         printf("\n");
            //     }
            // }

            // printf("\nPrinted normals\n");
            // for(int i = 0; i < out_vertices.size(); i++) {
            //     printf("%f ", out_normals[i]);
            //     if (i % 3 == 2) {
            //         printf("\n");
            //     }
            // }
        }

    }
};