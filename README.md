# DetMesh: Triangulated Surface Modeling for Detectors

DetMesh is a lightweight, extensible C++ framework for generating triangulated surface models of detectors from parameterized geometric descriptions. It is designed as the geometry part of the sourceless efficiency calibration workflow, but can also be used independently to produce detector mesh models for other Monte Carlo transport codes.

## Overview

Detectors such as high-purity germanium (HPGe) and scintillation detectors can be described by a modest set of geometric parameters (crystal dimensions, dead-layer thickness, borehole geometry, housing dimensions, etc.). DetMesh converts these parameters directly into triangulated surface meshes, preserving the structural features most relevant to particle transport simulation while avoiding the complexity of general-purpose CAD or mesh-generation tools.

The framework adopts a hierarchical architecture that decouples **geometric primitives** from **detector assembly logic**, allowing users to define new detector types by composing basic shapes and overriding a single virtual function.

## Features

- **Parameterized detector modeling** — detectors are described by a compact set of numeric parameters read from binary `.dtc` files
- **Standard VRML 2.0 export** — output files can be inspected in any 3D viewer for visual verification
- **Lightweight and self-contained** — depends only on the C++ standard library; no external geometry kernel or mesh library required
- **Extensible** — new geometry primitives and new detector types are added by subclassing the `Geometry` and `PhysicalGeometry` abstract interfaces, respectively

## Code Structure

```
include/
  geometry.h           Geometry abstract base class (generateMesh, outputmesh, rotateMesh, relocatemesh)
  UserGeometrys.h      Concrete geometries: ChamferedHollowCylinder, Cuboid
  structs.h            Basic data types: Vec3, Triangle
  triprocess.h         Normal and center calculations for triangles
  SurfaceRegistry.h    Coincident-face detection and separation
  DtcConstruction.h    PhysicalGeometry abstract base class
  OutputGeometry.h     VRML 2.0 export
  dtcread.h            Binary parameter-file reader

src/
  main.cpp             Driver program
  UserGeometrys.cpp    Mesh-generation algorithms for cylinder and cuboid
  triprocess.cpp       Triangle normal / center utilities
  SurfaceRegistry.cpp  Coincident-surface resolution logic
  DtcConstruction.cpp  (see Example/ for concrete detector implementations)
  OutputGeometry.cpp   VRML writer
  dtcread.cpp          Binary file reader

Example/
  hpge/                HPGe coaxial detector (ChamferedHollowCylinder-based)
  nai/                 NaI scintillation detector (Cuboid-based)
```

## Quick Start

### Build

No external dependencies are required beyond the C++ standard library.

### Parameter file format

Detector parameters are stored as binary `.dtc` files. The format is:

| Offset | Type     | Content                          |
|--------|----------|----------------------------------|
| 0      | `int`    | Number of parameters *N*         |
| 4      | `double` | Parameter 0                      |
| 12     | `double` | Parameter 1                      |
| ...    | ...      | ...                              |
| 4+8*N  | —        | End of file                      |

Example for an HPGe detector (5 parameters: crystal diameter, crystal length, entrance-window radius, entrance-window thickness, front-edge chamfer radius):

```cpp
int count = 5;
double params[] = {50.0, 110.0, 100.0, 30.0, 10.0};
FILE* f = fopen("detector0.dtc", "wb");
fwrite(&count, sizeof(int), 1, f);
fwrite(params, sizeof(double), count, f);
fclose(f);
```

### Usage

```cpp
#include "dtcread.h"
#include "DtcConstruction.h"       // or "Example/hpge/DtcConstruction.h"
#include "OutputGeometry.h"

int main() {
    double* fparamD;
    ReadDtcParams("detector0.dtc", fparamD);

    std::vector<Triangle> triangles;
    PhysicalGeometry* det = new HPGePhysicalGeometry(0, triangles);
    det->createGeometry(fparamD);

    exportWRLWithNormals("detector.wrl", triangles);
    delete[] fparamD;
    return 0;
}
```

## Adding a New Detector Type

1. Subclass `PhysicalGeometry` and implement `createGeometry(double* param)`
2. Inside `createGeometry`, follow the **inside-out** assembly pattern with `SurfaceRegistry`:

```cpp
void MyDetector::createGeometry(double* param) const {
    SurfaceRegistry reg;

    // 1. Inner component (registered first)
    Geometry* inner = new Cuboid(...);
    inner->generateMesh({0, 0, 0}, innerMat, -1);
    reg.resolveFaces(inner->getInternalTriangles());
    inner->outputmesh(triangles);
    delete inner;

    // 2. Outer component (coincident faces get pushed outward)
    Geometry* outer = new Cuboid(...);
    outer->generateMesh({0, 0, 0}, outerMat, -1);
    reg.resolveFaces(outer->getInternalTriangles());
    outer->outputmesh(triangles);
    delete outer;
}
```

See `Example/hpge/` and `Example/nai/` for complete working examples.

## Adding a New Geometry Primitive

1. Subclass `Geometry` and implement the five pure-virtual methods:
   - `generateMesh(Vec3 pos, int outerMat, int innerMat)` — populate the internal triangle buffer
   - `outputmesh(std::vector<Triangle>&)` — append internal triangles to an external container
   - `rotateMesh(int axis, double pos)` — reflect mesh across a plane perpendicular to the given axis
   - `relocatemesh(Vec3 offset)` — translate all vertices
   - `getInternalTriangles()` — return a reference to the internal triangle buffer (used by `SurfaceRegistry`)
2. Register the new class in `UserGeometrys.h`.

## Reference

If you use DetMesh in your work, please cite:

> Zhang K, Yan S, Wu Z, Zhang H, Qiu R, Li J. *DetMesh-Gadep: Triangulated Surface Modeling and GPU-based Monte Carlo Efficiency Calibration of High-Purity Germanium Detectors.* (Preprint at arXiv:2605.25963)

## License

This project is made available for academic and research use. See the manuscript for institutional affiliation and contact information.
