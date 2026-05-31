#include "../include/DtcConstruction.h"

// SurfaceRegistry integration pattern (inside-out assembly):
//
//   SurfaceRegistry reg;
//   // 1. Inner geometry first
//   Geometry* inner = new ...;
//   inner->generateMesh(...);
//   inner->rotateMesh / relocatemesh (as needed);
//   reg.resolveFaces(inner->getInternalTriangles());
//   inner->outputmesh(triangles);
//   delete inner;
//   // 2. Outer geometry second
//   Geometry* outer = new ...;
//   outer->generateMesh(...);
//   outer->rotateMesh / relocatemesh (as needed);
//   reg.resolveFaces(outer->getInternalTriangles());
//   outer->outputmesh(triangles);
//   delete outer;
//
// See Example/hpge/ and Example/nai/ for concrete detector implementations.
