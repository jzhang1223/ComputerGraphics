#pragma once
#include <vector>
#include <stdio.h>
#include <QVector3D>
// #include <glm/glm.hpp>

class OBJ {

private:
        std::vector < glm::vec3 > out_vertices;
        std::vector < glm::vec2 > out_uvs;
        std::vector < glm::vec3 > out_normals;

public:

    OBJ(std::string path) {

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;


        FILE *file = fopen(path, "r");
        if (file == NULL) {
            printf("No file path found!");
            // TODO: probably throw some exception...
            return false;
        }

        // TODO: Check file empty?
        while(1) {
            char lineHeader[128];
            // read first word
            int res = fscanf(file, "%s", lineHeader);
            // End of file
            if(res == EOF) {
                break;
            }

            else if(lineHeader[0] == '#') {
            // do nothing?
            }

            // parse vertices
            else if(lineHeader == "v") {
            // QVector3D
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            }
            // else if (lineHeader == "vt") {

            // }
            else if(lineHeader == "vn") {
                // QVector3D
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_normals.push_back(normal);
            }

            else if(lineHeader == "f") {
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                if(matches != 9) {
                    printf("Polygon face elements could not be parsed");
                // TODO: Probably throw some exception...
                    return false;
                }

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }


        // Processing the data
        for(int i = 0; i < vertexIndices.size(); i++) {
            int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex-1];
            out_vertices.push_back(vertex);
        }

        //
        for(int i = 0; i < uvIndices.size(); i++) {
            int uvIndex = uvIndices[i];
            // Questionable below??
            glm::vec3 uv = temp_uvs[uvIndex-1];
            out_uvs.push_back(uv);
        }

        for(int i = 0; i < normalIndices.size(); i++) {
            int normalIndex = uvIndices[i];
            glm::vec3 normal = temp_normals[normalIndex-1];
            out_normals.push_back(normal);
        }
    }

    void draw() {
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->&vertices[0], GL_STATIC_DRAW);
    }
}