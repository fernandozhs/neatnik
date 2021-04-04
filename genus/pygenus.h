/*
  Python bindings for the `Genus` class.
*/

/*
  Contributors: Fernando Zago.
*/

#include "../genus/genus.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Binds the `Genus` class to a Python module.
void bind_Genus(pybind11::module& m);
