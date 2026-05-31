#include "../include/DtcConstruction.h"
#include <vector>
#include <iostream>

void NaIPhysicalGeometry::createGeometry(double* param) const {
    if (dtctype == 0) {
        SurfaceRegistry reg;
        double ox = param[0], oy = param[1], oz = param[2];
        double ix = param[3], iy = param[4], iz = param[4];

        // --- Crystal (inner, built first) ---
        Geometry* crystal = new Cuboid(ix, iy, iz);
        crystal->generateMesh({0, 0, 0}, 2/*NaI*/, -1/*outmat*/);
        reg.resolveFaces(crystal->getInternalTriangles());
        crystal->outputmesh(const_cast<std::vector<Triangle>&>(triangles));
        delete crystal;

        // --- Housing (outer, built second) ---
        Geometry* housing = new Cuboid(ox, oy, oz);
        housing->generateMesh({0, 0, 0}, 3/*housing*/, -1/*outmat*/);
        reg.resolveFaces(housing->getInternalTriangles());
        housing->outputmesh(const_cast<std::vector<Triangle>&>(triangles));
        delete housing;
    } else {
        std::cerr << "Unsupported DTC type for NaIPhysicalGeometry" << std::endl;
    }
}
