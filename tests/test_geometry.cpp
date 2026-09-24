#include <iostream>
#include "GeometryUtils.H"

int main()
{
    Building testBuilding;

    testBuilding.footprint = {
        {0.0, 0.0},
        {10.0, 0.0},
        {10.0, 10.0},
        {0.0, 10.0}
    };

    std::cout << "Outside test: " << pointInPolygon(15.0, 5.0, testBuilding) << '\n';
    std::cout << "Inside test: " << pointInPolygon(5.0, 5.0, testBuilding) << '\n';
    return 0;
}