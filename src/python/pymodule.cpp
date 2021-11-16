/*
  Assembles all Python bindings into a module.
*/

/*
  Contributors: Fernando Zago.
*/

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../neatnik/pyneatnik.hpp"
#include "../organism/pyorganism.hpp"
#include "../genus/pyspecies.hpp"
#include "../genus/pygenus.hpp"
#include "../experiment/pyparameters.hpp"
#include "../experiment/pyexperiment.hpp"

// Assembles NEATnik's Python module.
PYBIND11_MODULE(neatnik, m)
{
    bind_NEATnik(m);
    bind_Genus(m);
    bind_Species(m);
    bind_Organism(m);
    bind_Parameters(m);
    bind_Experiment(m);
}
