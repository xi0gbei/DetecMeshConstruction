#include "../include/UserGeometrys.h"
#include "../include/dtcread.h"
#include "../include/DtcConstruction.h"
#include "../include/OutputGeometry.h"
#include <vector>
#include <iostream>
using namespace std;
int main(){
    double* fparamD; int detectorId;
    cout<<">>input the id of detector (0 for the example of HPGe and 1 for NaI): ";
     cin >> detectorId;
    string path = "..\\..\\..\\data\\parameters\\detector" + to_string(detectorId) + ".dtc";
    if (ReadDtcParams(path, fparamD)) {
    } else {
        cerr << "Failed to read DTC parameters." << endl;
        return -1;
    }
    vector<Triangle> traingles;
    PhysicalGeometry* geometry = new HPGePhysicalGeometry(0, traingles);
    //PhysicalGeometry* geometry = new NaIPhysicalGeometry(0, traingles);
    geometry->createGeometry(fparamD);
    exportWRLWithNormals("Detector.wrl", traingles);
    delete[] fparamD;
    return 0;
}