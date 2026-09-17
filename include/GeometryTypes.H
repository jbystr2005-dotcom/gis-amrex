#pragma once
#include <vector>

using namespace std;

struct Point2D
{
    double x;
    double y;
};

struct Building
{
    vector<Point2D> footprint;
};

struct GISData
{
    vector<Building> buildings;

    double minX;
    double minY;
    double maxX;
    double maxY;

    double width;
    double height;
};