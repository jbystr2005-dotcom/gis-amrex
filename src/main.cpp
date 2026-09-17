#include <iostream>
#include "GISProcessor.H"
#include "Simulation.H"

int main()
{
    GISProcessor processor;

    GISData data = processor.load("data/export.geojson");

    Simulation simulation(data);

    simulation.initialize();

    cout << "Width: " << data.width << "\n";
    cout << "Height: " << data.height << "\n";
    cout << "Number of buildings: " << data.buildings.size() << "\n";

    return 0;
}