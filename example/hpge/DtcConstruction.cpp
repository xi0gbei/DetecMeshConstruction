#include "../include/DtcConstruction.h"
#include <vector>
#include <iostream>

void HPGePhysicalGeometry::createGeometry(double* param) const {
    if(dtctype == 0){
        SurfaceRegistry reg;
        double D1 = param[0], D2 = param[1];
        double d1 = param[2], d2 = param[3], d3 = param[4];
        double HeightofWDct = D2;
        double innerradius, outerradius, height, chamferradius;
        Vec3 relocation_all = {0, 0, -HeightofWDct};

        // --- Ge crystal (inner, built first) ---
        innerradius = 0;
        outerradius = d2;
        chamferradius = d3;
        height = d1;
        Geometry* Ge1 = new ChamferedHollowCylinder(outerradius, innerradius, chamferradius, height, 32, 10);
        Vec3 location_Ge = {0, 0, (d1 - d3)};
        Vec3 location_halfheight = {0, 0, 1.5 * d3};
        Ge1->generateMesh({0, 0, 0}, 2/*Ge*/, -1/*outmat*/);
        Ge1->rotateMesh(3, 0);
        Ge1->relocatemesh(location_Ge + location_halfheight);
        Ge1->relocatemesh(relocation_all);
        reg.resolveFaces(Ge1->getInternalTriangles());
        Ge1->outputmesh(const_cast<std::vector<Triangle>&>(triangles));
        delete Ge1;

        // --- Alualloy tube (outer, built second) ---
        innerradius = 0;
        outerradius = D1;
        height = HeightofWDct;
        Geometry* Alualloy_tube = new ChamferedHollowCylinder(outerradius, innerradius, 0.0, height, 32, 10);
        Vec3 location_Alualloy = {0, 0, 0.5 * height};
        location_halfheight = {0, 0, 0.5 * height};
        Alualloy_tube->generateMesh(location_Alualloy - location_halfheight, 3/*carbon*/, -1/*outmat*/);
        Alualloy_tube->relocatemesh(relocation_all);
        reg.resolveFaces(Alualloy_tube->getInternalTriangles());
        Alualloy_tube->outputmesh(const_cast<std::vector<Triangle>&>(triangles));
        delete Alualloy_tube;
    }
    else{
        std::cerr << "Unsupported DTC type for HPGePhysicalGeometry" << std::endl;
    }
}
