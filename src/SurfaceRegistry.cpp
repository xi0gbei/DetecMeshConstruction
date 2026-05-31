#include "../include/SurfaceRegistry.h"
#include <cmath>

bool SurfaceRegistry::isAxisAligned(const Vec3& normal) {
    const double eps = 1.0e-9;
    double ax = std::abs(normal.x);
    double ay = std::abs(normal.y);
    double az = std::abs(normal.z);
    return (std::abs(ax - 1.0) < eps && ay < eps && az < eps) ||
           (std::abs(ay - 1.0) < eps && ax < eps && az < eps) ||
           (std::abs(az - 1.0) < eps && ax < eps && ay < eps);
}

FaceDir SurfaceRegistry::normalToFaceDir(const Vec3& normal) {
    if (normal.x > 0.5) return FaceDir::POS_X;
    if (normal.x < -0.5) return FaceDir::NEG_X;
    if (normal.y > 0.5) return FaceDir::POS_Y;
    if (normal.y < -0.5) return FaceDir::NEG_Y;
    if (normal.z > 0.5) return FaceDir::POS_Z;
    return FaceDir::NEG_Z;
}

Vec3 SurfaceRegistry::faceDirToNormal(FaceDir dir) {
    switch (dir) {
        case FaceDir::POS_X: return { 1.0,  0.0,  0.0};
        case FaceDir::NEG_X: return {-1.0,  0.0,  0.0};
        case FaceDir::POS_Y: return { 0.0,  1.0,  0.0};
        case FaceDir::NEG_Y: return { 0.0, -1.0,  0.0};
        case FaceDir::POS_Z: return { 0.0,  0.0,  1.0};
        case FaceDir::NEG_Z: return { 0.0,  0.0, -1.0};
    }
    return {0.0, 0.0, 0.0};
}

int SurfaceRegistry::resolveFaces(std::vector<Triangle>& triangles, double epsilon) {
    // Group axis-aligned triangles by (FaceDir, planeDistance)
    struct FaceGroup {
        FaceDir dir;
        double planeDist;
        std::vector<size_t> triIndices;
    };
    std::vector<FaceGroup> groups;

    for (size_t i = 0; i < triangles.size(); ++i) {
        const Triangle& tri = triangles[i];
        if (!isAxisAligned(tri.normal)) continue;

        FaceDir dir = normalToFaceDir(tri.normal);
        double planeDist = tri.normal.x * tri.v0.x +
                          tri.normal.y * tri.v0.y +
                          tri.normal.z * tri.v0.z;

        bool found = false;
        for (auto& g : groups) {
            if (g.dir == dir && std::abs(g.planeDist - planeDist) < COINCIDENT_TOLERANCE) {
                g.triIndices.push_back(i);
                found = true;
                break;
            }
        }
        if (!found) {
            groups.push_back({dir, planeDist, {i}});
        }
    }

    // Check each group against registry
    int adjustedCount = 0;
    for (auto& g : groups) {
        auto& registered = registeredPlanes_[g.dir];
        bool coincident = false;
        for (double regDist : registered) {
            if (std::abs(regDist - g.planeDist) < COINCIDENT_TOLERANCE) {
                coincident = true;
                break;
            }
        }

        if (coincident) {
            Vec3 offset = faceDirToNormal(g.dir);
            offset.x *= epsilon;
            offset.y *= epsilon;
            offset.z *= epsilon;
            for (size_t idx : g.triIndices) {
                Triangle& tri = triangles[idx];
                tri.v0 = tri.v0 + offset;
                tri.v1 = tri.v1 + offset;
                tri.v2 = tri.v2 + offset;
                tri.center = tri.center + offset;
            }
            ++adjustedCount;
        } else {
            registered.push_back(g.planeDist);
        }
    }

    return adjustedCount;
}
