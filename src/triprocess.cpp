#include "../include/triprocess.h"
#include <cmath>

Vec3 NormalCal(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3) {
    // Calculate the normal vector using the cross product of two edges
    Vec3 edge1 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    Vec3 edge2 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    Vec3 normal = {
        edge1.y * edge2.z - edge1.z * edge2.y,
        edge1.z * edge2.x - edge1.x * edge2.z,
        edge1.x * edge2.y - edge1.y * edge2.x
    };
    //normalization
    double length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length > 0) {
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
    }
    return normal;
}

Vec3 NormalCal(Vec3 v0, Vec3 v1, Vec3 v2) {
    // Calculate the normal vector using the cross product of two edges
    Vec3 edge1 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    Vec3 edge2 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    Vec3 normal = {
        edge1.y * edge2.z - edge1.z * edge2.y,
        edge1.z * edge2.x - edge1.x * edge2.z,
        edge1.x * edge2.y - edge1.y * edge2.x
    };
    //normalization
    double length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length > 0) {
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
    }
    return normal;
}

Vec3 CenterCal(Vec3 v0, Vec3 v1, Vec3 v2) {
    // Calculate the center of the triangle
    Vec3 center = {
        (v0.x + v1.x + v2.x) / 3,
        (v0.y + v1.y + v2.y) / 3,
        (v0.z + v1.z + v2.z) / 3
    };
    return center;
}