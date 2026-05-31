#ifndef STRUCTS_H
#define STRUCTS_H
struct Vec3 {
    double x, y, z;
    Vec3 operator+(const Vec3& rhs) const {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    }
    Vec3 operator-(const Vec3& rhs) const {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    }
};

struct Triangle {
    Vec3 v0, v1, v2;
    int outerMat = -1;
    int innerMat;
    Vec3 center;
    Vec3 normal;
};
#endif // STRUCTS_H