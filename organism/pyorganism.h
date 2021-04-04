/*
  Python bindings for the `Organism` class.
*/

/*
  Contributors: Fernando Zago.
*/

#include "../organism/organism.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Binds the `Organism` class to a Python module.
void bind_Organism(pybind11::module& m);
