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

// Implementation of Specific PhysicalGeometry