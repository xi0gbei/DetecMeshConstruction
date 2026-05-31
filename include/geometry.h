#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include "./structs.h"
class Geometry {
public:
    virtual void generateMesh(Vec3 position,int outerMat, int innerMat) const = 0;
    virtual void outputmesh(std::vector<Triangle>& triangles) const = 0;
    virtual void rotateMesh(int axis, double position) const = 0;
    virtual void relocatemesh(Vec3 position) const = 0;
    virtual std::vector<Triangle>& getInternalTriangles() = 0;
    virtual ~Geometry() {}
};
#endif // GEOMETRY_H