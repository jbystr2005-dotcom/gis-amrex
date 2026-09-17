#pragma once
#include <string>
#include "GeometryTypes.H"

class GISProcessor
{
public:
    GISData load(const std::string& filename);

private:
    void readBuildings();
    void projectCoordinates();
    void calculateBounds();
    void shiftToLocalCoordinates();
};