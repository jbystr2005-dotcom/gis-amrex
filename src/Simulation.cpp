#include "Simulation.H"
#include <AMReX_Box.H>
#include <AMReX_ParmParse.H>
#include <AMReX_Print.H>
#include <AMReX_RealBox.H>

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

    Real probLo[AMREX_SPACEDIM] = {0.0, 0.0};
    Real probHi[AMREX_SPACEDIM] = {gisData.width, gisData.height};
    RealBox realBox(probLo, probHi);

    Print()
        << "Physical domain low: " << realBox.lo(0) << ", " << realBox.lo(1) << "\n"
        << "Physical domain high: " << realBox.hi(0) << ", " << realBox.hi(1) << "\n";
}
