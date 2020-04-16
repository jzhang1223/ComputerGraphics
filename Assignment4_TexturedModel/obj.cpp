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
    std::vector<float> out_texs;
    std::vector<float> out_normals;
    std::vector<uint> out_indices;
    std::vector<uint> out_texIndices;

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

                if(lineHeader == "mtllib") {
                    std::string mtlName;
                    iss >> mtlName;
                }

                else if(lineHeader == "o") {
                    //
                }

                else if(lineHeader == "s") {
                    //
                }

                else if(lineHeader == "v") {
                    float x, y, z;
                    iss >> x >> y >> z;
                    out_vertices.push_back(x);
                    out_vertices.push_back(y);
                    out_vertices.push_back(z);
                    // printf("v: %f %f %f\n", x, y, z);
                }
                
                else if(lineHeader == "vt") {
                    float x, y;
                    iss >> x >> y;
                    out_texs.push_back(x);
                    out_texs.push_back(y);
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
                    uint v1, t1, n1, v2, t2, n2, v3, t3, n3;
                    sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                    // add vertices to indices
                    out_indices.push_back(v1-1);
                    out_indices.push_back(v2-1);
                    out_indices.push_back(v3-1);

                    // do something with t1,t2,t3
                    out_texIndices.push_back(t1-1);
                    out_texIndices.push_back(t2-1);
                    out_texIndices.push_back(t3-1);
                }
            }
            printf("Done parsing!\n");
            printf("%d\n", out_indices.size());
            printf("%d\n", out_texIndices.size());

        }

    }

    // QVector<QVector3D> getVertices() {
    //     QVector<QVector3D> result;
    //     for(int i = 0; i < out_vertices.size(); i += 3) {
    //         result << QVector3D(out_vertices[i], out_vertices[i+1], out_vertices[i+2]);
    //     }
    //     return result;
    // }

    // QVector<QVector2D> getTexs() {
    //     QVector<QVector2D> result;
    //     for(int i = 0; i < out_texs.size(); i += 2) {
    //         result << QVector3D(out_texs[i], out_texs[i+1]);
    //     }
    //     return result;
    // }

    // QVector<QVector3D> getNormals() {
    //     QVector<QVector3D> result;
    //     for(int i = 0; i < out_normals.size(); i += 3) {
    //         result << QVector3D(out_normals[i], out_normals[i+1], out_normals[i+2]);
    //     }
    //     return result;
    // }



    /*
    std::vector<float> out_vertices;
    std::vector<float> out_texs;
    std::vector<float> out_normals;
    std::vector<uint> out_indices;
    std::vector<uint> out_texIndices;
    */
};