/*
  Python bindings for the `Species` class.
*/

/*
  Contributors: Fernando Zago.
*/

#include "../genus/species.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


// Binds the `Species` class to a Python module.
void bind_Species(pybind11::module& m);
