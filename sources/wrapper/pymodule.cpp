#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pyneatnik.hpp"
#include "pyorganism.hpp"
#include "pyspecies.hpp"
#include "pygenus.hpp"
#include "pyparameters.hpp"
#include "pyexperiment.hpp"


PYBIND11_MODULE(neatnik, m)
{
    bind_NEATnik(m);
    bind_Genus(m);
    bind_Species(m);
    bind_Organism(m);
    bind_Parameters(m);
    bind_Experiment(m);
}
