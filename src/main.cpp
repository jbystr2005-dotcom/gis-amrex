#include <iostream>
#include <AMReX.H>
#include "GISProcessor.H"
#include "Simulation.H"

using namespace amrex;

int main(int argc, char* argv[])
{
    Initialize(argc, argv);
    
    {
        GISProcessor processor;

        GISData data = processor.load("data/export.geojson");

        Simulation simulation(data);

        simulation.initialize();

        cout << "Width: " << data.width << "\n";
        cout << "Height: " << data.height << "\n";
        cout << "Number of buildings: " << data.buildings.size() << "\n";
    }

    Finalize();
    return 0;
}