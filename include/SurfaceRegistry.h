#pragma once
#include <vector>
#include <map>
#include "./structs.h"

enum class FaceDir {
    POS_X,  // normal = ( 1,  0,  0)
    NEG_X,  // normal = (-1,  0,  0)
    POS_Y,  // normal = ( 0,  1,  0)
    NEG_Y,  // normal = ( 0, -1,  0)
    POS_Z,  // normal = ( 0,  0,  1)
    NEG_Z   // normal = ( 0,  0, -1)
};

class SurfaceRegistry {
public:
    static constexpr double DEFAULT_EPSILON = 1.0e-4;
    static constexpr double COINCIDENT_TOLERANCE = 1.0e-9;

    // Group axis-aligned triangles by face, check against registry.
    // Coincident faces are offset by epsilon along their outward normal.
    // Non-coincident faces are registered. Returns number of adjusted faces.
    int resolveFaces(std::vector<Triangle>& triangles, double epsilon = DEFAULT_EPSILON);

private:
    static bool isAxisAligned(const Vec3& normal);
    static FaceDir normalToFaceDir(const Vec3& normal);
    static Vec3 faceDirToNormal(FaceDir dir);

    std::map<FaceDir, std::vector<double>> registeredPlanes_;
};
