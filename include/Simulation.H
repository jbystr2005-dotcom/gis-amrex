#pragma once
#include "GeometryTypes.H"

class Simulation
{
public:
    explicit Simulation(const GISData& data);

    void initialize();
    void run();

private:
    GISData gisData;
};