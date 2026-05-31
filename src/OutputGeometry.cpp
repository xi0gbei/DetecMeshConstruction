#include "../include/OutputGeometry.h"
#include "../include/structs.h"
#include <fstream>
#include <iostream>
void exportWRLWithNormals(const std::string& outputFilename, const std::vector<Triangle>& triangles) {
    std::ofstream file(outputFilename);
    if (!file) {
        std::cerr << "Cannot create file: " << outputFilename << std::endl;
        return;
    }
    file << "# VRML V2.0 utf8\n";
    // for (int TriVecIndex = 0; TriVecIndex < vec_geo.size(); TriVecIndex++) {
    file << "Shape {\n geometry IndexedFaceSet {\n coord Coordinate {\n point [\n";
    for (const auto& tri : triangles) {
        file << tri.v0.x << " " << tri.v0.y << " " << tri.v0.z << ",\n";
        file << tri.v1.x << " " << tri.v1.y << " " << tri.v1.z << ",\n";
        file << tri.v2.x << " " << tri.v2.y << " " << tri.v2.z << ",\n";
    }
    file << "]\n }\n coordIndex [\n";
    for (size_t i = 0; i < triangles.size(); i++) {
        file << (i * 3) << ", " << (i * 3 + 1) << ", " << (i * 3 + 2) << ", -1,\n";
    }
    file << "]\n }\n}\n";
    // 法向可视化
    file << "Shape {\n geometry IndexedLineSet {\n coord Coordinate {\n point [\n";
    double normal_length = 5.0f;
    for (const auto& tri : triangles) {
        Vec3 normal_end = { tri.center.x + tri.normal.x * normal_length,
                                tri.center.y + tri.normal.y * normal_length,
                                tri.center.z + tri.normal.z * normal_length };
        file << tri.center.x << " " << tri.center.y << " " << tri.center.z << ",\n";
        file << normal_end.x << " " << normal_end.y << " " << normal_end.z << ",\n";
    }
    file << "]\n }\n coordIndex [\n";
    for (size_t i = 0; i < triangles.size(); i++) {
        file << (i * 2) << ", " << (i * 2 + 1) << ", -1,\n";
    }
    file << "]\n }\n}\n";
    // }
    file.close();
}