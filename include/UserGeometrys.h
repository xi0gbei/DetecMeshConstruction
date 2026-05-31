#ifndef USERGEOMETRYS_H
#define USERGEOMETRYS_H
#include "./geometry.h"
#include "./triprocess.h"
class ChamferedHollowCylinder : public Geometry {
    double outerradius, innerradius, chamferradius, zheight;
    int radslices;
    int zslices;
    std::vector<Triangle> *triangle_output;
public:
    ChamferedHollowCylinder(double oR, double ir, double cr, double zh, int s1, int s2) : 
    outerradius(oR), innerradius(ir), chamferradius(cr), zheight(zh), radslices(s1), zslices(s2) {
        triangle_output = new std::vector<Triangle>();
    }
    ~ChamferedHollowCylinder() {
        delete triangle_output;
    }
    void generateMesh(Vec3 position,  int outerMat, int innerMat) const override;
    void rotateMesh(int axis, double position) const override;
    void outputmesh(std::vector<Triangle>& triangles) const override;
    void relocatemesh(Vec3 position) const override;
    std::vector<Triangle>& getInternalTriangles() override { return *triangle_output; }
};

class Cuboid : public Geometry {
    double sizex, sizey, sizez;
    std::vector<Triangle> *triangle_output;
public:
    Cuboid(double sx, double sy, double sz);
    ~Cuboid();
    void generateMesh(Vec3 position, int outerMat, int innerMat) const override;
    void outputmesh(std::vector<Triangle>& triangles) const override;
    void rotateMesh(int axis, double position) const override;
    void relocatemesh(Vec3 position) const override;
    std::vector<Triangle>& getInternalTriangles() override { return *triangle_output; }
};

#endif // USERGEOMETRYS_H