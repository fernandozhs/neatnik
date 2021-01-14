/*
  Assembles all Python bindings into a module.
*/

/*
  Contributors: Fernando Zago.
*/

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../neatnik/pyneatnik.h"
#include "../organism/pyorganism.h"
#include "../genus/pyspecies.h"
#include "../genus/pygenus.h"
#include "../experiment/pyparameters.h"
#include "../experiment/pyexperiment.h"


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
