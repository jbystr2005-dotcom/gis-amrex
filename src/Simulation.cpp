#include "Simulation.H"
#include <AMReX_Box.H>
#include <AMReX_ParmParse.H>
#include <AMReX_Print.H>

using namespace amrex;

Simulation::Simulation(const GISData& data) : gisData(data) {}

void Simulation::initialize()
{
    ParmParse parameters("geometry");
    
    Vector<int> nCell(AMREX_SPACEDIM);
    parameters.getarr("n_cell", nCell);

    IntVect domainLo(0, 0);
    IntVect domainHi(nCell[0] - 1, nCell[1] - 1);

    Box grid(domainLo, domainHi);

    Print()
        << "Domain low: " << grid.smallEnd() << "\n"
        << "Domain high: " << grid.bigEnd() << "\n"
        << "Cells: " << grid.numPts() << "\n";
}
