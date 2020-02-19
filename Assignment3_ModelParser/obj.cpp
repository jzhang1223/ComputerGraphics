#pragma once
#include <vector>
#include <stdio.h>
#include <QVector3D>
#include <fstream>
#include <sstream>
#include <iostream>

// ??
#include <QtCore/QtMath>
// #include <glm/glm.hpp>

// #include <unistd.h>

class OBJ {

private:


public:

    std::vector<QVector3D> out_vertices;
    // std::vector<QVector2D> out_uvs;
    std::vector<QVector3D> out_normals;

    OBJ(std::string path) {

        // std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<unsigned int> vertexIndices, normalIndices;

        std::vector<QVector3D> temp_vertices;
        // std::vector<QVector2D> temp_uvs;
        std::vector<QVector3D> temp_normals;

// NEW
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
                    QVector3D vec(x, y, z);
                    temp_vertices.push_back(vec);
                    printf("v: %f %f %f\n", vec.x(), vec.y(), vec.z());
                }

                else if(lineHeader == "vn") {
                    float x, y, z;
                    iss >> x >> y >> z;
                    QVector3D normal(x, y, z);
                    temp_normals.push_back(normal);
                    printf("vn: %f %f %f\n", normal.x(), normal.y(), normal.z());
                }

                else if(lineHeader == "f") {
                    int v1, n1, v2, n2, v3, n3;
                    sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);

                    printf("\n");
                    printf("f: %d%d %d%d %d%d", v1, n1, v2, n2, v3, n3);


                    // int vertexIndex[3], normalIndex[3];
                    vertexIndices.push_back(v1);
                    vertexIndices.push_back(v2);
                    vertexIndices.push_back(v3);

                    normalIndices.push_back(n1);
                    normalIndices.push_back(n2);
                    normalIndices.push_back(n3);


                }
            }
            printf("Done");
            // DO SOME PUSHING HERE
            for(int i = 0; i < vertexIndices.size(); i++) {
                int vertexIndex = vertexIndices[i];
                QVector3D vertex = temp_vertices[vertexIndex-1];
                out_vertices.push_back(vertex);
            }

            for(int i = 0; i < normalIndices.size(); i++) {
                int normalIndex = normalIndices[i];
                QVector3D normal = temp_normals[normalIndex-1];
                out_normals.push_back(normal);
            }
        }
// END

        // FILE *file = fopen(path, "r");
        // if (file == NULL) {
        //     printf("No file path found!: ");
        //     printf(path);
        // }

        // TODO: Check file empty?
        // while(1) {
        //     char lineHeader[128];
        //     // read first word
        //     int res = fscanf(file, "%s", lineHeader);

        //     printf(lineHeader);
        //     printf("\n");

        //     // End of file
        //     if(res == EOF) {
        //         printf("Reached EOF");
        //         break;
        //     }

        //     else if(lineHeader[0] == '#') {
        //     // do nothing?
        //     }

        //     // parse vertices
        //     else if(lineHeader == "v") {
        //     // QVector3D
        //         float a, b, c;
        //         fscanf(file, "%f %f %f\n", &a, &b, &c);
        //         QVector3D vertex(a, b, c);
        //         temp_vertices.push_back(vertex);
        //         printf("Storing: %f %f %f\n", a, b, c);
        //     }
            // else if (lineHeader == "vt") {

            // }
            // else if(lineHeader == "vn") {
            //     // QVector3D
            //     QVector3D normal;
            //     fscanf(file, "%f %f %f\n", normal.x, normal.y, normal.z);
            //     temp_normals.push_back(normal);
            // }

            // else if(lineHeader == "f") {
            //     std::string vertex1, vertex2, vertex3;
            //     unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            //     int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
            //         vertexIndex[0], uvIndex[0], normalIndex[0],
            //         vertexIndex[1], uvIndex[1], normalIndex[1],
            //         vertexIndex[2], uvIndex[2], normalIndex[2]);
            //         // &vertexIndex[0], &normalIndex[0],
            //         // &vertexIndex[1], &normalIndex[1],
            //         // &vertexIndex[2], &normalIndex[2]);
            //     if(matches != 9) {
            //         printf("Polygon face elements could not be parsed");
            //         // TODO: Probably throw some exception...
            //     }

            //     vertexIndices.push_back(vertexIndex[0]);
            //     vertexIndices.push_back(vertexIndex[1]);
            //     vertexIndices.push_back(vertexIndex[2]);
            //     // uvIndices.push_back(uvIndex[0]);
            //     // uvIndices.push_back(uvIndex[1]);
            //     // uvIndices.push_back(uvIndex[2]);
            //     normalIndices.push_back(normalIndex[0]);
            //     normalIndices.push_back(normalIndex[1]);
            //     normalIndices.push_back(normalIndex[2]);
            // }
        // }


        // Processing the data
        // for(int i = 0; i < vertexIndices.size(); i++) {
        //     int vertexIndex = vertexIndices[i];
        //     QVector3D vertex = temp_vertices[vertexIndex-1];
        //     out_vertices.push_back(vertex);
        // }

        //
        // for(int i = 0; i < uvIndices.size(); i++) {
        //     int uvIndex = uvIndices[i];
        //     // Questionable below??
        //     QVector2D uv = temp_uvs[uvIndex-1];
        //     out_uvs.push_back(uv);
        // }

        // for(int i = 0; i < normalIndices.size(); i++) {
        //     int normalIndex = normalIndices[i];
        //     QVector3D normal = temp_normals[normalIndex-1];
        //     out_normals.push_back(normal);
        // }
    }

    // void draw() {
    //     glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(QVector3D), this->vertices[0], GL_STATIC_DRAW);
    // }
};