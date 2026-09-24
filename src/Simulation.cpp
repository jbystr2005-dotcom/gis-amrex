#include "Simulation.H"
#include <AMReX_Box.H>
#include <AMReX_ParmParse.H>
#include <AMReX_Print.H>
#include <AMReX_RealBox.H>
#include <AMReX_Geometry.H>

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
    RealBox physicalSpace(probLo, probHi);

    int coord = 0;
    int isPeriodic[AMREX_SPACEDIM] = {0, 0};

    Geometry geometry(grid, &physicalSpace, coord, isPeriodic);

    const Real* cellSize = geometry.CellSize();

    Print()
        << "dx: " << cellSize[0] << " meters\n"
        << "dy: " << cellSize[1] << " meters\n";
}
