#define _USE_MATH_DEFINES
#include "../include/UserGeometrys.h"
#include <iostream>
#include <cmath>
void ChamferedHollowCylinder::generateMesh(Vec3 position, int outerMat, int innerMat) const{
    //MEMBER VARIBLES:
    //outerradius, innerradius, chamferradius, zheight, silces
    if ((outerradius < 0) || (innerradius < 0) || (chamferradius < 0) || (zheight < 0) || (radslices < 3) || (zslices < 3) || (innerradius > outerradius) || ((outerradius - innerradius) < chamferradius )) {
        std::cerr << "Invalid parameters for ChamferedHollowCylinder." << std::endl;
        return;
    }
    //Starting Generation
    if (innerradius == 0 && chamferradius == 0) {
        //Generate a solid cylinder
        for (int i = 0; i < radslices; ++i) {
            double angle1 = (2 * M_PI * i) / radslices;
            double angle2 = (2 * M_PI * (i + 1)) / radslices;
            //Side triangles of the cylinder - position
            Vec3 v0 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z };
            Vec3 v1 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z };
            Vec3 v2 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z + zheight };
            Vec3 v3 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z + zheight };
            //Side triangles of the cylinder - center and normal
            Vec3 center1 = CenterCal(v0, v1, v2);
            Vec3 normal1 = NormalCal(v0, v1, v2, v3);
            Vec3 center2 = CenterCal(v0, v2, v3);
            //push back side triangles
            triangle_output->push_back({ v0, v1, v2, outerMat, innerMat, center1, normal1 });
            triangle_output->push_back({ v0, v2, v3, outerMat, innerMat, center2, normal1 });
            //Bottom and Top triangles of the cylinder - position
            Vec3 bottomCenter = { position.x, position.y, position.z };
            Vec3 bottomNormal = { 0, 0, -1 };
            Vec3 topCenter = { position.x, position.y, position.z + zheight };
            Vec3 topNormal = { 0, 0, 1 };            
            Vec3 center3 = CenterCal(v0, v1, bottomCenter);
            Vec3 center4 = CenterCal(v2, v3, topCenter);
            //push back bottom and top triangles
            triangle_output->push_back({ v0, v1, bottomCenter, outerMat, innerMat, center3, bottomNormal });
            triangle_output->push_back({ v2, v3, topCenter, outerMat, innerMat, center4, topNormal });
        }
        //end of generation
        std::cout << "case 1 happened"<< std::endl;
        return;
    }
    else if (innerradius == 0 && chamferradius != 0 && chamferradius < outerradius) {
        //Generate a solid cylinder
        for (int i = 0; i < radslices; ++i) {
            double angle1 = (2 * M_PI * i) / radslices;
            double angle2 = (2 * M_PI * (i + 1)) / radslices;
            //Side triangles of the cylinder - position
            Vec3 v0 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z + chamferradius };
            Vec3 v1 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z + chamferradius };
            Vec3 v2 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z + zheight };
            Vec3 v3 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z + zheight };
            //Side triangles of the cylinder - center and normal
            Vec3 center1 = CenterCal(v0, v1, v2);
            Vec3 normal1 = NormalCal(v0, v1, v2, v3);
            Vec3 center2 = CenterCal(v0, v2, v3);
            //push back side triangles
            triangle_output->push_back({ v0, v1, v2, outerMat, innerMat, center1, normal1 });
            triangle_output->push_back({ v0, v2, v3, outerMat, innerMat, center2, normal1 });
            //Bottom and Top triangles of the cylinder - position
            Vec3 bottomCenter = { position.x, position.y, position.z };
            Vec3 topCenter = { position.x, position.y, position.z + zheight };
            Vec3 v4 = { position.x + (outerradius - chamferradius) * cos(angle1), position.y + (outerradius - chamferradius) * sin(angle1), position.z };
            Vec3 v5 = { position.x + (outerradius - chamferradius) * cos(angle2), position.y + (outerradius - chamferradius) * sin(angle2), position.z };
            //Bottom and Top triangles of the cylinder - center and normal
            Vec3 bottomNormal = { 0, 0, -1 };
            Vec3 topNormal = { 0, 0, 1 };            
            Vec3 center3 = CenterCal(v4, v5, bottomCenter);
            Vec3 center4 = CenterCal(v2, v3, topCenter);
            //push back bottom and top triangles
            triangle_output->push_back({ v4, v5, bottomCenter, outerMat, innerMat, center3, bottomNormal });
            triangle_output->push_back({ v2, v3, topCenter, outerMat, innerMat, center4, topNormal });
            //Chamfer triangles of the cylinder - position
            for (int j = 0; j <zslices; j++){
                double chamferdeg1 = (M_PI / 2) * (j) / zslices;
                double chamferdeg2 = (M_PI / 2) * (j + 1) / zslices;
                Vec3 cv0 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * cos(angle1),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * sin(angle1),
                             position.z + chamferradius * (1 - sin(chamferdeg1))};
                Vec3 cv1 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * cos(angle1),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * sin(angle1),
                             position.z + chamferradius * (1 - sin(chamferdeg2))};
                Vec3 cv2 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * cos(angle2),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * sin(angle2),
                             position.z + chamferradius * (1 - sin(chamferdeg2))};
                Vec3 cv3 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * cos(angle2),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * sin(angle2),
                             position.z + chamferradius * (1 - sin(chamferdeg1))};
                //Chamfer triangles of the cylinder - center and normal
                // 0 2 3 1
                Vec3 center5 = CenterCal(cv0, cv2, cv3);
                Vec3 center6 = CenterCal(cv0, cv1, cv2);
                Vec3 normal2 = NormalCal(cv0, cv1, cv2, cv3);
                //push back chamfer triangles
                triangle_output->push_back({ cv0, cv2, cv3, outerMat, innerMat, center5, normal2 });
                triangle_output->push_back({ cv0, cv1, cv2, outerMat, innerMat, center6, normal2 });
            }
        }
        //end of generation
        std::cout << "case 2 happened"<< std::endl;
        return;
    }
    else if (innerradius == 0 && chamferradius == outerradius){
        //Generate a solid cylinder
        for (int i = 0; i < radslices; ++i) {
            double angle1 = (2 * M_PI * i) / radslices;
            double angle2 = (2 * M_PI * (i + 1)) / radslices;
            //Side triangles of the cylinder - position
            Vec3 v0 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z + chamferradius };
            Vec3 v1 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z + chamferradius };
            Vec3 v2 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z + zheight };
            Vec3 v3 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z + zheight };
            //Side triangles of the cylinder - center and normal
            Vec3 center1 = CenterCal(v0, v1, v2);
            Vec3 normal1 = NormalCal(v0, v1, v2, v3);
            Vec3 center2 = CenterCal(v0, v2, v3);
            //push back side triangles
            triangle_output->push_back({ v0, v1, v2, outerMat, innerMat, center1, normal1 });
            triangle_output->push_back({ v0, v2, v3, outerMat, innerMat, center2, normal1 });
            //Bottom and Top triangles of the cylinder - position
            Vec3 bottomCenter = { position.x, position.y, position.z };
            Vec3 topCenter = { position.x, position.y, position.z + zheight };
            Vec3 v4 = { position.x + (outerradius - chamferradius) * cos(angle1), position.y + (outerradius - chamferradius) * sin(angle1), position.z };
            Vec3 v5 = { position.x + (outerradius - chamferradius) * cos(angle2), position.y + (outerradius - chamferradius) * sin(angle2), position.z };
            //Bottom and Top triangles of the cylinder - center and normal
            Vec3 bottomNormal = { 0, 0, -1 };
            Vec3 topNormal = { 0, 0, 1 };            
            Vec3 center3 = CenterCal(v4, v5, bottomCenter);
            Vec3 center4 = CenterCal(v2, v3, topCenter);
            //push back bottom and top triangles
            triangle_output->push_back({ v4, v5, bottomCenter, outerMat, innerMat, center3, bottomNormal });
            triangle_output->push_back({ v2, v3, topCenter, outerMat, innerMat, center4, topNormal });
            //Chamfer triangles of the cylinder - position
            for (int j = 0; j <zslices - 1; j++){
                double chamferdeg1 = (M_PI / 2) * (j) / zslices;
                double chamferdeg2 = (M_PI / 2) * (j + 1) / zslices;
                Vec3 cv0 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * cos(angle1),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * sin(angle1),
                             position.z + chamferradius * (1 - sin(chamferdeg1))};
                Vec3 cv1 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * cos(angle1),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * sin(angle1),
                             position.z + chamferradius * (1 - sin(chamferdeg2))};
                Vec3 cv2 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * cos(angle2),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * sin(angle2),
                             position.z + chamferradius * (1 - sin(chamferdeg2))};
                Vec3 cv3 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * cos(angle2),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * sin(angle2),
                             position.z + chamferradius * (1 - sin(chamferdeg1))};
                //Chamfer triangles of the cylinder - center and normal
                // 0 2 3 1
                Vec3 center5 = CenterCal(cv0, cv2, cv3);
                Vec3 center6 = CenterCal(cv0, cv1, cv2);
                Vec3 normal2 = NormalCal(cv0, cv1, cv2, cv3);
                //push back chamfer triangles
                triangle_output->push_back({ cv0, cv2, cv3, outerMat, innerMat, center5, normal2 });
                triangle_output->push_back({ cv0, cv1, cv2, outerMat, innerMat, center6, normal2 });
            }
                double chamferdeg1 = (M_PI / 2) * (zslices - 1) / zslices;
                double chamferdeg2 = (M_PI / 2);
                Vec3 cv0 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * cos(angle1),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * sin(angle1),
                             position.z + chamferradius * (1 - sin(chamferdeg1))};
                Vec3 cv1 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * cos(angle1),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg2)) * sin(angle1),
                             position.z + chamferradius * (1 - sin(chamferdeg2))};
                Vec3 cv3 = { position.x + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * cos(angle2),
                             position.y + (outerradius - chamferradius + chamferradius * cos(chamferdeg1)) * sin(angle2),
                             position.z + chamferradius * (1 - sin(chamferdeg1))};
                Vec3 center6 = CenterCal(cv0, cv1, cv3);
                Vec3 normal2 = NormalCal(cv0, cv1, cv3);
                triangle_output->push_back({ cv0, cv1, cv3, outerMat, innerMat, center6, normal2 });
        }
        //end of generation
        std::cout << "case 3 happened"<< std::endl;
        return;
    }
    else if (innerradius != 0 && chamferradius == 0) {
        //Generate a hollow cylinder without chamfer
        for (int i = 0; i < radslices; ++i) {
            double angle1 = (2 * M_PI * i) / radslices;
            double angle2 = (2 * M_PI * (i + 1)) / radslices;
            //Outer Side triangles of the cylinder - position
            Vec3 v0 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z };
            Vec3 v1 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z };
            Vec3 v2 = { position.x + outerradius * cos(angle2), position.y + outerradius * sin(angle2), position.z + zheight };
            Vec3 v3 = { position.x + outerradius * cos(angle1), position.y + outerradius * sin(angle1), position.z + zheight };
            //Outer Side triangles of the cylinder - center and normal
            Vec3 center1 = CenterCal(v0, v1, v2);
            Vec3 normal1 = NormalCal(v0, v1, v2, v3);
            Vec3 center2 = CenterCal(v0, v2, v3);
            //push back outer side triangles
            triangle_output->push_back({ v0, v1, v2, outerMat, innerMat, center1, normal1 });
            triangle_output->push_back({ v0, v2, v3, outerMat, innerMat, center2, normal1 });
            //Inner Side triangles of the cylinder - position
            Vec3 v4 = { position.x + innerradius * cos(angle1), position.y + innerradius * sin(angle1), position.z };
            Vec3 v5 = { position.x + innerradius * cos(angle2), position.y + innerradius * sin(angle2), position.z };
            Vec3 v6 = { position.x + innerradius * cos(angle2), position.y + innerradius * sin(angle2), position.z + zheight };
            Vec3 v7 = { position.x + innerradius * cos(angle1), position.y + innerradius * sin(angle1), position.z + zheight };
            //Inner Side triangles of the cylinder - center and normal
            Vec3 center3 = CenterCal(v4, v5, v6);
            Vec3 normal2 = NormalCal(v7, v6, v5, v4);
            Vec3 center4 = CenterCal(v4, v6, v7);
            //push back inner side triangles
            triangle_output->push_back({ v5, v4, v6, outerMat, innerMat, center3, normal2 });
            triangle_output->push_back({ v6, v4, v7, outerMat, innerMat, center4, normal2 });
            //Bottom triangles of the cylinder - center and normal
            Vec3 bottomNormal = { 0, 0, -1 };
            Vec3 topNormal = { 0, 0, 1 };            
            Vec3 center5 = CenterCal(v0, v1, v5);
            Vec3 center6 = CenterCal(v0, v5, v4);
            Vec3 center7 = CenterCal(v2, v3, v6);
            Vec3 center8 = CenterCal(v2, v6, v7);
            //push back bottom triangles
            triangle_output->push_back({ v0, v1, v5, outerMat, innerMat, center5, bottomNormal });
            triangle_output->push_back({ v0, v5, v4, outerMat, innerMat, center6, bottomNormal });
            triangle_output->push_back({ v2, v3, v6, outerMat, innerMat, center7, topNormal });
            triangle_output->push_back({ v2, v6, v7, outerMat, innerMat, center8, topNormal });
        }
        //end of generation
        std::cout << "case 4 happened"<< std::endl;
        return;
    }
    else{
        std::cerr << "No Case Happened in Generating Mesh!!!" << std::endl << "with InnerRadius = " 
        << innerradius << "& ChamferRadius = " << chamferradius << std::endl;
        return;
    }
}

void ChamferedHollowCylinder::rotateMesh(int axis, double position) const {
    //1-x,2-y,3-z
    if (axis == 1){
        for (auto& triangle : *triangle_output) {
            triangle.v0.x = 2*position - triangle.v0.x;
            triangle.v1.x = 2*position - triangle.v1.x;
            triangle.v2.x = 2*position - triangle.v2.x;
            triangle.center.x = 2*position - triangle.center.x;
            triangle.normal.x = -triangle.normal.x;
        }
    }
    else if (axis == 2){
        for (auto& triangle : *triangle_output) {
            triangle.v0.y = 2*position - triangle.v0.y;
            triangle.v1.y = 2*position - triangle.v1.y;
            triangle.v2.y = 2*position - triangle.v2.y;
            triangle.center.y = 2*position - triangle.center.y;
            triangle.normal.y = -triangle.normal.y;
        }
    }
    else if (axis == 3){
        for (auto& triangle : *triangle_output) {
            triangle.v0.z = 2*position - triangle.v0.z;
            triangle.v1.z = 2*position - triangle.v1.z;
            triangle.v2.z = 2*position - triangle.v2.z;
            triangle.center.z = 2*position - triangle.center.z;
            triangle.normal.z = -triangle.normal.z;
        }
    }
    else {
        return;
    }
}

void ChamferedHollowCylinder::outputmesh(std::vector<Triangle>& triangles) const {
    triangles.insert(triangles.end(), triangle_output->begin(), triangle_output->end());
}

void ChamferedHollowCylinder::relocatemesh(Vec3 position) const {
    for (auto& triangle : *triangle_output) {
        triangle.v0 = position + triangle.v0;
        triangle.v1 = position + triangle.v1;
        triangle.v2 = position + triangle.v2;
        triangle.center = position + triangle.center;
    }
}


// ========== Cuboid ==========
Cuboid::Cuboid(double sx, double sy, double sz) : sizex(sx), sizey(sy), sizez(sz) {
    triangle_output = new std::vector<Triangle>();
}

Cuboid::~Cuboid() {
    delete triangle_output;
}

void Cuboid::generateMesh(Vec3 position, int outerMat, int innerMat) const {
    if (sizex <= 0 || sizey <= 0 || sizez <= 0) {
        std::cerr << "Invalid parameters for Cuboid." << std::endl;
        return;
    }
    double hx = sizex / 2.0;
    double hy = sizey / 2.0;
    double hz = sizez / 2.0;
    double px = position.x, py = position.y, pz = position.z;

    // 8 corners
    Vec3 p000 = {px - hx, py - hy, pz - hz};
    Vec3 p001 = {px - hx, py - hy, pz + hz};
    Vec3 p010 = {px - hx, py + hy, pz - hz};
    Vec3 p011 = {px - hx, py + hy, pz + hz};
    Vec3 p100 = {px + hx, py - hy, pz - hz};
    Vec3 p101 = {px + hx, py - hy, pz + hz};
    Vec3 p110 = {px + hx, py + hy, pz - hz};
    Vec3 p111 = {px + hx, py + hy, pz + hz};

    // +X face (normal = {1,0,0})
    {
        Vec3 n = {1, 0, 0};
        Vec3 v0 = p111, v1 = p101, v2 = p100, v3 = p110;
        triangle_output->push_back({v0, v1, v2, outerMat, innerMat, CenterCal(v0, v1, v2), n});
        triangle_output->push_back({v0, v2, v3, outerMat, innerMat, CenterCal(v0, v2, v3), n});
    }
    // -X face (normal = {-1,0,0})
    {
        Vec3 n = {-1, 0, 0};
        Vec3 v0 = p001, v1 = p011, v2 = p010, v3 = p000;
        triangle_output->push_back({v0, v1, v2, outerMat, innerMat, CenterCal(v0, v1, v2), n});
        triangle_output->push_back({v0, v2, v3, outerMat, innerMat, CenterCal(v0, v2, v3), n});
    }
    // +Y face (normal = {0,1,0})
    {
        Vec3 n = {0, 1, 0};
        Vec3 v0 = p111, v1 = p011, v2 = p010, v3 = p110;
        triangle_output->push_back({v0, v1, v2, outerMat, innerMat, CenterCal(v0, v1, v2), n});
        triangle_output->push_back({v0, v2, v3, outerMat, innerMat, CenterCal(v0, v2, v3), n});
    }
    // -Y face (normal = {0,-1,0})
    {
        Vec3 n = {0, -1, 0};
        Vec3 v0 = p100, v1 = p000, v2 = p001, v3 = p101;
        triangle_output->push_back({v0, v1, v2, outerMat, innerMat, CenterCal(v0, v1, v2), n});
        triangle_output->push_back({v0, v2, v3, outerMat, innerMat, CenterCal(v0, v2, v3), n});
    }
    // +Z face (normal = {0,0,1})
    {
        Vec3 n = {0, 0, 1};
        Vec3 v0 = p111, v1 = p011, v2 = p001, v3 = p101;
        triangle_output->push_back({v0, v1, v2, outerMat, innerMat, CenterCal(v0, v1, v2), n});
        triangle_output->push_back({v0, v2, v3, outerMat, innerMat, CenterCal(v0, v2, v3), n});
    }
    // -Z face (normal = {0,0,-1})
    {
        Vec3 n = {0, 0, -1};
        Vec3 v0 = p010, v1 = p110, v2 = p100, v3 = p000;
        triangle_output->push_back({v0, v1, v2, outerMat, innerMat, CenterCal(v0, v1, v2), n});
        triangle_output->push_back({v0, v2, v3, outerMat, innerMat, CenterCal(v0, v2, v3), n});
    }
}

void Cuboid::outputmesh(std::vector<Triangle>& triangles) const {
    triangles.insert(triangles.end(), triangle_output->begin(), triangle_output->end());
}

void Cuboid::rotateMesh(int axis, double position) const {
    if (axis == 1) {
        for (auto& triangle : *triangle_output) {
            triangle.v0.x = 2 * position - triangle.v0.x;
            triangle.v1.x = 2 * position - triangle.v1.x;
            triangle.v2.x = 2 * position - triangle.v2.x;
            triangle.center.x = 2 * position - triangle.center.x;
            triangle.normal.x = -triangle.normal.x;
        }
    } else if (axis == 2) {
        for (auto& triangle : *triangle_output) {
            triangle.v0.y = 2 * position - triangle.v0.y;
            triangle.v1.y = 2 * position - triangle.v1.y;
            triangle.v2.y = 2 * position - triangle.v2.y;
            triangle.center.y = 2 * position - triangle.center.y;
            triangle.normal.y = -triangle.normal.y;
        }
    } else if (axis == 3) {
        for (auto& triangle : *triangle_output) {
            triangle.v0.z = 2 * position - triangle.v0.z;
            triangle.v1.z = 2 * position - triangle.v1.z;
            triangle.v2.z = 2 * position - triangle.v2.z;
            triangle.center.z = 2 * position - triangle.center.z;
            triangle.normal.z = -triangle.normal.z;
        }
    }
}

void Cuboid::relocatemesh(Vec3 position) const {
    for (auto& triangle : *triangle_output) {
        triangle.v0 = position + triangle.v0;
        triangle.v1 = position + triangle.v1;
        triangle.v2 = position + triangle.v2;
        triangle.center = position + triangle.center;
    }
}