#ifndef OUTPUTGEOMETRY_H
#define OUTPUTGEOMETRY_H
#include <string>
#include <vector>
#include "structs.h"
void exportWRLWithNormals(const std::string& outputFilename, const std::vector<Triangle>& triangles);
#endif