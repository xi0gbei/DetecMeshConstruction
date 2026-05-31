#include "./geometry.h"
#include "./UserGeometrys.h"
#include "./SurfaceRegistry.h"
#include <vector>

class PhysicalGeometry{
public:
    virtual void createGeometry(double* param) const = 0;
    virtual std::vector<Triangle>& getTriangles() const = 0;
    virtual ~PhysicalGeometry() = default;
};

class NaIPhysicalGeometry : public PhysicalGeometry {
public:
    const std::vector<Triangle>& triangles;
    int dtctype;
public:
    NaIPhysicalGeometry(int dtctype, const std::vector<Triangle>& triangles)
        : dtctype(dtctype), triangles(triangles) {}
    void createGeometry(double* param) const override;
    std::vector<Triangle>& getTriangles() const override {
        return const_cast<std::vector<Triangle>&>(triangles);
    }
};
