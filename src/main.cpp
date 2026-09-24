#include <iostream>
#include <AMReX.H>
#include "GISProcessor.H"
#include "Simulation.H"

int main(int argc, char* argv[])
{
    amrex::Initialize(argc, argv);
    {
        GISProcessor processor;

        GISData data = processor.load("data/export.geojson");

        Simulation simulation(data);

        simulation.initialize();
    }
    amrex::Finalize();
    return 0;
}