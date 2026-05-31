#include "../include/dtcread.h"
#include <cstdio>

bool ReadDtcParams(const std::string& filepath, double*& fparamD) {
    fparamD = nullptr;

    FILE* file = nullptr;
    if (fopen_s(&file, filepath.c_str(), "rb") != 0) {
        return false;
    }
    if (!file) return false;

    int paramCount = 0;
    if (std::fread(&paramCount, sizeof(int), 1, file) != 1) {
        std::fclose(file);
        return false;
    }

    if (paramCount <= 0) {
        std::fclose(file);
        return false;
    }

    fparamD = new double[paramCount];

    size_t readCount = std::fread(fparamD, sizeof(double), paramCount, file);
    std::fclose(file);

    if (readCount != static_cast<size_t>(paramCount)) {
        delete[] fparamD;
        fparamD = nullptr;
        return false;
    }

    return true;
}